/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    MRFGaussianClassifierValidationApp.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _MRFGaussianClassifierValidationApp_txx
#define _MRFGaussianClassifierValidationApp_txx

#include "MRFGaussianClassifierValidationApp.h"

namespace itk
{

template <typename TImage, typename TMaskImage>
MRFGaussianClassifierValidationApp<TImage,TMaskImage>
::MRFGaussianClassifierValidationApp()
{ 
  m_ImageDirectoryName = "";
  m_BrainSegmentationDirectoryName = "";
  m_PatientID = "";
  m_StartSliceNumber = 1;
  m_NumberOfSlices = 1;
  m_StartSegSliceNumber = 1;
  m_NumberOfSegSlices = 1;
  m_NumberOfChannels = 1;

  m_ParameterFileName = "";
  m_OutputFileName = "";
  m_AppendOutputFile = true;
}


template <typename TImage, typename TMaskImage>
void
MRFGaussianClassifierValidationApp<TImage,TMaskImage>
::InitializeParser()
{
  m_Parser->SetImageDirectoryName( m_ImageDirectoryName.c_str() );
  m_Parser->SetBrainMaskDirectoryName( m_BrainMaskDirectoryName.c_str() );
  m_Parser->SetBrainSegmentationDirectoryName( m_BrainSegmentationDirectoryName.c_str() );

  m_Parser->SetPatientID( m_PatientID.c_str() );
  m_Parser->SetStartSliceNumber( m_StartSliceNumber );
  m_Parser->SetNumberOfSlices( m_NumberOfSlices );
  m_Parser->SetStartSegSliceNumber( m_StartSegSliceNumber );
  m_Parser->SetNumberOfSegSlices( m_NumberOfSegSlices );
  m_Parser->SetNumberOfChannels( m_NumberOfChannels );

  m_Parser->SetParameterFileName( m_ParameterFileName.c_str() );
}


template <typename TImage, typename TMaskImage>
void
MRFGaussianClassifierValidationApp<TImage,TMaskImage>
::InitializeClassifier()
{
  typedef TImage VectorInputImageType;

  typename VectorInputImageType::Pointer testImage = m_Parser->GetVectorInputImage();

  m_Classifier->SetVectorInputImage( m_Parser->GetVectorInputImage() );
  m_Classifier->SetMaskInputImage( m_Parser->GetMaskImage() );

  m_Classifier->SetNumberOfClasses( m_NumberOfClasses );  
  m_Classifier->SetNumberOfChannels( m_Parser->GetNumberOfChannels() );

  m_Classifier->SetClassMeans( m_Parser->GetClassMeans() );
  m_Classifier->SetClassNumberOfSamples( m_Parser->GetClassNumberOfSamples() );
  m_Classifier->SetClassCovariances( m_Parser->GetClassCovariances() ); 
  
  m_Classifier->SetMaximumNumberOfIterations( m_MaximumNumberOfIterations );
  m_Classifier->SetNeighborhoodRadius( m_NeighborhoodRadius );
  m_Classifier->SetErrorTolerance( m_ErrorTolerance ); 
  m_Classifier->SetSmoothingFactor( m_SmoothingFactor );

  
}


template <typename TImage, typename TMaskImage>
void
MRFGaussianClassifierValidationApp<TImage,TMaskImage>
::InitializeOutputGenerator()
{
  m_OutputGenerator->SetPatientID( m_PatientID.c_str() );

  m_OutputGenerator->SetClassifiedImage( m_Classifier->GetClassifiedImage() );
  m_OutputGenerator->SetTruthImage( m_Parser->GetTruthImage() );

  m_OutputGenerator->SetStartSegSliceNumber( m_Parser->GetStartSegSliceNumber() );
  m_OutputGenerator->SetNumberOfSegSlices( m_Parser->GetNumberOfSegSlices() );

  m_OutputGenerator->SetTruthLabels( m_TruthLabels );

  m_OutputGenerator->SetOutputFileName( m_OutputFileName.c_str() );
  m_OutputGenerator->SetAppendOutputFile( m_AppendOutputFile );
} 


} // namespace itk

#endif
