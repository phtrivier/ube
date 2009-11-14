# Current position, and time stamps
HERE=`pwd`
NOW=`date +%Y-%m-%d_%H-%M-%S`

# Create folders to build and install
BUILDS=$HERE/builds/linux
BUILD_FOLDER=$BUILDS/tmp_$NOW
INSTALL_FOLDER=$BUILDS/ube_linux_$NOW
LATEST=$BUILDS/latest
mkdir -p $BUILD_FOLDER
mkdir -p $INSTALL_FOLDER

# Reconfigure, and build for win32
autoreconf
cd $BUILD_FOLDER
../../../configure --prefix $INSTALL_FOLDER --with-lua-prefix=/usr/include/lua5.1 --with-lua-suffix=5.1
make && make install && rm -rf $BUILD_FOLDER && rm -rf $LATEST && ln -sf $INSTALL_FOLDER $LATEST
