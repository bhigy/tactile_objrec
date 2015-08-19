#ifndef FINGERS_MODEL_MODULE_H
#define FINGERS_MODEL_MODULE_H

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

#include <yarp/os/Port.h>
#include <yarp/os/RFModule.h>

#include "fingers_model_thread.h"

class FingersModelModule: public yarp::os::RFModule
{
	public:
	   
	   bool configure(yarp::os::ResourceFinder &rf); // configure all the module parameters and return true if successful
	   bool interruptModule();                       // interrupt, e.g., the ports 
	   bool close();                                 // close and shut down the module
	   bool respond();
	   bool updateModule();
	   
   private:
	   /* module parameters */
	   double	   period_;
	   std::string module_name_;
	   std::string springy_port_name_;
	   std::string tactile_port_name_;
	   std::string model_config_filename_;
	   	 
	   /* class variables */
	   yarp::os::Port 		springy_port_;
	   yarp::os::Port 		tactile_port_;
	   FingersModelThread 	*thread_;
};

#endif
