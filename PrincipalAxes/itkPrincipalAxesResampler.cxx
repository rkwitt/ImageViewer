/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkPrincipalAxesResampler.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/


/*--------------------------------------------------------------------------
This command line program reads an image file, finds its principal
axes, and resamples the image into principal axes coordinates.  It
takes two arguments: the names of the input and output image files.
The image dimensions are fixed at 192 slices by 256 rows by 256
columns and the data format is fixed at bigendian 16-bit unsigned
integer.  (But see below for hooks to change these parameters.)
---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "itkAffineTransform.h"
#include "itkByteSwapper.h"
#include "itkImage.h"
#include "itkImageMomentsCalculator.h"
#include "itkResampleImageFilter.h"
#include "itkSimpleImageRegionIterator.h"
#include "itkLinearInterpolateImageFunction.h"

enum {NDimensions = 3};

typedef unsigned short                      PixelType;
typedef itk::Image<PixelType, NDimensions>  ImageType;
typedef ImageType::RegionType               ImageRegionType;
typedef ImageType::SizeType                 ImageSizeType;
typedef ImageType::AffineTransformType      AffineTransformType;

typedef itk::Index<NDimensions>                    ImageIndexType;
typedef itk::SimpleImageRegionIterator<ImageType>  ImageIteratorType;
typedef itk::ImageMomentsCalculator<ImageType>  ImageMomentsCalculatorType;
typedef itk::LinearInterpolateImageFunction<ImageType>  InterpolatorType;
typedef itk::Point<double, NDimensions>            PointType;


int
main(int argc, char *argv[])
{
    /* Set image and other parameters */
    long ImageWidth     = 256;
    long ImageHeight    = 256;
    long NumberOfSlices = 192;
    int bigend  = 1;             // Bigendian data in external files?
    int verbose = 1;             // Show intermediate results?

    /* Get input and output file names from the command line */
    if (argc < 2)
        {
            fprintf(stderr, "You must give input and output file names\n");
            exit(EXIT_FAILURE);
        }
    char *filename1 = argv[1];
    char *filename2 = argv[2];

    /* Open image file */
    /* FIXME: Translate into C++ */
    FILE *infile = fopen(filename1, "rb");
    if (infile == 0) 
        {
            fprintf(stderr, "Unable to open input file\n");
            exit(EXIT_FAILURE);
        }

    /* Allocate an image object to store the input file in */
    ImageIndexType base = {{0,0,0}};
    ImageSizeType  size = {{ImageWidth, ImageHeight, NumberOfSlices}};
    double spacing[3] = {1.0, 1.0, 1.0};      // Pixel size
    double origin [3] = {0.0, 0.0, 0.0};      // Location of (0,0,0) pixel
    ImageType::Pointer image = ImageType::New();
    ImageRegionType region;
    region.SetIndex(base);
    region.SetSize(size);
    image->SetLargestPossibleRegion(region);
    image->SetBufferedRegion(region);
    image->SetRequestedRegion(region);
    image->Allocate();
    image->SetOrigin(origin);
    image->SetSpacing(spacing);

    /* Read the image file into an itkImage object */
    /* FIXME: Find or write Insightful tools for this */
    std::cout << "Reading image file." << std::endl;
    ImageIndexType index;        // Index to current pixel
    unsigned long point[3];      // Location of current pixel
    PixelType *buff = new PixelType[ImageWidth];  // Input/output buffer
    PixelType maxval = 0;        // Maximum pixel value in image
    size_t count;
    for (long slice = 0; slice < NumberOfSlices; slice++) {
        point[2] = slice;
        for (long row = 0; row < ImageHeight; row++) {
            point[1] = row;
            count = fread(buff, sizeof(PixelType), ImageWidth, infile);
            if (count != (size_t)ImageWidth) {
                fprintf(stderr, "Error reading input file\n");
                exit(EXIT_FAILURE); 
            }
            if (bigend)
                itk::ByteSwapper<PixelType>::SwapRangeBE(buff, ImageWidth);
            else
                itk::ByteSwapper<PixelType>::SwapRangeLE(buff, ImageWidth);
            for (long col = 0; col < ImageWidth; col++) {
                point[0] = col;
                index.SetIndex(point);
                image->SetPixel(index, buff[col]);
                if (buff[col] > maxval)
                    maxval = buff[col];
            }
        }
    }

    /* Print the maximum pixel value found.  (This is useful for detecting
       all-zero images, which confuse the moments calculation.) */
    std::cout << "   Max pixel value: " << maxval << std::endl;

    /* Close the input file */
    fclose(infile);

    /* Compute principal moments and axes */
    std::cout << "Computing moments and transformation." << std::endl;
    ImageMomentsCalculatorType moments(image);
    double ctm = moments.GetTotalMass();
    itk::Vector<double,3>
        ccg = moments.GetCenterOfGravity();
    itk::Vector<double,3>
        cpm = moments.GetPrincipalMoments();
    itk::Matrix<double,3,3>
        cpa = moments.GetPrincipalAxes();

    /* Report moments information to the user */
    if (verbose) {
        std::cout << "\nTotal mass = "        << ctm << std::endl;
        std::cout << "\nCenter of gravity = " << ccg << std::endl;
        std::cout << "\nPrincipal moments = " << cpm << std::endl;
        std::cout << "\nPrincipal axes = \n";
        std::cout << cpa << "\n";
    }

    /* Compute the transform from principal axes to original axes */
    double pi = 3.14159265359;
    AffineTransformType::Pointer trans = AffineTransformType::New();
    itk::Vector<double,3> center;
    center[0] = -ImageWidth / 2.0;
    center[1] = -ImageHeight / 2.0;
    center[2] = -NumberOfSlices / 2.0;
    trans->Translate(center);
    trans->Rotate(1, 0, pi/2.0);   // Rotate into radiological orientation
    trans->Rotate(2, 0, -pi/2.0);
    AffineTransformType::Pointer pa2phys =
        moments.GetPrincipalAxesToPhysicalAxesTransform();
    if (verbose) {
        std::cout << "Principal axes to physical axes transform" << std::endl;
        pa2phys->PrintSelf( std::cout );
    }
    trans->Compose(pa2phys);
    trans->Compose(image->GetPhysicalToIndexTransform());
    if (verbose) {
        std::cout << "Backprojection transform:" << std::endl;
        trans->PrintSelf( std::cout );
    }

    /* Create and initialize the interpolator */
    InterpolatorType::Pointer interp = InterpolatorType::New();
    interp->SetInputImage(image);

    /* Resample image in principal axes coordinates */
    std::cout << "Resampling the image" << std::endl;
    itk::ResampleImageFilter< ImageType, ImageType >::Pointer resample;
    resample = itk::ResampleImageFilter< ImageType, ImageType >::New();
    resample->SetInput(image);
    resample->SetSize(size);
    resample->SetTransform(trans);
    resample->SetInterpolator(interp);

    // Run the resampling filter
    resample->Update();

    // Extract the output image
   ImageType::Pointer resamp = resample->GetOutput();

    /* Open the output file */
    /* FIXME: Translate into C++ */
    std::cout << "Writing the output file" << std::endl;
    FILE *outfile = fopen(filename2, "wb");
    if (outfile == 0) 
        {
            fprintf(stderr, "Unable to open output file\n");
            exit(EXIT_FAILURE);
        }

    /* Write resampled image to a file */
    for (long slice = 0; slice < NumberOfSlices; slice++) {
        point[2] = slice;
        for (long row = 0; row < ImageHeight; row++) {
            point[1] = row;
            for (long col = 0; col < ImageWidth; col++) {
                point[0] = col;
                index.SetIndex(point);
                buff[col] = resamp->GetPixel(index);
            }
            if (bigend)
                itk::ByteSwapper<PixelType>::SwapRangeBE(buff, ImageWidth);
            else
                itk::ByteSwapper<PixelType>::SwapRangeLE(buff, ImageWidth);
            count = fwrite(buff, 2, ImageWidth, outfile);
            if (count != (size_t)ImageWidth) {
                fprintf(stderr, "Error writing output file\n");
                exit(EXIT_FAILURE); }
        }
    }
    fclose(outfile);

    delete [] buff;
    return 0;
}
