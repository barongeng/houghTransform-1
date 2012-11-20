#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.4)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details
#-----------------------------------------------------------------------------
if(POLICY CMP0017)
  cmake_policy(SET CMP0017 OLD)
endif()

#-----------------------------------------------------------------------------
# Module name
#   - Usually identique to the directory name)
#   - You shouldn't call 'project(...)'. See SlicerConfig.cmake for more details.
#-----------------------------------------------------------------------------

set(MODULE_NAME houghTransformCLI)

#-----------------------------------------------------------------------------
# Prerequisites
#-----------------------------------------------------------------------------
if(NOT Slicer_SOURCE_DIR)
  find_package(Slicer REQUIRED)

  # Additional C/CXX flags - Should be defined before including Slicer_USE_FILE
  set(ADDITIONAL_C_FLAGS "" CACHE STRING "Additional ${EXTENSION_NAME} C Flags")
  set(ADDITIONAL_CXX_FLAGS "" CACHE STRING "Additional ${EXTENSION_NAME} CXX Flags")

  include(${Slicer_USE_FILE})

  set(EXTENSION_DEPENDS NA) # Specified as a space separated list or 'NA' if any
  set(EXTENSION_LICENSE_FILE ${Slicer_LICENSE_FILE})
  set(EXTENSION_README_FILE ${Slicer_README_FILE})
  set(EXTENSION_LICENSE_SHORT_DESCRIPTION ${Slicer_LICENSE_SHORT_DESCRIPTION})
  set(EXTENSION_CONTRIBUTORS "Guillaume Pernelle")
  set(EXTENSION_DESCRIPTION "Performs circle detection in volume using an Hough Transform")
  set(EXTENSION_CATEGORY "Segmentation")
  set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/4.2/Extensions/CircleDetectionHoughTransform")

  include(SlicerEnableExtensionTesting)
endif()

# Configure XML description
configure_file(
  ${EXTENSION_NAME}.xml
  ${CMAKE_CURRENT_BINARY_DIR}/${EXTENSION_NAME}.xml
  @ONLY
  )

#add_subdirectory(Logic)

set(cli_module_export_directive "Q_SLICER_QTMODULES_LOADABLEEXTENSIONTEMPLATE_EXPORT")

# Additional includes
set(cli_module_include_directories
  )

# Additional source files
set(cli_module_SRCS
  )


# Additional Target libraries
set(cli_module_target_libraries
    ${ITK_LIBRARIES}
    ${VTK_LIBRARIES}
)


#-----------------------------------------------------------------------------
# Build
#-----------------------------------------------------------------------------

SlicerMacroBuildCLI(
  NAME ${EXTENSION_NAME}
  #LOGO_HEADER ${Slicer_SOURCE_DIR}/Resources/NAMICLogo.h
  TARGET_LIBRARIES ${cli_module_target_libraries} ${ITK_LIBRARIES}
  INCLUDE_DIRECTORIES ${cli_module_include_directories} 
  INCLUDE_DIRECTORIES ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${cli_module_include_directories}
  ADDITIONAL_SRCS ${cli_module_SRCS}
  )

#-----------------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------------
# if(BUILD_TESTING)
#   add_subdirectory(Testing)
# endif()


#-----------------------------------------------------------------------------
# Packaging
#-----------------------------------------------------------------------------
if(NOT Slicer_SOURCE_DIR)
  include(${Slicer_EXTENSION_CPACK})
endif()


