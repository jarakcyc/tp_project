#!/bin/bash

mkdir tmp
cd tmp

cmake .. -DBUILD_TESTS=ON
make

#./tests