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

#include "grasperThread.h"

using namespace std;
using namespace yarp::os;

const string GrasperThread::GRASP_ACTION 	= "grasp";
const string GrasperThread::ACK 			= "ACK";
const string GrasperThread::NACK 			= "NACK";

const string GrasperThread::strLaterality[] = {"left", "right"};

GrasperThread::GrasperThread(RpcServer *cmdPort, RpcClient *actionPort, Port *labelPort, ELaterality laterality, double graspDuration)
	: cmdPort_(cmdPort), actionPort_(actionPort), labelPort_(labelPort), laterality_(laterality), graspDuration_(graspDuration)
{
}

void GrasperThread::run()
{
	while (!isStopping())
	{
		cout << "Waiting for a message..." << endl;
		Bottle request, reply;
		cmdPort_->read(request, true);
		cout << "Message: " << request.toString() << endl;
		
		if (request.size() != 2 || request.get(0).asString() != GRASP_ACTION)
		{
			reply.addString(NACK);
		}
		else
		{
			sendLabel(request.get(1).asString());
			sendAction(Close);
			Time::delay(graspDuration_);
			sendAction(Open);
			reply.addString(ACK);
		}	
		cout << "Reply: >>" << reply.toString() << endl;
		cmdPort_->reply(reply);
	}
}

Bottle* GrasperThread::sendAction(EAction action)
{
	Bottle cmd, *response;
	response = new Bottle;
	
	switch(action) {
		case Close:
			cmd.addString("close");
			cmd.addString(strLaterality[laterality_]);
			break;
		case Open:
			cmd.addString("home");
			cmd.addString("hands");
			break;
	}
	actionPort_->write(cmd, *response);
	
	return response;
}

void GrasperThread::sendLabel(string label)
{
	Bottle b;
	b.addString(label);
	labelPort_->write(b);
}

