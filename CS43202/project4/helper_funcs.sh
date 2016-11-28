##
## Begin Functions
##

# Define some handy functions here.

# Display a message and exit the script immediately
quit () {
    printf "$1\n"
    exit
}

# Print a pretty status message
report_status () {
    STATUS=$1 
    if [ $STATUS = 0 ]; then
        printf "[\033[0;32m";printf "OK\033[0m]\t"
    else
        printf "[\033[0;31m";printf "FAIL\033[0m]\t"
    fi
    printf "$2\n"
}

# Download a URL and save it as a filename
# use like:
# download_url https://foo.blah/file.tar /home/foo/file.tar
download_url () {
    URL=$1
    DEST=$2

    curl -s -L "${URL}" -o "${DEST}"
    STATUS=$?

    return $STATUS
}

verify_python () {

    if [ -x ${INSTALL_ROOT}/bin/python ]; then
        ${INSTALL_ROOT}/bin/python -V 2>&1 | grep -q "${PYTHON_VERSION}" || \
        msg="${INSTALL_ROOT}/bin/python version not reporting ${PYTHON_VERSION}"
        quit "$msg"
    else
        quit "${INSTALL_ROOT}/bin/python is not executable!"
    fi
}

# Function to download python source
download_python () {
    # If source already downloaded, don't waste the bandwidth...
    test -f $SRC_DIR/$PYTHON_TAR || \
      download_url $PYTHON_TAR_URL $SRC_DIR/$PYTHON_TAR
    STATUS=$?
    report_status $STATUS "Downloading python $PYTHON_VERSION"

    # See if we already downloaded the signature file, if not, go fetch it
    test -f $SRC_DIR/$PYTHON_TAR_SIG || \
        download_url $PYTHON_SIG_URL $SRC_DIR/$PYTHON_TAR_SIG
    report_status $? "Downloading python $PYTHON_VERSION gpg signature"
    
    return $STATUS
}

# Function to verify source download is good
verify_python_source () {

    # Download python release manager's public gpg keys so we can
    # verify the source downloads
    test -f $PYTHON_PUBKEYS || download_url $PYTHON_PUBKEY_URL $PYTHON_PUBKEYS
    report_status $? "Downloading python.org gpg public keys"

    # import python public keys for verifying download
    gpg -q --import $PYTHON_PUBKEYS > /dev/null
    report_status $? "Importing python.org gpg public keys"

    # verify the download is legit
    gpg -q --verify "${SRC_DIR}/${PYTHON_TAR_SIG}" 2>/dev/null
    STATUS=$?
    report_status $STATUS "Verifying Python source download"

    return $STATUS
}

##
## End Functions
##
