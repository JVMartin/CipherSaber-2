#!/usr/bin/env python3

# Copyright (c) 2015 Jacob Martin

# A client for sending TauNet Messages.

import sys
import os
import socket
from subprocess import call

target_host = "localhost"
target_port = 6283
key         = "password"

args = sys.argv

# Helpful usage hints.
if len(args) != 2:
	print("usage:")
	print("\tpython3 client.py <message>\n")
	exit()

message = args[1]

with open("message", "w") as messageFile:
	messageFile.write(message)

call(["./cs2", "encrypt", key, "message", "encrypted"])
os.remove("message")

target = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
target.connect((target_host, target_port))

with open("encrypted", "rb") as encryptedFile:
	target.send(encryptedFile.read(1024))

target.close()
os.remove("encrypted")
