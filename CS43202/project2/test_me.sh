#!/bin/sh

export PATH=${PATH}":."

report_status () {
   STATUS=$1 
   if [ $STATUS = 0 ]; then
    printf "[\033[0;32m";printf "OK\033[0m]\t"
   else
    printf "[\033[0;31m";printf "FAIL\033[0m]\t"
   fi
   printf "$2\n"
}
count () {
    if [ -n "$1" ]; then
        return $#
    else
        return 0
    fi
}
is_def () {
    type $1 | grep -q 'is a.*function'
    return $?
}

check_vars () {
    test -n "$MESSAGE"
    STATUS=$?
    report_status $STATUS "Checking variable MESSAGE set correctly"
    test -n "$DIRC"
    STATUS=$?
    report_status $STATUS "Checking variable DIRC exists"
    touch $DIRC/flapjacks 2>/dev/null
    STATUS=$?
    report_status $STATUS "Checking variable DIRC set correctly"
    grep -q '^ex.*STFILE.*foo123$' fix_me.sh
    STATUS=$?
    report_status $STATUS "Checking TESTFILE variable set globally"
}
check_images () {
    IMGS=tree/images/*.???
    count $IMGS
    NUM=$?
    test $NUM -eq 16
    STATUS=$?
    report_status $STATUS "Checking correct number of images decoded"
    STATUS=0
    for f in tree/images/*.???; do
        TYPE=$(file -b --mime-type $f|cut -d'/' -f1)
        if [ "$TYPE" != "image" ]; then
            STATUS=1
        fi
    done
    report_status $STATUS "Check that all files in image dir are images"
}
check_heredoc () {
    STATUS=0
    grep -q 'XX1123143221' tree/modulator/creaks/heredoc && STATUS=1
    report_status $STATUS "Testing HERE DOC"
}
check_testfun () {
    is_def testfun
    STATUS=$?
    report_status $STATUS "Checking if testfun function is defined"
    if [ $STATUS -eq 0 ]; then
        STATUS1=5
        touch $TESTFILE && testfun
        STATUS1=$?
        rm -f $TESTFILE && testfun
        STATUS2=$?
        test $STATUS1 -eq 0 && test $STATUS2 -ne 0
        STATUS=$?
        report_status $STATUS "Check whether testfun works"
    fi
}
check_quote () {
    test -n "$QUOTE"
    STATUS=$?
    report_status $STATUS "Checking variable QUOTE set correctly"
    grep -q 'Nietzsche' tree/generated/splines/setbacks/victualed/steadies/quote 2>/dev/null
    STATUS=$?
    report_status $STATUS "Checking QUOTE written to file correctly"
}

# source the fix_me script so it runs as it should
. fix_me.sh

check_vars
check_images
check_heredoc
check_testfun
check_quote

printf "\n$QUOTE\n"

