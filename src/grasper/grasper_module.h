#ifndef GRASPER_MODULE_H
#define GRASPER_MODULE_H

/* 
 * Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Bertand Higy
 * email:  bertrand.higy@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include <yarp/os/RpcServer.h>
#include <yarp/os/RpcClient.h>
#include <yarp/os/RFModule.h>

#include "grasper_thread.h"

class GrasperModule: public yarp::os::RFModule
{
	public:
	   bool configure(yarp::os::ResourceFinder &rf); // configure all the module parameters and return true if successful
	   bool interruptModule();                       // interrupt, e.g., the ports 
	   bool close();                                 // close and shut down the module
	   bool respond();
	   bool updateModule();
	   
   private:
	   /* module parameters */
	   std::string 					module_name_;
	   std::string 					cmd_port_name_;
	   std::string 					action_port_name_;
	   std::string 					label_port_name_;
	   GrasperThread::ELaterality 	laterality_;
	   double						grasp_duration_;
	 
	   /* class variables */
	   yarp::os::RpcServer 	cmd_port_;
	   yarp::os::RpcClient 	action_port_;
	   yarp::os::Port		label_port_;
	   GrasperThread 		*thread_;
};

#endif
