#!/usr/bin/env bash

g++ -o a -Wall -Wextra -Wpedantic -g -std=c++17 -fsanitize=address,undefined $@
