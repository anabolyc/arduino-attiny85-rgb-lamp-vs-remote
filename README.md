# Arduino based RGB night lamp controlled by Atmel attiny85

## Motivation

* I want to create night lamp that changes color
* I need to be able to turn it on and off remotely (from my bed actually)
* I might want another version without remote to cheer my night trip to toilet
* I'm in love with Attiny85 mcu and I want to do something fun with it
* I want to practice in designing and assembling simple PCBs to gain experience for bigger projects

## Non-remote controlled version

I used [this article](http://www.technoblogy.com/show?LE0) for technical inspiration. 
Basically Attiny85 has 2 timers, providing 2 pwms each. Unfortunately pins for those pwms overlapping, so getting 4-th pwm is tricky. But 3 is enough for me, so that works quite ok.

I used smd led for this one (KY-009 module), but actually it is not brilliant, it is not very powerfull and colors are not very bright. 

![pcb front](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-21-14.08.59.jpg)
![pcb back](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-21-14.08.45.jpg)


## Remote-controlled version

I decided to assemble version that is possible to switch on and off remotely using RF433 radio module. Although module itself is building and working fine with Attiny85, it is using Timer0, therefore blocking 2 pwms. Timer0 works in CTC mode, so basically it is always 50% pwm (sort of) and i can only change frequency by adjusting radio channel speed. So trick here is
* RF library finds register OCRA value in combination with prescaler for which Timer0 overflow will happen once per bit sent, therefore I can find radio speed, so OCRA value will be close to 255 (I found it to be 254 actually, which is close enough)
* When i have Timer0 running in CTC mode from 0 to OCRA i can set OCRB register value to any value between 0 and OCRA and by hooking up interrupts to OCRB match and timer overflow I'm able to switch led on and off in PWM manner
* This trick not working brilliantly for small values, but for my case it is good enough

![pcb front](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-20-21.13.16.jpg)
![pcb back](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-20-21.13.37.jpg)
![panda lamp](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-20-21.35.14.jpg)
![led inplace](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-20-21.14.21.jpg)


## Remote control unit

I used capacitive sensor library, which turns any 2 pins into touch sensing button. So my button is just piese of aluminium foil covered by plastic tape. From my experience it works perfect!

![button](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-27-19.15.31.jpg)
![pcb front](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-26-18.45.56.jpg)
![pcb back](https://raw.githubusercontent.com/anabolyc/arduino-attiny85-rgb-lamp-vs-remote/master/images/2018-03-26-18.46.20.jpg)

## PCB and schematics

* [EasyEDA project - RGB lamp](https://easyeda.com/andrey.mal/00_rgb_lamp-959c0fd48be74b9ea60832f59a6886bc)
* [EasyEDA project - Remote control](https://easyeda.com/andrey.mal/03_panda_control_unit-81d20461bdbd45bd93433dddf72159b2)

## Links

* [Four PWM Outputs from the ATtiny85](http://www.technoblogy.com/show?LE0)
* [ATtiny PWM (similar to above)](http://matt16060936.blogspot.co.uk/2012/04/attiny-pwm.html)
* [AVR fuse calculator](http://www.engbedded.com/fusecalc)
* [Attiny core for Arduino](https://github.com/Coding-Badly/arduino-tiny)
* [Same on old google code site](https://code.google.com/archive/p/arduino-tiny/)
* [RF433 antenna recommendation](http://www.instructables.com/id/433-MHz-Coil-loaded-antenna/)
* [RF433 modules and library](http://www.instructables.com/id/RF-315433-MHz-Transmitter-receiver-Module-and-Ardu/)
* [Another RF433 library explanation](http://cosa-arduino.blogspot.de/2013/03/news-virtual-wire-interface.html)

## Video

Video is demonstrating color changes as well as remote control being tested

[Watch the video at Youtube](https://youtu.be/MXWmvgHrwHE)