# This file is usefull when cross-compiling
# Change this path as appropriate
export MW32=$HOME/sandbox/src/mingw-cross-env/usr
export PATH=$MW32/bin:$MW32/i686-pc-mingw32/bin:$PATH

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

# Reconfigure, and build for win32
autoreconf
cd $BUILD_FOLDER
../../../configure --prefix $INSTALL_FOLDER --host=i686-pc-mingw32 --build=i686-pc-linux-gnu
make && make install && rm -rf $BUILD_FOLDER && rm -rf $LATEST && ln -sf $INSTALL_FOLDER $LATEST
cd $HERE
makensis ./scripts/w32.nsis
