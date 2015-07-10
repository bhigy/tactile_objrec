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

#include <cstdlib>

#include <yarp/os/Bottle.h>
#include <yarp/os/Time.h>

#include "fingers_model_thread.h"

using namespace std;
using namespace yarp::os;

FingersModelThread::FingersModelThread(int period, Port *springy_port)
	: RateThread(period), springy_port_(springy_port)
{
	Property p;
	p.fromConfigFile("grasp_model_left.ini");
	sf_model_.fromProperty(p);
    p.put("finger", "all_parallel");
	sf_model_.calibrate(p);
}

void FingersModelThread::run()
{
	Value out;
	sf_model_.getOutput(out);
	Bottle b;
	b.add(out);
	springy_port_->write(b);
}

