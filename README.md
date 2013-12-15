## Scope ##

This package contains a Vera plugin and associated Arduino Yun sketch. The Yun Sketch recognises IR commands from a Philips Television remote and sends those commands to the Vera plugin. You can use any remote you have lying around for this project.

## Features ##

An instance of the Vera plugin is created for each room in the house. These plugin instances are configured to make them aware of the AV devices and lights available in the room they control. They then automatically route commands to the correct device.

You can think of the Vera plugin as a composite virtual device. It means, for example, you only need one Play button and it will be routed to the device you are watching automatically.

Some examples of the functions:

* Route Volume, Mute, EQ commands to the AV receiver device
* Auto route Menu control and AV transport (play, pause, stop etc) to the correct media player device based on current AV receiver input
* Map some buttons to Vera scenes (like All Off)
* Provides lights up/down function that reads the current level of all lights in the room, then increases or decreases each light in fixed steps
* When sending a Play command, tries to read the current transport status of the media player device. If it is already playing then send pause instead. This allows you to use a remote having a single Play/Pause button, with devices that only support discrete Play and Pause commands, such as Sonos.

It relies on the device you want to control exposing methods that are compliant with the generic UPnP methods. 

e.g. 

urn:micasaverde-com:serviceId:MenuNavigation1/Back
urn:micasaverde-com:serviceId:MediaNavigation1/Stop
etc...

I use this with the following Vera plugins:

* Sonos
* XBMCRemote
* Onkyo
* AppleTV (IR)

I had to make some changes to the XBMCRemote plugin to support standard UPnP methods. You can find it along with my Apple TV IR plugin on github.com/pigsty


## Vera Usage ##

Create the device instance then restart Vera and reload the GUI. You should now be able to see and configure the following parameters:

###ReceiverDevice###

Give this the Vera id of your receiver. Mine uses the Onkyo plugin but it should work with any that supports reporting of the "Input" status field.

###AllOffScene###

Vera scene id that is triggered by the Power button on your remote

###Source1Device###

Vera device that controls your first AV input. e.g. Apple TV, XBMC, Sonos etc

###Source1Input###

The input your first source is connected to on your receiver. e.g. "CD", "10", "01" etc

###Source2Device###

See above 

###Source2Input###

See above

###Source3Device###

See above

###Source3Input###

See above

###RedScene###

Vera scene id to be run when the Red button is pressed 

###GreenScene###

Vera scene id to be run when the Green button is pressed 

###YellowScene###

Vera scene id to be run when the Yellow button is pressed 

###BlueScene###

Vera scene id to be run when the Blue button is pressed 

###LightsList###

Comma separated list of Vera lighting device ids for this room. e.g. 7,8,9


## Arduino Usage ##

The Arduino code works on the Yun. You could modify it to work on other models, using the Ethernet shield, quite easily. 

If you connect to it via Serial console you will see the codes echoed back at you when you press a button on your remote. In this way it is simple to learn new codes and update the sketch.

Note that my handling of the Philips toggle codes is a bit messy, using separate code definitions for both toggle variants. If you do not use a Philips remote then you do not need to match on two versions of every code.


## Limitations ##

Setting the number of AV inputs in the Vera plugin to a fixed value of 3 is quite lazy of me! This should really have been configurable.

## License ##

Copyright © 2013 Chris Birkinshaw

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/