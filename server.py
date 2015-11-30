#!/usr/bin/env python3

# Copyright (c) 2015 Jacob Martin

# A server for receiving TauNet Messages.

import socket

print("Initializing server.")

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind(("localhost", 6283))
serversocket.listen(5)

print("Listening on port 6283.")

while True:
	(clientsocket, address) = serversocket.accept()
	ct = client_thread(clientsocket)
	ct.run()