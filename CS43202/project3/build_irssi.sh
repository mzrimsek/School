#!/bin/bash
. ./funcs.sh

#variables
export LOCALDIR=${HOME}"/local"
export SRCDIR=${LOCALDIR}"/src"
export BUILDDIR=${LOCALDIR}"/build"
export IRSSI_VERSION="0.8.20"
export IRSSI_TAR="irssi-${IRSSI_VERSION}.tar.gz"
export IRSSI_BASE_URL="https://github.com/irssi/irssi/releases/download/"

#make build and src directories if don't exist
test -d $SRCDIR || mkdir -p $SRCDIR
test -d $BUILDDIR || mkdir -p $BUILDDIR

#download latest version
curl -s -L "${IRSSI_BASE_URL}${IRSSI_VERSION}/${IRSSI_TAR}" \
     -o ${SRCDIR}"/"${IRSSI_TAR} || quit "Download failed for some reason!"

#test download was successful
test -f ${SRCDIR}"/"${IRSSI_TAR} || quit "File must have failed to download!"

#unpack source to build directory
tar -C ${BUILDDIR} -f "${SRCDIR}/${IRSSI_TAR}" -xv --strip-components=1

#configure and install
cd $BUILDDIR
./configure --prefix ${LOCALDIR} --disable-ipv6
make
make install

#verify installation
test -x ~/local/bin/irssi || quit "irssi didn't get installed? Check ~/local/bin/irssi exists!"
verify_irssi_install
