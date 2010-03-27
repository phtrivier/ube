#!/bin/sh

header() {
    echo "---------------------------------------"
    echo "Ube Ubuntu helper compiling script."
    echo "Copyright (c) 2009 Pierre-Henri Trivier"
    echo "---------------------------------------"
}

usage(){
    echo "Usage : cc_linux.sh [--no-tmp] [--help]"
}

options() {
    echo "Options :"
    echo "--no-build : the package is simply configured, and not build. This implies '--no-tmp'."
    echo "--no-tmp   : a long-lasting folder will be used for the build instead of a temporary one."
    echo "--help     : print this message"
}

# Is this a temporary build, or should we be able to reuse the folder in next builds ?
TMP_BUILD="yes"
BUILD="yes"

for a in $@
do
    case $a in
	--no-build)
	    BUILD="no"
	    TMP_BUILD="no"
	    ;;
	--no-tmp)
	    TMP_BUILD="no"
	    ;;
	--help)
	    header
	    usage
	    options
	    exit 0
	    ;;
	*)
	    echo "Unrecognized option '$a'"
	    usage
	    exit 1
    esac
done

prepare_folders() {
# Current position, and time stamps
    HERE=`pwd`
    NOW=`date +%Y-%m-%d_%H-%M-%S`

# Create folders to build and install
    BUILDS=$HERE/builds/linux

    if [ "$TMP_BUILD" = "yes" ]
    then
	BUILD_FOLDER=$BUILDS/tmp_$NOW
	INSTALL_FOLDER=$BUILDS/ube_linux_$NOW
    else
	BUILD_FOLDER=$BUILDS/current
	INSTALL_FOLDER=$BUILDS/ube_linux
    fi

    LATEST=$BUILDS/latest
    mkdir -p $BUILD_FOLDER
    mkdir -p $INSTALL_FOLDER
}

configure() {
    autoreconf
    cd $BUILD_FOLDER
    ../../../configure --prefix $INSTALL_FOLDER
}

build() {
# Reconfigure, and build for linux
    if [  "$TMP_BUILD" = "yes" ]
    then
	make check && make install && rm -rf $BUILD_FOLDER && rm -rf $LATEST && ln -sf $INSTALL_FOLDER $LATEST
    else
	make check && make install
    fi
}

main() {
    prepare_folders
    configure
    if [ "$BUILD" = "yes" ]
    then
	build
    fi
}

main