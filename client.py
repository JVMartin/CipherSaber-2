#!/usr/bin/env python3

# Copyright (c) 2015 Jacob Martin

# A client for sending TauNet Messages.

import socket


target_host = "localhost"
target_port = 6283

target = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
target.connect((target_host, target_port))
target.send("Hello there.".encode())
target.close()
