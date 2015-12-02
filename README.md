TauNet Client Application
=========================
Copyright (c) 2015 Jacob Martin

The TauNet client application can be used to send messages to and receive messages
from other TauNet client applications.

Installation
------------
Compile the provided CipherSaber-2 encryption tool using:
```bash
gcc cs2.c -o cs2
```

The Python scripts depend upon this tool being compiled.

Install the client table by first copying the example:
```bash
cp clients.json.example clients.json
```

...and then edit the table to add your key and client list while following
the given format.

You are now ready to use the application.

Usage
-----
