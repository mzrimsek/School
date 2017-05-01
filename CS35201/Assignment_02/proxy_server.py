import csv
import os
import sys
import socket
from datetime import datetime

remote_port = 80
log_file = "log.csv"

num_requests = 0
total_bytes = 0
total_num_cache = 0
total_cache_bytes = 0
request_time = ""
response_time = ""

def run_server(local_host, local_port):
    global num_requests
    global request_time

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.bind((local_host, local_port))
    except:
        print "[!!] Failed to listen on %s:%d" %(local_host, local_port)
        print "[!!] Check for other listening sockets or correct permissions."
        sys.exit(0)

    print "[*] Listening on %s:%d" % (local_host, local_port)
    server.listen(5)

    while num_requests < 100:
        num_requests += 1
        client_socket, addr = server.accept()
        request_time = str(datetime.now())

        print "[==>] Revieved incomming connection from %s:%d" % (addr[0], addr[1])
        request = receive_from_connection(client_socket)

        process_request(request, client_socket, addr)
        print get_request_stats()

        write_to_log(request)

def get_remote_file (request):
    remote_host = request.split(' ')[1].split('/')[2]
    remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    remote_socket.connect((remote_host, remote_port))
    remote_socket.send(request)
    remote_buffer = receive_from_connection(remote_socket)

    if len(remote_buffer):
        print "[<==] Sending %d bytes to localhost." %len(remote_buffer)

    if not len(remote_buffer):
        remote_socket.close()
        print "[*] No more data. Closing connections."
    
    return remote_buffer

def receive_from_connection(connection):
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

def process_request(request, client_socket, addr):
    global num_requests
    global total_bytes
    global total_num_cache
    global total_cache_bytes

    line_to_print = get_request_stats() + "\r\n\r\n"
    request_type = request.split("\n")[0].split(" ")[1]
    if request_type == "/proxy_usage?":
        http_message = process_request_message(line_to_print)
        send_response(client_socket, http_message.encode())
    elif request_type == "/proxy_usage_reset?":
        num_requests = 0
        total_bytes = 0
        total_num_cache = 0
        total_cache_bytes = 0
        http_message = process_request_message(line_to_print)
        send_response(client_socket, http_message.encode())
    elif request_type == "/proxy_log?":
        file = open(os.path.join(log_file), 'r')
        line_to_print = file.read()
        http_message = process_request_message(line_to_print)
        send_response(client_socket, http_message.encode())
    else:
        parsed_request = request.split(' ')[1].split('/', 3)
        host = parsed_request[2]
        file = parsed_request[3]
        
        if os.path.isdir(host) and os.path.isfile(os.path.join(host,file)):
            data = get_from_cache(host, file)
            total_bytes += len(data)
            total_num_cache += 1
            total_cache_bytes += len(data)
            send_response(client_socket, data)
        else:
            data = get_remote_file(request)
            if not os.path.isdir(host):
                os.makedirs(host)
            with open(os.path.join(host, file), 'wb') as temp_file:
                temp_file.write(data)
            total_bytes += len(data)
            send_response(client_socket, data)

        if not len(data):
            client_socket.close()

def send_response(client_socket, message):
    global response_time

    client_socket.send(message)
    response_time = str(datetime.now())

def process_request_message(line_to_print):
    message = "HTTP/1.1 200 OK\r\n"
    message += "Content-Type: text/plain\r\n"
    message += "Content-Length: " + str(len(line_to_print))
    message += "Connection: close\r\n\r\n"
    message += line_to_print
    return message

def get_request_stats():
    global num_requests
    global total_bytes
    global total_num_cache
    global total_cache_bytes

    return "( " + str(num_requests) + " | " + str(total_bytes) + " | " + str(total_num_cache) + " | " + str(total_cache_bytes) + " )"

def get_from_cache (host, file):
    print "Cache Hit!"
    file = open(os.path.join(host, file), 'r')
    data = file.read()
    file.close()
    return data

def write_to_log(request):
    global total_num_cache
    global request_time
    global response_time

    parsed_request = request.split(' ')[1].split('/', 3)
    requested_file = parsed_request[len(parsed_request)-1]
    if not os.path.isfile(os.path.join(log_file)):
        file = open(os.path.join(log_file), 'a')
        file.write("Requested time, Response Time, CacheHit, RequestedString\n")
    else:
        file = open(os.path.join(log_file), 'a')

    file.write(request_time + ", " + response_time + ", " + str(total_num_cache) + ", " + str(requested_file) + "\n")
    file.close()

def main():
    local_host = "127.0.0.1"
    local_port = 9001
    run_server(local_host, local_port)

if __name__ == '__main__':
    main()