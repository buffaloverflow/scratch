import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12345))
server_socket.listen(1)

name = input("[ ] Enter your name: ")

while True:
    print("[ ] Waiting for connection...")
    client_socket, client_address = server_socket.accept()
    print(f'[!] Accepted connection from {client_address[0]}')
    client_socket.sendall(bytes("Welcome to " + name + "'s chat server!", "utf-8"))
    while True:
        data = client_socket.recv(1024)
        if not data:
            break
        elif data.decode() == "Bye!":
            break
        print(f"[{client_address[0]}]: {data.decode()}")
        data = input("[ ] ")
        client_socket.sendall(bytes(data, "utf-8"))
    client_socket.close()
