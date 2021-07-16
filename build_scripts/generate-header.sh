#!/bin/bash
interactive=1
LCM_HEINEKEN_HOME=../../lcm_heineken

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
root_path=$(cd ../ ; pwd -P)
cd "$parent_path"

if [ "$interactive" = "1" ]; then
    response=

    echo -n "Enter path to lcm_heineken repository [$LCM_HEINEKEN_HOME] : "
    read response
    if [ -n "$response" ]; then
        LCM_HEINEKEN_HOME=$response
    fi

    echo "Removing old definitions"
    rm -rf ../Definitions/Hmi/*

    echo "Copying all LCM definitions from lcm_heineken"    
    cd $parent_path
    cd ${LCM_HEINEKEN_HOME}
    cd lcm/AVP
    find . -name "*.lcm" -type f -exec cp {} "$root_path"/Definitions/Hmi \;

    cd ../General
    find . -name "*.lcm" -type f -exec cp {} "$root_path"/Definitions/Hmi \;

    cd ../TJP
    find . -name "*.lcm" -type f -exec cp {} "$root_path"/Definitions/Hmi \;

    cd ../VirtualBumper
    find . -name "*.lcm" -type f -exec cp {} "$root_path"/Definitions/Hmi \;

    echo "Deleting old LCM sources"
    cd $parent_path

    if [ ! -d ../GeneratedLcm/Hmi ]
    then
        mkdir ../GeneratedLcm/Hmi
    else
        rm -rf ../GeneratedLcm/Hmi/*
    fi


    echo "Generating new LCM sources from lcm_heineken"
    cd ../Hmi
    find ../../Definitions/Hmi -name "*.lcm" -print0 | xargs -0 lcm-gen -x
    
    exit 1

fi
