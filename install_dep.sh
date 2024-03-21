#!/bin/sh

apt-get install -y build-essential libz-dev

if ! [ -f ./build ]; then
    mkdir build
fi
