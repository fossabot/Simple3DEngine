#!/bin/sh
export CC=gcc
export CXX=g++

meson -Db_coverage=true build && cd build && ninja
