import socket
import json
import math
import struct

HOST = "127.0.0.1"
PORT = 45896

serversocket = socket.socket(socket.AF_INET,  # Internet
                             socket.SOCK_STREAM)  # TCP
serversocket.bind((HOST, PORT))
serversocket.listen(1)  # become a server socket, only 1 connection allowed


while True:
    client, address = serversocket.accept()
    length = client.recv(4)
    if length is not None:
        buffersize = struct.unpack(">I", length)[0]
	#print buffersize
    data = client.recv(buffersize)  # buffer size is 1024 bytes
    print "received message:", data
    response = "Roger that golden eagle"
    print "responding"
    # client.send(format(len(response), '#04x') + response)
    preamble = bytearray(struct.pack(">H", len(response) + 4))
    preamble += bytearray(struct.pack(">I", len(response)))
    client.send(preamble + response)
    print "responded"
    client.close()
