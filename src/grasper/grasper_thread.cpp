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

#include "grasper_thread.h"

using namespace std;
using namespace yarp::os;

const char GrasperThread::DELIMITER = ' ';

GrasperThread::GrasperThread(RpcServer *rpc_port, string *default_answer,  Property *dictionary, double delay)
	: rpc_port_(rpc_port), default_answer_(default_answer), dictionary_(dictionary), delay_(delay)
{
}

void GrasperThread::run()
{
	while (!isStopping())
	{
		cout << "Waiting for a message..." << endl;
		Bottle request, *reply;
		rpc_port_->read(request, true);
		cout << "Message: " << request.toString() << endl;
		Time::delay(delay_);
		if (dictionary_ != NULL)
		{
			Value answer = dictionary_->find(request.toString());
			if (answer.isNull())
			{
				reply = buildBottle(*default_answer_);
			}
			else
			{
				reply = buildBottle(answer.asString());
			}
		}
		else
		{
			reply = buildBottle(*default_answer_);
		}
		cout << "Reply: >>" << reply->toString() << endl;
		rpc_port_->reply(*reply);
		delete reply;
	}
}

Bottle* GrasperThread::buildBottle(string msg)
{
	Bottle *bottle = new Bottle();
	int pos;
	string token;
	while ((pos = msg.find(DELIMITER)) != string::npos) {
		token = msg.substr(0, pos);
		addValue(*bottle, token);
		msg.erase(0, pos + 1);
	}
	addValue(*bottle, msg);
	return bottle;
}

void GrasperThread::addValue(Bottle& b, const string& value)
{
	char* p;
	long converted = strtol(value.c_str(), &p, 10);
	if (*p) {
		b.addString(value);
	}
	else {
		b.addInt(converted);
	}
}
