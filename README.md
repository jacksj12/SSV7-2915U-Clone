# Soft Serve V7 🍦
The official Repo for Soft Serve V7 | VRC 2915U

This program uses the VEX Robotics V5 Platform, made with Purdue ACM SIGBots PROS, (Kernel 3.8.0, CLI 3.4.3).

Na but fr, every time I fix something I swear somthing else breaks. #spaghettiCodeGang

## TODO!
This is not important at all and I will most certainly update this as the project continues. (not a chance).
 - [ ] Add Joystick curving due to high speed. Allows for a significant amount of choice for the driver and the ability to change profile(s) at a fly. (opcontrol.cpp)
 - [ ] Add PID during endgame to balance on the middle bar. (opcontrol.cpp) & (pid.cpp)
 - [ ] Find a better way to do the PTO motor group situation. Its actually crap. (opcontrol.cpp)
 - [ ] Program some autons... 
 - [ ] Test  the internal encoders. Might come in handy for PID.
 - [ ] Some part detected to the Cata and different launch profiles? 
 - [ ] Custom auton selector? - Have one for both auton sides.
 - [ ] Permanent fix for the denominator / division by zero error (opcontrol.hpp)
 - [ ] Test PID!
 - [x] Chuck an IMU somewhere?
 - [x] Rewrite the PID to include an intergral and settling time.
 - [x] Finish the PID!!! (pid.cpp & pid.hpp)

## Versions
I might write something about this >.< 
## Why PROS
I decided mid-way through SSV6, that VEXCode, while completely applicable wasn't the best choice available. Actually, I had been meaning to migrate to PROS earlier due to the extensive "documentation" the PROS team have graciously made for us.  But due to my laptop being actually terrible I never used it because I thought the only way to use PROS was via the VSCode extension which really never worked. But once I got the CLI up and running, it was relatively smooth sailing. 

## My Workflow
I mainly operate between two machines, my desktop computer which I can open up an RDP pretty much anytime (but for whatever reason exception events 🙃). But majority of the work would be done through my Lenovo Ideapad-330s 15-AST, which was holding on for literally dear life. On this machine I would daily drive both Windows 10, and Fedora 37. Which meant I was constantly switching between the two. This meant I needed some sort of system which would make it easy to transfer contents between each other. 

Now I thought about creating a partition of my drive which was accessible to both operating systems. But for some reason I never went through with it. Mainly because I knew I'd forget to commit work down and then I'd be outdated on my desktop machine which caused major problems for other projects.  So, I decided to fully commit to committing... 

## Additional credits 

 - Awesome Auton selector 
	 - 
	 - [Vex Autonomous Selector](https://github.com/kunwarsahni01/Vex-Autonomous-Selector) Copyright (c) 2019 Kunwar Sahni - OSI under MIT license   
