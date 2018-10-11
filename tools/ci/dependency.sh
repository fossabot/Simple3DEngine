#!/bin/sh
apt-get update -qq
apt-get install -qq -y wget
apt-get install -qq -y gnupg
apt-get install -qq -y gnupg2
apt-get install -qq -y gnupg1

 wget http://blog.anantshri.info/content/uploads/2010/09/add-apt-repository.sh.txt
 mv add-apt-repository.sh.txt add-apt-repository
 chmod +x add-apt-repository
 ./add-apt-repository  'ppa:zoogie/sdl2-snapshots'
 ./add-apt-repository ppa:ubuntu-toolchain-r/test 
 ./add-apt-repository ppa:boost-latest/ppa 
 ./add-apt-repository 'ppa:dartsim/ppa'
 apt-get update -qq
 apt-get install -qq -y cmake
 apt-get install -qq -y ninja-build
 apt-get install -qq -y build-essential
 apt-get install -qq -y libglew-dev
 apt-get install -qq -y libsdl2-dev
 apt-get install -qq -y libsdl2-image-dev
 apt-get install -qq -y libassimp-dev
 apt-get install -qq -y libglm-dev
 apt-get install -qq -y lcov
 apt-get install -qq -y gcov
 apt-get install -qq -y clang
 apt-get install -qq -y meson
 apt-get install -qq -y googletest
