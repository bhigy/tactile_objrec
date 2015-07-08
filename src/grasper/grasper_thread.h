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

#include <yarp/os/Bottle.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/RpcClient.h>
#include <yarp/os/Thread.h>
  
class GrasperThread : public yarp::os::Thread
{
	public:
		enum ELaterality
		{
			Left,
			Right
		};
		enum EAction
		{
			Close,
			Open
		};
		
		static const std::string GRASP_ACTION;
		static const std::string ACK;
		static const std::string NACK;
		
		GrasperThread(yarp::os::RpcServer *cmd_port, yarp::os::RpcClient *action_port, yarp::os::Port *label_port, ELaterality laterality, double grasp_duration);   
		void run(); 
	   
	protected:
		static const std::string strLaterality[2];
		
		/* thread parameters */
		yarp::os::RpcServer	*cmd_port_;
		yarp::os::RpcClient *action_port_;
		yarp::os::Port		*label_port_;
		ELaterality 		laterality_;
		double 				grasp_duration_;
		
		yarp::os::Bottle* 	sendAction(EAction action);
		void 				sendLabel(std::string label);
};

#endif
