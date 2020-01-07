#!/bin/bash

unamestr=`uname -s`
if [[ ${unamestr} == "Darwin" ]] ; then
    preload="DYLD_INSERT_LIBRARIES"
    suffix="dylib"
else
    preload="LD_PRELOAD"
    suffix="so"
fi

echo "##################### Static, no tool linked ####################"
./program_static_notool

echo "##################### Static, tools linked   ####################"
./program_static

echo "##################### Dynamic, no tool linked ###################"
./program_dynamic_notool

echo "##################### Dynamic, tools linked   ###################"
./program_dynamic

echo "##################### Dynamic, one tool preload #################"
export ${preload}=./libtool1.${suffix}
./program_dynamic_notool

echo "##################### Dynamic, two tool preload #################"
export ${preload}=./libtool1.${suffix}:./libtool2.${suffix}
./program_dynamic_notool

unset ${preload}
