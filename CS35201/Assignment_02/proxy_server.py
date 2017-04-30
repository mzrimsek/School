import csv
import os
import sys
import socket
from datetime import datetime

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

    myServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        myServer.bind((local_host, local_port))
    except:
        print "[!!] Failed to listen on %s:%d" % (local_host, local_port)
        print "[!!] Check for other listening sockets or correct permissions."
        sys.exit(0)

    print "[*] Listening on %s:%d" % (local_host, local_port)

    myServer.listen(5)

    while num_requests < 100:

        num_requests += 1
        client_socket, addr = myServer.accept()
        request_time = str(datetime.now())

        #print out the local connection information
        print "[==>] Revieved incomming connection from %s:%d" % (addr[0], addr[1])
        #connect to remote host
        request = recieve_from(client_socket)

        #check if file in cache
        check_cache(request, client_socket, addr)

        #prints optional task - 1
        print "( " + str(num_requests) + " | " + str(total_bytes) + " | " + str(total_num_cache) + " | " + str(total_cache_bytes) + " )"

        write_to_csv(request)


def get_remote_file (request):

    remote_host = request.split(' ')[1].split('/')[2]
    remote_port = 80

    remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    remote_socket.connect((remote_host, remote_port))
    remote_socket.send(request)
    remote_buffer = recieve_from(remote_socket)


    #if we have data to send to our local client, send it
    if len(remote_buffer):
        print "[<==] Sending %d bytes to localhost." %len(remote_buffer)


    #if no more data on either side, close the connections
    if not len(remote_buffer):
        remote_socket.close()
        print "[*] No more data. Closing connections."
    
    return remote_buffer

def recieve_from(connection):
    buffer=""

    #we set 2 sec timeout
    connection.settimeout(2)
    try:
        #keep reading into buffer until there is no more data or time out
        while True:
            data = connection.recv(4096)

            if not data:
                break

            buffer += data
    
    except:
        pass

    return buffer

#check if file exists
def check_cache(request, client_socket, addr):
    global num_requests
    global total_bytes
    global total_num_cache
    global total_cache_bytes
    global response_time

    #optional-task-2
    if request.split("\n")[0].split(" ")[1] == "/proxy_usage?":
        line_to_print = "( " + str(num_requests) + " | " + str(total_bytes) + " | " + str(total_num_cache) + " | " + str(total_cache_bytes) + " )\r\n\r\n"
        http_message = "HTTP/1.1 200 OK\r\n"
        http_message += "Content-Type: text/plain\r\n"
        http_message += "Content-Length: " + str(len(line_to_print))
        http_message += "Connection: close\r\n\r\n"
        http_message += line_to_print
        client_socket.send(http_message.encode())
        response_time = str(datetime.now())

    #optional-task-3
    elif request.split("\n")[0].split(" ")[1] == "/proxy_usage_reset?":
        num_requests = 0
        total_bytes = 0
        total_num_cache = 0
        total_cache_bytes = 0
        line_to_print = "( " + str(num_requests) + " | " + str(total_bytes) + " | " + str(total_num_cache) + " | " + str(total_cache_bytes) + " )\r\n\r\n"
        http_message = "HTTP/1.1 200 OK\r\n"
        http_message += "Content-Type: text/plain\r\n"
        http_message += "Content-Length: " + str(len(line_to_print))
        http_message += "Connection: close\r\n\r\n"
        http_message += line_to_print
        client_socket.send(http_message.encode())
        response_time = str(datetime.now())

    
    elif request.split("\n")[0].split(" ")[1] == "/proxy_log?":
        file = open(os.path.join("log_file.csv"), 'r')
        line_to_print = file.read()
        http_message = "HTTP/1.1 200 OK\r\n"
        http_message += "Content-Type: text/plain\r\n"
        http_message += "Content-Length: " + str(len(line_to_print))
        http_message += "Connection: close\r\n\r\n"
        http_message += line_to_print
        client_socket.send(http_message.encode())
        response_time = str(datetime.now())


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


#get request from cache
def get_from_cache (host, file):
    print "Cache Hit!"
    file = open(os.path.join(host, file), 'r')
    returned_buffer = file.read()
    file.close()
    return returned_buffer


#modify requests to remote host
def request_handler(buffer):
    #put modifications here

    return buffer


#optional-task-4
def write_to_csv(request):
    global total_num_cache
    global request_time
    global response_time

    parsedRequest = request.split(' ')[1].split('/', 3)
    requested_file = parsedRequest[len(parsedRequest)-1]
    if not os.path.isfile(os.path.join("log_file.csv")):
        file = open(os.path.join("log_file.csv"), 'a')
        file.write("Requested time, Response Time, CacheHit, RequestedString\n")
        file.write(request_time + ", " + response_time + ", " + str(total_num_cache) + ", " + str(requested_file) + "\n")
    
    else:
        file = open(os.path.join("log_file.csv"), 'a')
        file.write(request_time + ", " + response_time + ", " + str(total_num_cache) + ", " + str(requested_file) + "\n")

    file.close()


def main():
    local_host = "127.0.0.1"
    local_port = 9001

    server(local_host, local_port)


if __name__ == '__main__':
    main()
    