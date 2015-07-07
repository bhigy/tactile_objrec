#ifndef FINGERS_MODEL_THREAD_H
#define FINGERS_MODEL_THREAD_H

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
#include <yarp/os/Thread.h>
#include <iCub/perception/springyFingers.h>
  
class FingersModelThread : public yarp::os::Thread
{
	public:
		
		FingersModelThread(yarp::os::Port *springy_port, yarp::os::Port *tactile_port);   
		void run(); 
	   
	protected:
		/* thread parameters */
		yarp::os::Port 							*springy_port_;
		yarp::os::Port 							*tactile_port_;
		iCub::perception::SpringyFingersModel 	sf_model_;
};

#endif
