import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12345))
data = client_socket.recv(1024)
print(data.decode())

while True:
    message = input('Enter message: ')
    if not message:
        break
    client_socket.sendall(message.encode())
    data = client_socket.recv(1024*5)
    print(f'Received: {data.decode()}')

client_socket.close()