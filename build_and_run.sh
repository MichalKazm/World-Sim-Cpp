#!/bin/bash

mkdir -p build
cd build

cmake ..
make

./World_Sim_Cpp
