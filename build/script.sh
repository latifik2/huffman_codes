#!/bin/bash

g++ ../source/* ../lib/*.cpp -o App
./App $1 $2
