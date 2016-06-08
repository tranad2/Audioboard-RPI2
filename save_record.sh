#!/bin/bash

X=$(date -d "today" +"%Y%m%d%H%M")
arecord -D plughw:1,0 -f dat -vv /home/pi/Desktop/Final_Project/audioboard/ARecord/recordings/${X}_Input.wav

echo "Uploading to DropBox\n"
./dropbox_uploader.sh upload /home/pi/Desktop/Final_Project/audioboard/ARecord/recordings/${X}_Input.wav ${X}_Input.wav