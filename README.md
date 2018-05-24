# Audioboard-RPI2

## Introduction

The goal of the project is to create a remote control soundboard with a record and
upload feature. Using an IR remote, the user can press one of the buttons to make the
speaker output a preprogrammed audio file. The user also has the ability to record
audio through the microphone by pressing a specific button on the remote. The
recording is then uploaded to the application’s Dropbox when the program is exited.

![How it works](https://i.imgur.com/8ozKtAJ.png)

## Requirements

IR Remote & IR Receiver
- Used to send and receive button presses to interact with the RPi’s GPIO
Raspberry Pi 2
- The backbone of the project
Speakers
- Used to output the sound files
Microphone
- Used to record audio input
Dropbox
- Cloud storage service used to upload recorded files

## Resources

IR Remote Tutorial:
- http://ozzmaker.com/how-to-control-the-gpio-on-a-raspberry-pi-with-an-ir-remote/
DropboxUploader:
- https://github.com/andreafabrizi/Dropbox-Uploader
mpg123 MPEG Audio Player:
- https://www.mpg123.de/
ALSA:
- www.alsaproject.org/

### About
Developed by Alex Tran and Michael Herrera.
