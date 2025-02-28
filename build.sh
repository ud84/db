#!/bin/sh

cmake CMakeLists.txt
make -j 4
echo "db ready in src/"
