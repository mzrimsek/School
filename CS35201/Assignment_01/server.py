from socket import *

def main():
    server_socket = socket(AF_INET, SOCK_STREAM)
    server_socket.bind(('localhost', 8059))
    server_socket.listen(1)

    while True:
        connection_socket, addr = server_socket.accept()

        try:
            message = connection_socket.recv(1024)
            file_name = message.split()[1]
            requested_file = open(file_name[1:])
            output_data = requested_file.read()

            connection_socket.send('\n')
            connection_socket.send('HTTP/1.1 200 OK\n')
            connection_socket.send('Connection: close\n')
            length_string = 'Content-Length: ' + str(len(output_data)) + '\n'
            connection_socket.send(length_string)
            connection_socket.send('Content-Type: text/html\n')
            connection_socket.send('\n')
            connection_socket.send('\n')

            for i in range(0, len(output_data)):
                connection_socket.send(output_data[i])
            connection_socket.close()

        except IOError:
            connection_socket.send('\n')
            error_string = '404 Not Found: Requested document not found'
            connection_socket.send(error_string)
            connection_socket.close()

    server_socket.close()

if __name__ == '__main__':
    main()
