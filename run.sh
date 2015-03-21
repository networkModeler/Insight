#!/bin/sh

echo "Checking for input and output directories..."
mkdir -p ./wc_input
mkdir -p ./wc_output

echo "Compiling..."
g++ -std=c++0x -O2 -o Insight -I. ./src/main.cpp ./src/WordCount.cpp ./src/FileList.cpp ./src/Parser.cpp ./src/WordMap.cpp ./src/Histogram.cpp ./src/Constants.cpp ./src/Test.cpp
echo "Done Compiling..."

Insight
echo ""
