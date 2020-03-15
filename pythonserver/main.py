import socket
from dataprocessor import *
from rtmidihandler import *

print("Initializing the server.")
HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)

dp = DataProcessor(scale_name="D#m", scale_type=1)
rt = RtMidi(port=2)
print("Server is up and listening")

with rt.midiout:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                else:
                    rt.send_signal(dp.process_data(data))
                conn.sendall(data)

