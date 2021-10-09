#!/bin/bash
# please `sudo chmod u+x startup.sh` before execute this script

rm -rf build
cd scripts
rm -rf !app.py
cd ..
rm -f workers.cpp
rm *.sh