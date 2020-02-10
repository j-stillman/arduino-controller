# arduino-controller
Custom-made controller that converts button inputs to key presses.

I made this controller as my final project for ART 150 - Intro to New Media Arts. It is a little system of Arduino and Processing sketches that work together to operate a game controller. The controller itself I had modeled and 3D printed. Those STL files are also included.

The Arduino takes in input from buttons and a joystick that are connected to the Arduino. These inputs are translated into key presses, which cause the character in the game to run and jump. The Arduino sketch also reads the serial port and turns on lights whenever you complete an objective in the game. Since this game was made in GameMaker: Studio, which isn't compatible with Arduino, I had to work around this by using Processing.

The Processing sketch, ledDriver.pde, periodically reads from a local text file led.txt, which is manipulated by GameMaker. This file is just 3 bits, each one corresponding to an LED on the controller. Any time it notices a change from 0 to 1 or vice versa, it sends the signal to the Arduino to turn the light on or off.

Demonstration video: https://www.youtube.com/watch?v=IrtBmlKMP_o
The game, ArrJiiBii, can be found here: https://burlapthemonkey.itch.io/arrjiibii
