# Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Bertrand Higy
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

set(ENABLE_ICUB_SCRIPTS ON  CACHE BOOL "Install scripts for real robot")
set(ENABLE_SIM_SCRIPTS  OFF CACHE BOOL "Install scripts for simulator")

add_subdirectory(fingersModel)
add_subdirectory(grasper)
