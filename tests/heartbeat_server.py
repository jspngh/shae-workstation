import threading
import socket
import json
import struct
import logging
import sys
import time
import datetime


class HeartBeatThread (threading.Thread):
    def __init__(self, threadID):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.quit = False
        self.workstation_ip = None
        self.workstation_port = None

    def run(self):
        if self.workstation_ip is None or self.workstation_port is None:
            return
        print self.workstation_ip
        print self.workstation_port
        print "Running heartbeat thread"
        while not self.quit:
            workstation_socket = socket.socket(socket.AF_INET,      # Internet
                                               socket.SOCK_STREAM)  # TCP
            workstation_socket.connect((self.workstation_ip, self.workstation_port))

            control_socket = socket.socket(socket.AF_UNIX,      # Unix Domain Socket
                                           socket.SOCK_STREAM)  # TCP
            success = True
            try:
                now = time.time()
                localtime = time.localtime(now)
                milliseconds = '%03d' % int((now - int(now)) * 1000)
                timestamp = time.strftime('%Y/%m/%d-%H:%M:%S:', localtime) + milliseconds
                loc = {'Latitude': 51.022658, 'Longitude': 3.709956}
                heart_beat = {'MessageType': 'status', 'Timestamp': timestamp, 'Location': loc, 'Reached WP': 0}
                hb_message = json.dumps(heart_beat)
                print "Heartbeat message: ", hb_message
                workstation_socket.send(bytearray(struct.pack(">H", len(hb_message) + 4)))
                response_length = bytearray(struct.pack(">I", len(hb_message)))
                workstation_socket.send(response_length + hb_message)
                # close the connection
                control_socket.close()
                workstation_socket.close()
            except socket.error:
                success = False

            if success:
                # sleep 500ms before requesting another heartbeat
                time.sleep(0.5)

    def configure(self, ip, port):
        print "configuring the heartbeat thread"
        self.workstation_ip = ip
        self.workstation_port = port

    def stop_thread(self):
        self.quit = False


serversocket = socket.socket(socket.AF_INET,  # Internet
                             socket.SOCK_STREAM)  # TCP
serversocket.bind(("127.0.0.1", 6331))
serversocket.listen(1)  # become a server socket, only 1 connection allowed

heartbeat_thread = HeartBeatThread(0)

while True:
    client, address = serversocket.accept()
    length = client.recv(4)
    if length is not None:
        buffersize = struct.unpack(">I", length)[0]
        raw = client.recv(buffersize)
        packet = json.loads(raw)  # parse the Json we received
        if 'MessageType' not in packet:  # every packet should have a MessageType field
            print "every packet should have a MessageType field"
            raise ValueError
        if 'Message' not in packet:  # every packet should have a Message field
            print "every packet should have a Message field"
            raise ValueError

        message_type = packet['MessageType']
        message = packet['Message']
        config = packet['Configuration']
        ip = config['IpAddress']
        print "IP: {0}".format(ip)
        port = config['Port']
        port = int(port)
        print "port: {0}".format(port)
        heartbeat_thread.configure(ip, port)
        heartbeat_thread.start()
        client.send(struct.pack(">I", 200))
