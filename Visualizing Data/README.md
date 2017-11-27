README for Visualizing Data
Authors: Ben Jukus and Ryan Drexel

***CONTENTS***

-Drivers used
-RGB LED
-LCD Display
-Implementation

============
|LCD Driver|
============
The LCD Driver written by Russell Trafford was used to complete this lab. See the respective README for more information.

=========
|RGB LED|
=========
In this part of the project, the ADC was used and it's value was utilized to change the color of an RGB LED. A thermistor was the sensor chose
for this assignment, and the LED changes color with respect to the temperature (blue in cold temperature, pruple below room temp., red at room temp., orange above room temp. yellow in hot temp.

To do this, all that had to be done with the ADC reading is change the pulse width of R, G, and B with simple math based on the temperature range. The chart below shows the gist of the 
LEDs' change
__________________________________________________________________
LED brightness approximation with respect to temp. approximation  |
								  |
	40*F	55*F	70*F	85*F	100*F			  |
  -------------------------------------------			  |
R| 	0%	100%	100%	75%	100%			  |			
G|	0%	0%	0%	50%	100%			  |
B|	100%	100%	0%	0%	0%			  |
__________________________________________________________________|

=============
|LCD Display|
=============
This portion of the lab made use of the MSP430FR6989's LCD display in order to produce a human-legible output for the reading of a temperature sensor.

===============
|Implementaion|
===============
This code can be utilized and implemented on a variety of different projects/applications. The code is compatible with virtually any sensor with an analog output
as long as the sensor fits the specifications of the MSP430. Only minor calculations need to be changed in order to read any sensor with this code.
