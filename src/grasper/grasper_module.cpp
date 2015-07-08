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

#include "grasper_module.h"

using namespace std;
using namespace yarp::os;

bool GrasperModule::configure(ResourceFinder &rf)
{    
	module_name_ = rf.check("name", Value("grasper"), "module name (string)").asString();
	setName(module_name_.c_str());

	// get the name of the input and output ports, automatically prefixing the module name by using getName()
	cmd_port_name_ = "/";
	cmd_port_name_ += getName(rf.check("cmd_port", Value("/cmd:io"), "Command port (string)").asString());
	action_port_name_ = "/";
	action_port_name_ += getName(rf.check("action_port", Value("/actions:io"), "Action port (string)").asString());
	label_port_name_ = "/";
	label_port_name_ += getName(rf.check("label_port", Value("/labels:o"), "Label port (string)").asString());
	 
	// open ports
	if (!cmd_port_.open(cmd_port_name_.c_str())) {
		cerr << getName() << ": unable to open port " << cmd_port_name_ << endl;
		return false;
	}
	if (!action_port_.open(action_port_name_.c_str())) {
		cerr << getName() << ": unable to open port " << action_port_name_ << endl;
		return false;
	}
	if (!label_port_.open(label_port_name_.c_str())) {
		cerr << getName() << ": unable to open port " << label_port_name_ << endl;
		return false;
	}
	
	string laterality = rf.check("laterality", Value("left"), "Laterality (string)").asString();
	if (laterality == "right")
		laterality_ = GrasperThread::Right;
	else
		laterality_ = GrasperThread::Left;
		
	grasp_duration_ = rf.check("grasp_duration", Value("0"), "Grasp duration (double)").asDouble();
   	// create the thread and pass pointers to the module parameters
	thread_ = new GrasperThread(&cmd_port_, &action_port_, &label_port_, laterality_, grasp_duration_);
	// now start the thread to do the work
	thread_->start(); // this calls threadInit() and it if returns true, it then calls run()

   	return true ;
}

bool GrasperModule::updateModule()
{
	return true;
}

bool GrasperModule::interruptModule()
{
	cmd_port_.interrupt();
	action_port_.interrupt();
	label_port_.interrupt();
	return true;
}

bool GrasperModule::close()
{
	/* stop the thread */
	thread_->stop();

	cmd_port_.close();
	action_port_.close();
	label_port_.close();
	return true;
}

