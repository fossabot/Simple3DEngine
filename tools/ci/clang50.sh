#!/bin/sh

export CC=clang-5.0
export CXX=clang++-5.0

meson -Db_coverage=true build && cd build && ninja
