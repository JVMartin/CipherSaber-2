TauNet Client Application
=========================
Copyright (c) 2015 Jacob Martin

The TauNet client application can be used to send messages to and receive messages
from other TauNet client applications.

Installation
------------
First, ensure you have `gcc` installed and that `/dev/urandom` is working (is
readable and outputs pseudorandom bytes.)

Compile the provided CipherSaber-2 encryption tool using:
```bash
gcc cs2.c -o cs2
```

The Python scripts depend upon this tool being compiled.

Install the client table by first copying the example:
```bash
cp clients.json.example clients.json
```

...and then edit `clients.json` to add your key, username, and client list while
following the provided format.

You are now ready to use the application.

Usage
-----
To *receive* incoming messages, start the receive command using:
```bash
./receive.py
```

The command will continue to run and will display any messages it receives
as soon as it receives them.

To *send* an outgoing message, use the command:
```bash
./send.py <username> <message>

# Examples:
./send.py bart "Hey, how are you?"
./send.py jacob "I'll be there in 10 minutes."
```
