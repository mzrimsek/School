#!/bin/bash
#####################################
# Functions that can be used in the #
# build_irssi.sh script.            #
#####################################

# Print out some message and exit the script immediately
quit () {
    printf "$1\n"
    exit
}

report_status () {
    STATUS=$1 
    if [ $STATUS = 0 ]; then
        printf "[\033[0;32m";printf "OK\033[0m]\t"
    else
        printf "[\033[0;31m";printf "FAIL\033[0m]\t"
    fi
    printf "$2\n"
}

verify_irssi_install () {
    test -d ~/local
    report_status $? "Making sure local dir exists."
    test -x ~/local/bin/irssi
    report_status $? "Make sure irssi is an executable"
    ~/local/bin/irssi --version|grep -q '^irssi .*201609.*$' 2>/dev/null
    report_status $? "Verify irssi installed and reports version"
    ldd ~/local/bin/irssi |grep -q libssl 2>/dev/null
    report_status $? "Verify irssi compiled with SSL support"
    strings ~/local/bin/irssi |grep etc|grep -q `whoami` 2>/dev/null
    report_status $? "Verify it was installed in user's home dir."
}
