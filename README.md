# ❤️ Heart Beat to MIDI
You can use the code in this repo to make a device that measures your heart beats, sends them to your computer that's acting as a server and then, the computer processes the data and sends out MIDI signals with your prefered target scale to quantize and MIDI port and channel.

## What hardware tools does this need?
This project is coded on Pulsesensor heart beat sensor, ESP8266 wifi module, and Arduino Uno. Use [this link](https://pulsesensor.com/pages/code-and-guide) for learning about the wiring of the sensor and [this link](
https://medium.com/@cgrant/using-the-esp8266-wifi-module-with-arduino-uno-publishing-to-thingspeak-99fc77122e82
) for the wiring of the wifi module.

## What software tools does this need?
The server code is written in python. You should install `numpy` and `rtmidi` modules to run the server. The GUI is coded with `Tkinter`.

## TO DO LIST:
1) Connect UI to server