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
    label_port = yarp.Port()
    return label_port:open(prefix .. "/labels:o");
end

PortMonitor.update = function(thing)
	if thing:asBottle() == nil then
        print("event_monitor.lua: got wrong data type (expected type Bottle)")
        return thing
    end
    
	bt = thing:asBottle()
	if bt:size() == 2 and bt:get(0):asString() == "grasp" then
		label = yarp.Bottle()
		label:add(bt:get(1))
		label_port:write(label)
	end
	return thing
end

PortMonitor.destroy = function()
	label_port:close()
end
