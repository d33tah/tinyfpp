#!/usr/bin/python

import sys
import socket
import threading
import SocketServer
import time

HOST = "localhost"
PORT = 9991
try:
    PORT = int(sys.argv[1])
except:
    pass

listeners = []

class ThreadedTCPRequestHandler(SocketServer.BaseRequestHandler):

    def handle(self):
        global listeners
        listeners += [ self.request ]
        while True:
            data = self.request.recv(1024)
            #self.rotY, self.rotX, self.xpos, self.zpos = map(float,data.split(' '))
            for listener in listeners:
                try:
                    if listener!=self.request:
                        listener.sendall(data)
                except:
                    pass

class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass

if __name__ == "__main__":

    while PORT>0:
        try:
            server = ThreadedTCPServer((HOST, PORT), ThreadedTCPRequestHandler)
            ip, port = server.server_address
            server_thread = threading.Thread(target=server.serve_forever)
            server_thread.daemon = True
            server_thread.start()
            print "Listening started on %s:%s" % (HOST,PORT)
            break
        except:
            PORT -= 1

    try:
        while True:
            time.sleep(0.01)
            pass
    except KeyboardInterrupt:
        server.shutdown()
