#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
sudo ldconfig

if [ "$1" == "debug" ]; then
    make debug
else
    make run
fi
