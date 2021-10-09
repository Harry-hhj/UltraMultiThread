#!/bin/bash
# please `sudo chmod u+x startup.sh` before execute this script

rm -rf build
cd scripts
rm -rf *
cd ..
rm -f workers.cpp
rm *.sh