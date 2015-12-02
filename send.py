#!/usr/bin/env python3

"""
Copyright (c) 2015 Jacob Martin

A command for sending TauNet Messages.
"""

import sys
import os
import socket
from subprocess import call
from taunet import *

args = sys.argv

# Helpful usage hints.
if len(args) != 3:
	print("usage:")
	print("\tpython3 client.py <username> <message>")
	exit()

to_username = args[1]

# Fetch the target host from the client table using the username argument.
try:
	target_host = client_table.clients[to_username]
except KeyError:
	print("That client does not exist in the table.")
	exit()

target_port = 6283
message     = args[2]

# Construct the message.

# Write the message to a file.
with open("message", "w") as messageFile:
	messageFile.write("""\
version: %s
from: %s
to: %s

%s""" % (version, client_table.username, to_username, message))

call(["./cs2", "encrypt", client_table.key, "message", "encrypted"])
os.remove("message")

target = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
target.connect((target_host, target_port))

with open("encrypted", "rb") as encryptedFile:
	target.send(encryptedFile.read(1024))

target.close()
os.remove("encrypted")
