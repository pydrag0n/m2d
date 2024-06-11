import socket
import message_printer

mp = message_printer.MessagePrinter()



server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("localhost", 8080))

server_socket.listen(5)

print("==Server started. Waiting for connections...")

while True:
    connection, address = server_socket.accept()
    mp.info_message(f"Connected by {address}")
    message = connection.recv(1024).decode()

    if not message=="" or not message==" ":
        response = "OK"
    else:
        response = "ERROR"

    connection.sendall(response.encode())

    connection.close()