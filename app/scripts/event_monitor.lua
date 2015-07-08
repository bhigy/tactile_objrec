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
PortMonitor.create = function(options)
	if options:find("sender_side"):asInt() == 1 then
		prefix = options:find("source"):asString()
	else
		prefix = options:find("destination"):asString()
	end
    event_port = yarp.Port()
    return event_port:open(prefix .. "events:o");
end

PortMonitor.update = function(thing)
	if thing:asBottle() == nil then
        print("event_monitor.lua: got wrong data type (expected type Bottle)")
        return thing
    end
    
	bt = thing:asBottle()
	event = yarp.Bottle()
	event:addString("request")
	event:append(bt)
	event_port:write(event)
	return thing
end

-- update_reply is called when the ports receives a reply from an RPC connection
-- @param thing The Things abstract data type
-- @return Things
PortMonitor.update_reply = function(thing)
    if thing:asBottle() == nil then
        print("event_monitor.lua: got wrong data type (expected type Bottle)")
        return thing
    end

    bt = thing:asBottle()
    event = yarp.Bottle()
    event:addString("reply")
	event:append(bt)
	event_port:write(event)
    return thing
end

PortMonitor.destroy = function()
	event_port:close()
end
