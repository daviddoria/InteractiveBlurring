cmake_minimum_required(VERSION 2.6)

PROJECT(InteractiveBlurring)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

if(UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif(UNIX)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

FIND_PACKAGE(ITK REQUIRED ITKCommon ITKIOImageBase ITKTestKernel
             ITKImageIntensity ITKImageFeature ITKMathematicalMorphology
             ITKBinaryMathematicalMorphology ITKDistanceMap)
INCLUDE(${ITK_USE_FILE})

if(NOT TARGET Widgets)
  add_subdirectory(Widgets)
  include_directories(${Widgets_includes})
endif()

if(NOT TARGET ITKQtHelpers)
  add_subdirectory(ITKQtHelpers)
  include_directories(${ITKQtHelpers_includes})
endif()

QT4_WRAP_UI(UISrcs InteractiveBlurringWidget.ui)
QT4_WRAP_CPP(MOCSrcs InteractiveBlurringWidget.h)

ADD_EXECUTABLE(InteractiveBlurring InteractiveBlurring.cpp InteractiveBlurringWidget.cpp
${UISrcs} ${MOCSrcs})
TARGET_LINK_LIBRARIES(InteractiveBlurring ${VTK_LIBRARIES}
${ITK_LIBRARIES} CustomWidgets)
