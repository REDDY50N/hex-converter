#!/usr/bin/env bash

cmake -B build -S . -DBUILD_TESTING=OFF
cmake && cmake --build && ctest && cmake --install