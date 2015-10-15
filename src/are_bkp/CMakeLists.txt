# Copyright: 2011 RobotCub Consortium
# Author: Carlo Ciliberto
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

set(PROJECTNAME are_bkp	)
project(${PROJECTNAME})

find_package(YARP REQUIRED)
find_package(ICUB REQUIRED)
find_package(OpenCV REQUIRED)

set(folder_source main.cpp
                  utils.cpp
                  MotorThread.cpp
                  VisuoThread.cpp)

set(folder_header utils.h 
                  VisuoThread.h
                  MotorThread.h)
                  
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(${PROJECT_SOURCE_DIR}/include ${YARP_INCLUDE_DIRS}
                    ${iKin_INCLUDE_DIRS} ${actionPrimitives_INCLUDE_DIRS}
                    ${OpenCV_INCLUDE_DIRS} ${GSL_INCLUDE_DIRS})

add_executable(${PROJECTNAME} ${folder_header} ${folder_source})
target_link_libraries(${PROJECTNAME} iKin actionPrimitives ${OpenCV_LIBRARIES}
                      ${GSL_LIBRARIES} ${YARP_LIBRARIES})

install(TARGETS ${PROJECTNAME} DESTINATION bin)

#target_link_libraries( main ${OpenCV_LIBS} ) 
