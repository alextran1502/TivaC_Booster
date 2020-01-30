#!/bin/bash
WORKSPACE=$(pwd)
ARCH=$(uname)

if [ "$ARCH" == "Darwin" ]; then # Build process for Mac
    echo "Macos TODO"
elif [ "$ARCH" == "Linux" ]
then
    /home/alex/ti/uniflash_5.0.0/dslite.sh -c $WORKSPACE/TM4C_Template/target_config.ccxml -e -f $WORKSPACE/TM4C_Template/Debug/TM4C_Template.out


else # Flash process for Window
    dslite.exe flash -c $WORKSPACE\\Benetton-TM4C\\target_config.ccxml -e -f $WORKSPACE\\Benetton-TM4C\\Debug\\Benetton-TM4C.out
fi