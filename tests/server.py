import socket
import json
import math
import struct

HOST = "127.0.0.1"
PORT = 6331

serversocket = socket.socket(socket.AF_INET,  # Internet
                             socket.SOCK_STREAM)  # TCP
serversocket.bind((HOST, PORT))
serversocket.listen(1)  # become a server socket, only 1 connection allowed


while True:
    client, address = serversocket.accept()
    length = client.recv(4)
    if length is not None:
        buffersize = struct.unpack(">I", length)[0]
        # print buffersize
    data = client.recv(buffersize)
    # print "received message:{0}".format(data)
    packet = json.loads(data)  # parse the Json we received

    if 'MessageType' not in packet:  # every packet should have a MessageType field
        raise ValueError
    if 'Message' not in packet:  # every packet should have a Message field
        raise ValueError

    message_type = packet['MessageType']  # the 'message type' attribute tells us to which class of packet this packet belongs
    message = packet['Message']           # the 'message' attribute tells what packet it is, within it's class
    print message

    response = "Roger that golden eagle"
    print "responding"
    # client.send(format(len(response), '#04x') + response)
    preamble = bytearray(struct.pack(">H", len(response) + 4))
    preamble += bytearray(struct.pack(">I", len(response)))
    client.send(preamble + response)
    print "responded"
    client.close()
