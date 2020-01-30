WORKSPACE=$(pwd)
ARCH=$(uname)

if [ "$ARCH" == "Darwin" ]; then # Build process for Mac
    # Build Web App
    cd $WORKSPACE/Benetton-TM4C/src_web
    npm run build
    
    # Delete Map File
    cd $WORKSPACE/Benetton-TM4C/src_web/build/static
    find . -name "*.map" -type f -delete
    
    # Build fs from perl script
    cd $WORKSPACE/Benetton-TM4C/
    perl makefsdata
    
    # Check
    cd $WORKSPACE/Benetton-TM4C/
    INCLUDE_CHECK=$(sed '55!d' io_fs.c)
    if [ "$INCLUDE_CHECK" == "#include \"fsdata.h\"" ]; then
        echo Header File is Good
        continue
    else
        echo CHECK HEADER FILE IN io_fs.c
        exit 1
    fi
    
    # # Build
    cd $WORKSPACE/Benetton-TM4C/Debug
    /Applications/ti/ccs901/ccs/utils/bin/gmake -k -j 12 all -O
elif [ "$ARCH" == "Linux" ]
then
    cd $WORKSPACE/TM4C_Template/Debug
    /home/alex/ti/ccs920/ccs/utils/bin/gmake -k -j 8 all -O


else # Build process for Window
    cd $WORKSPACE\\Benetton-TM4C\\src_web
    npm run build

    cd $WORKSPACE\\Benetton-TM4C\\src_web\\build\\static
    find . -name "*.map" -type f -delete

    cd $WORKSPACE\\Benetton-TM4C\\
    # ./makefsfile.exe -i fs -o io_fsdata.h -r -h -q
    # ./makefsfile.exe -i src_web/build/ -o io_fsdata.h -r -h -q
    perl makefsdata

    cd $WORKSPACE\\Benetton-TM4C\\Debug
    C:\\ti\\ccs901\\ccs\\utils\\bin\\gmake -k -j 12 all -O
fi


echoerr() { echo "$@" 1>&2; }



