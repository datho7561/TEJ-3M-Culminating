
# TEJ 3M Computer Engineering Culminating Project

This is the source code for the Arduino for my TEJ 3M grade 11 highschool
Computer Engineering course.

Please do not judge this code, I wrote it quite some time ago and have since
had more formal experience with C and C++.

## About the Project

My project was a digital alarm clock. It had a 4 digit 7 segment display which I
drived with one seven segment decoder. It used persistence of vision to keep
the display running. To keep time, it used the built-in Arduino clock. From
what I remember this meant that it would lose a lot of time. I think I may have
hard coded the minute delay slightly shorter than usual so that it would match
better to actual time. It also featured an alarm that would play one of three
selectable tunes when ringing. The time and alarm could be selected using a
button and a potentiometer.

## How I Found the Source

This is a mildly interesting story. A while ago I had the idea to upload this
project to Github to demonstrate that I had (some (very limited)) experience
with C. I went to download the code and circuit diagram from 123D Circuits
(an online circuit simulator by Autocad), only to discover that the website no
longer existed. I assumed that the project was completely lost, and forgot about
it. Recently, I got a message from Dropbox saying that all my data would be
deleted unless I logged in. So, I logged in, and low and behold there was a
zipped folder containing the source code and the below README.

Here is the unmodified source code and the original README for your
entertainment.

## Original README From Project Submission

SEVEN SEGMENT DIGITAL CLOCK
by David Thompson

FEATURES:
-> Keeps track of and displays time
-> 24h
-> Alarm with 3 selectable alarm tunes (See tune names in code)
-> Can update time and alarm time

OPERATION:

-> When the clock is set up and the code is loaded, it will start at a time of 6:45 (AM),
with the alarm set for 6:45 (am) and going off immediately. By default it will play the second tune.

-> To edit the time, alarm time, and selected tune, press the button.
Turn the potentiometer to modify the flashing digit(s), and press the button to confirm your selection

	- After one press, the minutes digits will be edited
	- After two presses, the minutes tens will be edited
	- After three presses, the hours digits will be edited
	- After four presses, the hours tens will be edited
	- After five presses, the alarm minutes will be edited (it can be edited within 15 minutes)
	- After six presses, the alarm hours will be edited
	- After seven presses, the alarm tune will be edited
	- After eight presses, the time will set itself to  a number smaller than 24 if the input time is larger than 24,
		and timekeeping will return to normal

-> Please note that the alarm will not go off during the editing stages.

WIRING DIAGRAM:

https://123d.circuits.io/circuits/2207089-culminating-project-11-v2-0/embed#breadboard

