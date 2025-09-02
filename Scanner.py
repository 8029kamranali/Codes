import socket

ip=input("Enter IP to Scan: ")
for port in range(1,1025):
    server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server.settimeout(1)
    result=server.connect_ex((ip,port))
    if result==0:
        print(f"{port} is OPEN")
    server.close()

