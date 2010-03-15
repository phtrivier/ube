#!/bin/sh

header() {
    echo "---------------------------------------"
    echo "Ube Ubuntu Distribution checker."
    echo "Copyright (c) 2009 Pierre-Henri Trivier"
    echo "---------------------------------------"
}

usage(){
    echo "Usage : cc_distcheck.sh [--no-tmp] [--help]"
}

options() {
    echo "Options :"
    echo "--help     : print this message"
}

for a in $@
do
    case $a in
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
    BUILD_FOLDER=$BUILDS/distcheck

    INSTALL_FOLDER=$BUILDS/distcheck/ube_linux

    UBUNTU_CONFIG_OPTIONS='--with-lua-prefix=/usr/include/lua5.1 --with-lua-suffix=5.1'

    chmod u+w $BUILD_FOLDER
    rm -rf $BUILD_FOLDER
    mkdir -p $BUILD_FOLDER
    mkdir -p $INSTALL_FOLDER
}


configure() {
    autoreconf
    cd $BUILD_FOLDER
    ../../../configure --prefix $INSTALL_FOLDER $UBUNTU_CONFIG_OPTIONS
}

build() {
    cd $BUILD_FOLDER
    export DISTCHECK_CONFIGURE_FLAGS="$UBUNTU_CONFIG_OPTIONS"
    make distcheck
}

main() {
    echo "Preparing distcheck..."
    prepare_folders
    echo "Configuring ..."
    configure
    echo "Checking distribution ..."
    build
}

# Fiat lux
main
