--
-- Copyright (C) 2015 iCub Facility
-- Authors: Bertrand HIGY
-- CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
--
 
-- loading lua-yarp binding library
require("yarp")

--
-- create is called when the port monitor is created 
-- @return Boolean
--
PortMonitor.create = function()
    -- set the constraint here 
    -- Notice that we never want to receive image data from
    -- this connection (/Selector/grabber)
    --PortMonitor.setEvent("e_dump_activated")
    PortMonitor.setConstraint("false")       
    dumpActivated = false
    giveInitiated = false
    return true;
end

-- 
-- destroy is called when port monitor is destroyed
--
PortMonitor.destroy = function()
    -- unset the all events on destroy
    PortMonitor.unsetEvent("e_dump_activated")
end

--
-- accept is called when the port receives new data
-- @param thing The Things abstract data type
-- @return Boolean
-- if false is returned, the data will be ignored 
-- and update() will never be called
PortMonitor.accept = function(thing)
	bt = thing:asBottle()
    if dumpActivated == true then
    	if giveInitiated == false then
			if  bt:size() == 2 and bt:get(0):asString() == "request"
			and string.sub(bt:get(1):asString(), 1, 4) == "give" then
		    	giveInitiated = true
		   	end
       	else
       		if  bt:size() == 2 and bt:get(0):asString() == "reply" then
       			dumpActivated = false
		    	giveInitiated = false
		    	PortMonitor.unsetEvent("e_dump_activated")
		   	end
        	
        end
    else
    	if  bt:size() == 2 and bt:get(0):asString() == "request" 
    	and string.sub(bt:get(1):asString(), 1, 5) == "expect" then
    		dumpActivated = true
        	PortMonitor.setEvent("e_dump_activated")
	   	end
    end
    return true
end
