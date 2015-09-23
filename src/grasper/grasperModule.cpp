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

#include "grasperModule.h"

using namespace std;
using namespace yarp::os;

bool GrasperModule::configure(ResourceFinder &rf)
{    
	moduleName_ = rf.check("name", Value("grasper"), "module name (string)").asString();
	setName(moduleName_.c_str());

	// get the name of the input and output ports, automatically prefixing the module name by using getName()
	cmdPortName_ = "/";
	cmdPortName_ += getName(rf.check("cmdPort", Value("/cmd:io"), "Command port (string)").asString());
	actionPortName_ = "/";
	actionPortName_ += getName(rf.check("actionPort", Value("/actions:io"), "Action port (string)").asString());
	labelPortName_ = "/";
	labelPortName_ += getName(rf.check("labelPort", Value("/labels:o"), "Label port (string)").asString());
	wbdPortName_ = "/";
	wbdPortName_ += getName(rf.check("wbdPort", Value("/wbd:io"), "Label port (string)").asString());
	 
	// open ports
	if (!cmdPort_.open(cmdPortName_.c_str())) {
		cerr << getName() << ": unable to open port " << cmdPortName_ << endl;
		return false;
	}
	if (!actionPort_.open(actionPortName_.c_str())) {
		cerr << getName() << ": unable to open port " << actionPortName_ << endl;
		return false;
	}
	if (!labelPort_.open(labelPortName_.c_str())) {
		cerr << getName() << ": unable to open port " << labelPortName_ << endl;
		return false;
	}
	if (!wbdPort_.open(wbdPortName_.c_str())) {
		cerr << getName() << ": unable to open port " << wbdPortName_ << endl;
		return false;
	}
	
	string laterality = rf.check("laterality", Value("left"), "Laterality (string)").asString();
	if (laterality == "right")
		laterality_ = GrasperThread::Right;
	else
		laterality_ = GrasperThread::Left;
		
	graspDuration_ = rf.check("graspDuration", Value("0"), "Grasp duration (double)").asDouble();
   	// create the thread and pass pointers to the module parameters
	thread_ = new GrasperThread(&cmdPort_, &actionPort_, &labelPort_, &wbdPort_, laterality_, graspDuration_);
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
	cmdPort_.interrupt();
	actionPort_.interrupt();
	labelPort_.interrupt();
	return true;
}

bool GrasperModule::close()
{
	/* stop the thread */
	thread_->stop();

	cmdPort_.close();
	actionPort_.close();
	labelPort_.close();
	return true;
}

