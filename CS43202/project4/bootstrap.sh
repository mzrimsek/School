#!/bin/bash
######################################################
# bootstrap.sh
#
#  Bootstraps admin tool environment from scratch.
#
#  Author:  Mike Zrimsek  <mzrimsek@kent.edu>
#  Version:  1.0
#
######################################################
. ./helper_funcs.sh

#location variables
export SCRIPT_DIR="$(pwd)"
export INSTALL_ROOT="${HOME}/local"
export SRC_DIR="${INSTALL_ROOT}/src"
export BUILD_DIR="${INSTALL_ROOT}/build"
export BIN_DIR="${INSTALL_ROOT}/bin"

#python download variables
export PYTHON_VERSION="2.7.12"
export PYTHON_BASE_URL="https://www.python.org/ftp/python/"
export PYTHON_TAR="Python-${PYTHON_VERSION}.tgz"
export PYTHON_TAR_SIG="Python-${PYTHON_VERSION}.tgz.asc"
export PYTHON_DOWNLOAD_URL="${PYTHON_BASE_URL}${PYTHON_VERSION}"
export PYTHON_TAR_URL="${PYTHON_DOWNLOAD_URL}/${PYTHON_TAR}"
export PYTHON_SIG_URL="${PYTHON_DOWNLOAD_URL}/${PYTHON_TAR_SIG}"

#python pubkey variables
export PYTHON_PUBKEY_URL="https://www.python.org/static/files/pubkeys.txt"
export PYTHON_PUBKEYS="${SRC_DIR}/python_pubkeys.txt"

#make required directories if don't exist
test -d ${INSTALL_ROOT} || mkdir -p ${INSTALL_ROOT}
test -d ${SRC_DIR} || mkdir -p ${SRC_DIR}
test -d ${BUILD_DIR} || mkdir -p ${BUILD_DIR}
test -d ${BIN_DIR} || mkdir -p ${BIN_DIR}

#check if installation exists
SKIP_INSTALL=1

if [ -e ${BIN_DIR}/python ]; then
	INSTALLED_VERSION=$(${BIN_DIR}/python -V 2>&1)
	if [[ $INSTALLED_VERSION == *$PYTHON_VERSION* ]]; then
		echo "$INSTALLED_VERSION installation found. Skipping to Pip..."
		SKIP_INSTALL=0
	fi
fi

#skip installation if exists with correct version
if [ $SKIP_INSTALL = 1 ]; then

	#download and verify source
	download_python || quit "Failed to download python!"
	verify_python_source || quit "Python source verification failed"

	#unpack source to build directory
	tar -C $BUILD_DIR -f ${SRC_DIR}/$PYTHON_TAR -xv --strip-components=1

	#configure and install
	cd $BUILD_DIR
	./configure --prefix ${INSTALL_ROOT} --disable-ipv6
	make
	make install

	#verify Python installation
	test -x ${BIN_DIR}/python || quit "Python not installed correctly!"

	#clean up build directory
	cd $INSTALL_ROOT
	rm -r $BUILD_DIR

	#verify installed version
	INSTALLED_VERSION=$(${BIN_DIR}/python -V 2>&1)
	if [[ $INSTALLED_VERSION != *$PYTHON_VERSION* ]]; then
		quit "Incorrect Python version installed"
	fi
fi

#verify Pip module and update to latest
${BIN_DIR}/python -m ensurepip
${BIN_DIR}/python -m pip install --upgrade pip

#verify Pip installation
test -x ${BIN_DIR}/pip || quit "Pip not installed correctly!"

#install packages
${BIN_DIR}/pip install --upgrade -r ${SCRIPT_DIR}/requirements.txt

echo "Installation complete"
