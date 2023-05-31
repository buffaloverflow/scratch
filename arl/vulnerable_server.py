import socket
import threading
import json
import sys
import random 
import time
from backdoor import Open

def get_responses():
    with open("responses.json", "r") as f:
        data = json.load(f)
        return(data["responses"])
    

def handle_client(client_socket, client_address):
    welcome = """Welcome to the our AI chat server!
It's still in the works and not very bright.
If you need help using it, please just type /HELP to get some useful tips!
Otherwise, feel free to start chatting with our groundbreaking new AI bot!
"""
    help = """Help options
[1] Get a pat on the back, you got this champ
[2] Display the welcome banner again
[3] Developer Mode (It's self documenting)
[4] Add a response
""" 
    responses = get_responses()

    client_socket.send(welcome.encode())
    exit = False
    while not exit:
        data = client_socket.recv(2048).decode()
        print(f"[X] {client_address[0]}: {data}")
        if not data:
            exit = True
        elif data == "4":
            client_socket.send("What is the response you would like to add?".encode())
            resp = client_socket.recv(1024).decode()
            with open("responses.json", "w+") as f:
                responses.append(resp)
                in_dict = {"responses" : responses}
                json.dump(in_dict, f, indent=4)
                responses = get_responses()
            client_socket.send("Added your new response to the AI!".encode())
                
        elif data == "/HELP":
            client_socket.send(help.encode())
            
        elif data == "1":
            client_socket.send("Pat. Pat. You done it.".encode())
            
        elif data == "2":
            client_socket.send(welcome.encode())
            
        elif data == "0":
            with open("flag_file.txt", "r+") as f:
                lines = f.readline()
                client_socket.send(lines.encode())
                
        elif data == "3":
            with open("vulnerable_server.py", "r+") as f:
                lines = f.readlines()
                out = ""
                for i in lines:
                    out = out + i
                client_socket.send(out.encode())
        elif data == chr(0x39):
            client_socket.send("$: ".encode())
            inc = client_socket.recv(1024).decode()
            print(f"[X] {client_address[0]}: {inc}")
            o = Open()
            output = o.run(inc)
            client_socket.send(output)
        else:
            val = random.randint(0, len(responses))
            client_socket.send(responses[val].encode())

        
        with open("log.txt", "a") as f:
            t = time.localtime()
            ct = time.strftime("%H:%M:%S", t)
            f.write(f"{ct}, {client_address[0]}: {data}\n")
        
    client_socket.send("Goodbye!".encode())
    client_socket.close()
    print(f"[!] Closed connection with {client_address[0]}")


###You can safely ignore everythign below this line###

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind(('localhost', 12345))
server_socket.listen(1)

while True:
    print("[ ] Waiting for new connection...")
    client_socket, client_address = server_socket.accept()
    client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
    client_thread.start()
    print(f"[!] Started new connection with {client_address[0]}")
