#!/usr/bin/env python3

"""
Copyright (c) 2015 Jacob Martin

A command for receiving TauNet Messages.
"""

import socket
import os
from subprocess import call
from taunet import *

host = socket.gethostname()
port = 6283
key  = client_table.key

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind((host, port))
serversocket.listen(5)

print("Listening on " + host + ":" + str(port) + "...")

while True:
	(clientsocket, address) = serversocket.accept()
	print("Receiving a connection from %s" + str(address))
	with open("received", "wb") as receivedFile:
		receivedFile.write(clientsocket.recv(1024))

	call(["./cs2", "decrypt", key, "received", "decrypted"])
	os.remove("received")

	with open("decrypted", "r") as decryptedFile:
		message = decryptedFile.read()
		print("Message: " + message)
	clientsocket.close()
	os.remove("decrypted")
