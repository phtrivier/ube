#!/bin/sh

# The MW32 path should be the path where syou installed mingw-cross-env.
# Version 2.9 at least is required.

# Change this path as appropriate
#export MW32=$HOME/sandbox/src/mingw-cross-env
export MW32=$HOME/src/mingw-cross-env-trunk

# Tools from mingw-cross-env should be available
export PATH=$MW32/usr/bin:$MW32/usr/i686-pc-mingw32/bin:$PATH
#export PATH=$MW32/usr/i686-pc-mingw32/bin:$MW32/usr/bin:$PATH

# Check that mingw_cross_env has been installed
check_mingw_cross_env() {
    if [ ! -d $MW32 ]
    then
	echo "No mingw-cross-env found at $MW32"
	echo "Fix the script accordingly."
	exit 1
    fi
}

header() {
    echo "---------------------------------------"
    echo "Ube cross compiling script."
    echo "Copyright (c) 2009 Pierre-Henri Trivier"
    echo "---------------------------------------"
}

# Print usage
usage() {
    echo "Usage : cc_w32.sh [--no-nsis] [--no-cc] [--help]"
}

# Print options
options() {
    echo "Options : "
    echo " --no-nsis : do not build the NSIS installer."
    echo " --no-cc   : do not rebuild the c++ code (code from 'build/w32/latest' build will be used)."
    echo " --help    : print this message."
}

prepare_folders() {
# Current position, and time stamps
    HERE=`pwd`
    NOW=`date +%Y-%m-%d_%H-%M-%S`

# Create folders to build and install
    BUILDS=$HERE/builds/w32
    BUILD_FOLDER=$BUILDS/tmp_w32_$NOW
    INSTALL_FOLDER=$BUILDS/ube_w32_$NOW
    LATEST=$BUILDS/latest
    mkdir -p $BUILD_FOLDER
    mkdir -p $INSTALL_FOLDER
}

build_cc() {
    autoreconf
    cd $BUILD_FOLDER
    ../../../configure  --with-boost=$MW32/usr/i686-pc-mingw32/include --with-boost-lib-dir=$MW32/usr/i686-pc-mingw32/lib --prefix $INSTALL_FOLDER --host=i686-pc-mingw32 --build=i686-pc-linux-gnu 
    make  && make install && rm -rf $BUILD_FOLDER && rm -rf $LATEST && ln -sf $INSTALL_FOLDER $LATEST
}

build_nsis() {
    if [ -e $LATEST ]
    then
	cd $HERE
	makensis ./scripts/w32.nsis
    else
	echo "No build found in $LATEST."
	echo "You probably need to run the script at least one without the --no-cc option."
	exit 1
    fi
}

build_required() {

    if [ "$MAKE_CC" = "yes" ]
    then
	build_cc
    fi

    if [ "$MAKE_NSIS" = "yes" ]
    then
	build_nsis
    fi
}

MAKE_NSIS="yes"
MAKE_CC="yes"
for a in $@
do
    case "$a" in 
	--no-nsis)     
	    MAKE_NSIS="no"
	    ;;
	--no-cc )
	    MAKE_CC="no"
	    ;;
	--help)
	    header
	    usage
	    options
	    exit 0
	    ;;
	*)
	    echo "Unrecognized option $a"
	    usage
	    exit 1
	    ;;
    esac
done

main() {
    check_mingw_cross_env
    prepare_folders
    build_required
}

# Fiat lux.
main