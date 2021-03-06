#---------------------------------------------------------------------------
# Get and build itk

set( ITK_TAG "v4.3.0" )
ExternalProject_Add( ITK
  GIT_REPOSITORY "${git_protocol}://itk.org/ITK.git"
  GIT_TAG "${ITK_TAG}"
  SOURCE_DIR ITK
  BINARY_DIR ITK-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DITK_BUILD_ALL_MODULES:BOOL=ON
    -DITK_LEGACY_REMOVE:BOOL=OFF
    -DITKV3_COMPATIBILITY:BOOL=ON
  INSTALL_COMMAND ""
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)
