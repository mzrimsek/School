#!/bin/bash

send_request() {
    wget -O/dev/null -e use_proxy=yes -e http_proxy=127.0.0.1:9001 $1
}

send_requests() {
    send_request http://www.atr.cs.kent.edu/proxy_test1.html
    send_request http://www.atr.cs.kent.edu/proxy_test2.html
    send_request http://www.atr.cs.kent.edu/proxy_test3.html
}

cleanup_files() {
    rm -rf www.*
    rm -rf proxy_test*.html*
    rm *.csv
}

echo "Round 1"
send_requests

echo "Round 2"
send_requests

echo "Round 3"
send_requests

echo "Cleaning Up"
cleanup_files

echo "Killing Server"
pkill -f proxy_server.py