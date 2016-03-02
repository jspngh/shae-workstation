import socket
import json

HOST = "127.0.0.1"
PORT = 6330

serversocket = socket.socket(socket.AF_INET,  # Internet
                             socket.SOCK_STREAM)  # TCP
serversocket.bind((HOST, PORT))
serversocket.listen(1)  # become a server socket, only 1 connection allowed


while True:
    client, address = serversocket.accept()
    data = client.recv(1024)  # buffer size is 1024 bytes
    print "received message:", data
