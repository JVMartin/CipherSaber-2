#!/usr/bin/env python3

# Copyright (c) 2015 Jacob Martin

# A client for sending TauNet Messages.

import sys
import socket

args = sys.argv

# Helpful usage hints.
if len(args) != 2:
	print("usage:")
	print("\tpython3 client.py <message>\n")
	exit()

message = args[1]

target_host = "localhost"
target_port = 6283

target = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
target.connect((target_host, target_port))
target.send(message.encode())
target.close()
