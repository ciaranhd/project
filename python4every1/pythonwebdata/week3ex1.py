import socket
#create a handle
mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# we establish a connection, however it has not yet connected. 80 refers to the web server
# 'extension'
mysock.connect(('data.pr4e.org', 80))
# the command line handle refers to the page we actually want.
cmd = 'GET http://data.pr4e.org/intro-short.txt HTTP/1.0\r\n\r\n'.encode()
mysock.send(cmd)
# we can also set some parameters for the data we recover
while True:
    data = mysock.recv(512)
    if len(data) < 1:
        break
    print(data.decode(),end='')

mysock.close()
