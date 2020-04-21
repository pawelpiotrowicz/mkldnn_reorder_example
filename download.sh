#!/bin/bash

git clone https://github.com/intel/mkl-dnn.git
cd mkl-dnn
git checkout 589c09728e34d09d79106cba0211e93caf142d54
mkdir build
cd build
cmake .. && make -j10



