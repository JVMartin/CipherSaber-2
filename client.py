#!/usr/bin/env python3

# Copyright (c) 2015 Jacob Martin

# A client for sending TauNet Messages.

import socket


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("localhost", 80))
