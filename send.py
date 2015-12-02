#!/usr/bin/env python3

"""
Copyright (c) 2015 Jacob Martin

A command for sending TauNet Messages.
"""

import sys
import os
import socket
from subprocess import call
from clienttable import ClientTable

args = sys.argv

# Helpful usage hints.
if len(args) != 3:
	print("usage:")
	print("\tpython3 client.py <username> <message>")
	exit()

client_table = ClientTable()
try:
	target_host = client_table.clients[args[1]]
except KeyError:
	print("That client does not exist in the table.")
	exit()

target_port = 6283
message     = args[2]

with open("message", "w") as messageFile:
	messageFile.write(message)

call(["./cs2", "encrypt", client_table.key, "message", "encrypted"])
os.remove("message")

target = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
target.connect((target_host, target_port))

with open("encrypted", "rb") as encryptedFile:
	target.send(encryptedFile.read(1024))

target.close()
os.remove("encrypted")
