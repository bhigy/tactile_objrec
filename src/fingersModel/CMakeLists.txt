# Copyright: (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
# Authors: Bertrand Higy
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME fingersModel)
project(${PROJECTNAME})

find_package(OpenCV)
find_package(ICUB)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
  
include_directories(${YARP_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${ICUB_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

set(folder_source main.cpp)
#source_group("Source Files" FILES ${folder_source})
add_executable(${PROJECTNAME} ${folder_source} fingers_model_module.cpp fingers_model_thread.cpp)

target_link_libraries(${PROJECTNAME} ${OpenCV_LIBRARIES} ${YARP_LIBRARIES} perceptiveModels)

install(TARGETS ${PROJECTNAME} DESTINATION bin)

