#!/usr/bin/env python3

# Copyright (c) 2015 Jacob Martin

# A server for receiving TauNet Messages.

import socket

host = 'localhost'
port = 6283

print("Initializing server.")

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind((host, port))
serversocket.listen(5)

print("Listening on port " + str(port) + "...")

while True:
	(clientsocket, address) = serversocket.accept()
	print("Receiving a connection from %s" + str(address))
	string = clientsocket.recv(1024).decode()
	print("Message: " + string)
	clientsocket.close()