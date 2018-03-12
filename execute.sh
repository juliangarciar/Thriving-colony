#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
sudo ldconfig
echo "Ejecutando..."
./bin/ThrivingColony