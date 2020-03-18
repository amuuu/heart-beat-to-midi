import socket
from dataprocessor import *
from rtmidihandler import *

HOST = '192.168.43.26'  # Your local network IP
PORT = 80

print("Initializing the server on", HOST, ":", PORT)
dp = DataProcessor(scale_name="D#m", scale_type=1)
rt = RtMidi(port=2, channel=1)
print("Server is up and listening...")

with rt.midiout:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        while True:
            conn, addr = s.accept()
            try:
            # with conn:
                print('Connected by', addr)
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    else:
                        rt.send_signal(dp.process_data(data.split("oded\r\n\r\n",1)[1])) # pick the value from the request sent from arduino,
                                                                                         # process it, and send out midi signal.

                    # conn.sendall(data)
            finally:
                conn.close()


rt.midiout.close_port()
del rt.midiout