#!/bin/bash
# please `sudo chmod u+x startup.sh` before execute this script
mkdir build
cd build
cmake ..
make -j2
./example ../scripts/app.py -s ../scripts/background_run.py ../scripts/workers.py