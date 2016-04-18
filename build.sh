#!/bin/bash
cd ~/kbd/libTst/kbd-master
rm main.cpp
rm input-event-codes.h
rm kbd.h
rm kbd.c
rm kbd.o
rm main.o


cd ~/kbd/libTst
rm master.zip
wget https://github.com/tarasleonnardo/kbd/archive/master.zip
unzip master.zip
cd kbd-master

gcc -c main.cpp kbd.c 
gcc main.o kbd.o -o libtst

echo build done