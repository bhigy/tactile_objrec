# Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Bertrand Higy
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
cmake_minimum_required(VERSION 2.8)

set(appname tactileObjrec)

file(GLOB scripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*.xml)
file(GLOB conf    ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini)
file(GLOB lua     ${CMAKE_CURRENT_SOURCE_DIR}/lua/*.lua)
       
### create a single target that installs all applications at once
MESSAGE(${ICUBCONTRIB_CONTEXTS_INSTALL_DIR})
yarp_install(FILES ${conf} 	  DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${lua} 	  DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_APPLICATIONS_INSTALL_DIR})
