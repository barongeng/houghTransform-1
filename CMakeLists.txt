cmake_minimum_required(VERSION 2.8.9)

project(houghTransformCLI)

#-----------------------------------------------------------------------------
set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/4.2/Extensions/CircleDetectionHoughTransform")
set(EXTENSION_CONTRIBUTORS "Guillaume Pernelle")
set(EXTENSION_CATEGORY "Segmentation")
set(EXTENSION_DESCRIPTION "Performs circle detection in volume using an Hough Transform")
set(EXTENSION_ICONURL "http://www.slicer.org/slicerWiki/images/6/6e/HtIcon.png")
set(EXTENSION_SCREENSHOTURLS "http://www.slicer.org/slicerWiki/images/7/70/CirclesDetectionHoughTransform-result.png")

#-----------------------------------------------------------------------------
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
set(MODULE_NAME ${PROJECT_NAME})

#-----------------------------------------------------------------------------
set(MODULE_TARGET_LIBRARIES
  ${ITK_LIBRARIES} ${VTK_LIBRARIES}
  )

set(MODULE_ADDITIONAL_SRCS
  itkHoughTransformRadialVotingImageFilter.h
  itkHoughTransformRadialVotingImageFilter.txx
  utilitiesIO.h
  utilitiesIO.hxx
  utilitiesImage.h
  utilitiesImage.hxx
  )

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  ADDITIONAL_SRCS ${MODULE_ADDITIONAL_SRCS}
  )

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})

