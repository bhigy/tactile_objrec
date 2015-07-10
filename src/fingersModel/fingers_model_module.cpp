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

#include "fingers_model_module.h"

using namespace std;
using namespace yarp::os;

bool FingersModelModule::configure(ResourceFinder &rf)
{    
	module_name_ = rf.check("name", Value("fingersModel"), "module name (string)").asString();
	setName(module_name_.c_str());

	// get the name of the input and output ports, automatically prefixing the module name by using getName()
	springy_port_name_ = "/";
	springy_port_name_ += getName(rf.check("springy_port", Value("/springy:o"), "Springy port (string)").asString());
	 
	// open ports
	if (!springy_port_.open(springy_port_name_.c_str())) {
		cerr << getName() << ": unable to open port " << springy_port_name_ << endl;
		return false;
	}
	
   	// create the thread and pass pointers to the module parameters
   	int period = 1 / 30 * 1000;
	thread_ = new FingersModelThread(period, &springy_port_);
	// now start the thread to do the work
	thread_->start(); // this calls threadInit() and it if returns true, it then calls run()

   	return true ;
}

bool FingersModelModule::updateModule()
{
	return true;
}

bool FingersModelModule::interruptModule()
{
	springy_port_.interrupt();
	return true;
}

bool FingersModelModule::close()
{
	/* stop the thread */
	thread_->stop();

	springy_port_.close();
	return true;
}

