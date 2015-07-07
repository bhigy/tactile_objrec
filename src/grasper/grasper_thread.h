#ifndef GRASPER_THREAD_H
#define GRASPER_THREAD_H

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

#include <string>
#include <yarp/os/Bottle.h>
#include <yarp/os/Property.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/Thread.h>
  
class GrasperThread : public yarp::os::Thread
{
	public:
		static const char DELIMITER;
		
		GrasperThread(yarp::os::RpcServer *rpc_port, std::string *default_answer,  yarp::os::Property *dictionary, double delay);   
		void run(); 
	   
	protected:
		/* thread parameters */
		std::string 		*default_answer_;
		yarp::os::Property 	*dictionary_;
		yarp::os::RpcServer *rpc_port_;
		double 				delay_;
		
		yarp::os::Bottle* buildBottle(std::string msg);
		void addValue(yarp::os::Bottle& b, const std::string& value);
};

#endif
