import socket
public_server_ip = "70.12.108.71"
public_server_port = 10200
public_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
public_socket.connect((public_server_ip, public_server_port))

# RESTROOM_ID = 1
# congestion = 2
# backend_socket.sendall(("congestion,%d,%d,"%(congestion, RESTROOM_ID)).encode())
print("connected")
public_socket.sendall("hihi".encode())
print("wait")
rec = public_socket.recv(1024).decode().strip()
print(rec)

public_socket.close()