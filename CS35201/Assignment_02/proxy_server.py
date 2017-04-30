import csv
import os
import sys
import socket
from datetime import datetime

log_file_name = "log.csv"

num_requests = 0
total_bytes = 0
total_num_cache = 0
total_cache_bytes = 0
request_time = ""
response_time = ""

def server(local_host, local_port):
    global num_requests
    global total_bytes
    global total_num_cache
    global total_cache_bytes
    global request_time
    global response_time

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        server.bind((local_host, local_port))
    except:
        print "[!!] Failed to listen on %s:%d" % (local_host, local_port)
        print "[!!] Check for other listening sockets or correct permissions."
        sys.exit(0)

    print "[*] Listening on %s:%d" % (local_host, local_port)
    server.listen(5)

    while num_requests < 100:
        num_requests += 1
        client_socket, addr = server.accept()
        request_time = str(datetime.now())

        print "[==>] Revieved incomming connection from %s:%d" % (addr[0], addr[1])
        request = receive_from(client_socket)

        check_cache(request, client_socket, addr)
        print "( " + str(num_requests) + " | " + str(total_bytes) + " | " + str(total_num_cache) + " | " + str(total_cache_bytes) + " )"

        write_log(request)

def get_remote_file (request):
    remote_host = request.split(' ')[1].split('/')[2]
    remote_port = 80

    remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    remote_socket.connect((remote_host, remote_port))
    remote_socket.send(request)
    remote_buffer = receive_from(remote_socket)

    if len(remote_buffer):
        print "[<==] Sending %d bytes to localhost." %len(remote_buffer)

    if not len(remote_buffer):
        remote_socket.close()
        print "[*] No more data. Closing connections."
    
    return remote_buffer

def receive_from(connection):
    buffer=""
    connection.settimeout(2)

    try:
        while True:
            data = connection.recv(4096)
            if not data:
                break
            buffer += data
    except:
        pass

    return buffer

def check_cache(request, client_socket, addr):
    global num_requests
    global total_bytes
    global total_num_cache
    global total_cache_bytes
    global response_time

    line_to_print = "( " + str(num_requests) + " | " + str(total_bytes) + " | " + str(total_num_cache) + " | " + str(total_cache_bytes) + " )\r\n\r\n"
    request_type = request.split("\n")[0].split(" ")[1]

    if request_type == "/proxy_usage?":
        get_response(line_to_print)
    elif request_type == "/proxy_usage_reset?":
        reset_proxy(line_to_print
    elif request_type == "/proxy_log?":
        get_proxy_log(line_to_print)
    else:
        parsedRequest = request.split(' ')[1].split('/', 3)
        host = parsedRequest[2]
        file = parsedRequest[3]
        remote_port = 80
        
        if os.path.isdir(host) and os.path.isfile(os.path.join(host,file)):
            returned_buffer = get_from_cache(host, file)
            total_num_cache += 1
            total_cache_bytes += len(returned_buffer)
            total_bytes += len(returned_buffer)
            client_socket.send(returned_buffer)
            response_time = str(datetime.now())
        else:
            returned_buffer = get_remote_file(request)
            if not os.path.isdir(host):
                os.makedirs(host)
            with open(os.path.join(host, file), 'wb') as temp_file:
                temp_file.write(returned_buffer)
            total_bytes += len(returned_buffer)
            client_socket.send(returned_buffer)
            response_time = str(datetime.now())

        if not len(returned_buffer):
            client_socket.close()

def get_from_cache (host, file):
    print "Cache Hit!"
    file = open(os.path.join(host, file), 'r')
    returned_buffer = file.read()
    file.close()
    return returned_buffer

def write_log(request):
    global total_num_cache
    global request_time
    global response_time

    parsedRequest = request.split(' ')[1].split('/', 3)
    requested_file = parsedRequest[len(parsedRequest)-1]
    info_to_write = request_time + ", " + response_time + ", " + str(total_num_cache) + ", " + str(requested_file) + "\n"
    log_file = open(os.path.join(log_file_name), 'a')

    if not os.path.isfile(os.path.join(log_file_name)):
        log_file.write("Requested time, Response Time, CacheHit, RequestedString\n")
        log_file.write(info_to_write)
    else:
        log_file.write(info_to_write)

    log_file.close()

def reset_proxy(line_to_print):
    num_requests = 0
    total_bytes = 0
    total_num_cache = 0
    total_cache_bytes = 0
    get_response(line_to_print)

def get_proxy_log(line_to_print):
    file = open(os.path.join(log_file_name), 'r')
    line_to_print = file.read()
    get_response(line_to_print)

def get_response(line_to_print):
    message = "HTTP/1.1 200 OK\r\n"
    message += "Content-Type: text/plain\r\n"
    message += "Content-Length: " + str(len(line_to_print))
    message += "Connection: close\r\n\r\n"
    message += line_to_print
    client_socket.send(message.encode())
    response_time = str(datetime.now())

def main():
    local_host = "127.0.0.1"
    local_port = 9001
    server(local_host, local_port)

if __name__ == '__main__':
    main()