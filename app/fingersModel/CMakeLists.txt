# Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Bertrand Higy
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

set(appname fingersModel)

file(GLOB conf    ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini)
       
### create a single target that installs all applications at once
yarp_install(FILES ${conf} 	  	  DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${appname})
