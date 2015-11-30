"""
Copyright (c) 2015 Jacob Martin

The ClientTable class is a data structure that reads the clients.json file
into its members and makes them accessible.
"""

import json

class ClientTable:

	def __init__(self):
		try:
			with open("clients.json") as json_file:
				clientTable = json.load(json_file)
			self.key     = clientTable["key"]
			self.clients = clientTable["clients"]
		except FileNotFoundError:
			print("The client table file is missing.")
