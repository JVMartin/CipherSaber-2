#!/usr/bin/env python3

"""
Copyright (c) 2015 Jacob Martin

A command for receiving TauNet Messages.
"""

import socket
import os
import time
from subprocess import call
from taunet import *

host = socket.gethostname()

# Listen on the set hostname and port.
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serversocket.bind((host, port))
serversocket.listen(5)

print("Listening on " + host + ":" + str(port) + "...")

while True:
	(clientsocket, from_address) = serversocket.accept()
	with open("received", "wb") as receivedFile:
		# Write the raw received bytes to a file.
		receivedFile.write(clientsocket.recv(1024))

	# Discard if the received message is 0 bytes.
	bytes = os.path.getsize("received")
	if bytes < 50:
		os.remove("received")
		continue

	# Decrypt the file and delete the original.
	call(["./cs2", "decrypt", client_table.key, "received", "decrypted"])
	os.remove("received")

	# Open the decrypted file and parse it.
	with open("decrypted", "r") as decryptedFile:
		full_message = decryptedFile.read()
		lines        = full_message.split("\n")

		# Check if the message is malformed or noncompliant.
		if (
				len(lines) < 4 or
				lines[0] != "version: 0.2" or
				not lines[1].startswith("from: ") or
				not lines[2].startswith("to: ") or
				len(lines[3]) # The fourth line must be empty
		   ):
			print("Received malformed message from " + str(from_address))
			print("Malformed message:")
			print(full_message)

		# The message is good, display it.
		else:
			from_username = lines[1][6:]
			message       = "\n".join(lines[4:])

			display   = time.strftime("%x %X") + " "
			display  += "<" + from_username + "> " + message
			print(display)

	clientsocket.close()
	os.remove("decrypted")
