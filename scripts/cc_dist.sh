#!/bin/sh

header() {
    echo "---------------------------------------"
    echo "Ube Ubuntu Distribution helper."
    echo "Copyright (c) 2009 Pierre-Henri Trivier"
    echo "---------------------------------------"
}

usage(){
    echo "Usage : cc_dist.sh [--check] [--help]"
}

options() {
    echo "Options :"
    echo "--help     : print this message"
    echo "--no-check : do not run 'check' tests"
}

DISTCHECK="yes"

for a in $@
do
    case $a in
	--help)
	    header
	    usage
	    options
	    exit 0
	    ;;
	--no-check)
	    DISTCHECK="no"
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

    chmod u+w $BUILD_FOLDER
    rm -rf $BUILD_FOLDER
    mkdir -p $BUILD_FOLDER
    mkdir -p $INSTALL_FOLDER
}


configure() {
    autoreconf --install
    cd $BUILD_FOLDER
    ../../../configure --prefix $INSTALL_FOLDER
}

build() {
    cd $BUILD_FOLDER
    export DISTCHECK_CONFIGURE_FLAGS="$UBUNTU_CONFIG_OPTIONS"
    if [ "$DISTCHECK" = "yes" ]
    then
	make distcheck
    else
	make dist
    fi
}

main() {
    echo "Preparing dist..."
    prepare_folders
    echo "Configuring ..."
    configure
    echo "Checking distribution ..."
    build
}

# Fiat lux
main
