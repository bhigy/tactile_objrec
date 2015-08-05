# Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Bertrand Higy
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
cmake_minimum_required(VERSION 2.8)

set(appname tactileObjrec)

set(ENABLE_ICUB_SCRIPTS ON  CACHE BOOL "Install scripts for real robot")
set(ENABLE_SIM_SCRIPTS  OFF CACHE BOOL "Install scripts for simulator")

file(GLOB conf    ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini)
file(GLOB lua     ${CMAKE_CURRENT_SOURCE_DIR}/lua/*.lua)

if(ENABLE_ICUB_SCRIPTS)
	file(GLOB icubScripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/icub/*.xml)
endif(ENABLE_ICUB_SCRIPTS)
if(ENABLE_SIM_SCRIPTS)
	file(GLOB simScripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/sim/*.xml)
endif(ENABLE_SIM_SCRIPTS)
       
### create a single target that installs all applications at once
yarp_install(FILES ${conf} 	  	  DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${lua} 	  	  DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${icubScripts} DESTINATION ${ICUBCONTRIB_APPLICATIONS_INSTALL_DIR})
yarp_install(FILES ${simScripts}  DESTINATION ${ICUBCONTRIB_APPLICATIONS_INSTALL_DIR})
