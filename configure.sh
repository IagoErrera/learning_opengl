#!/bin/bash
mkdir -p build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
