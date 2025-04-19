#!/bin/bash

mkdir build
cd build

cmake ..
make

mv World_Sim_Cpp ..
cd ..

rm -rf build

./World_Sim_Cpp
