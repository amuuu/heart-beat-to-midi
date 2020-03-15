import rtmidi


class RtMidi():
    def __init__(self, port):
        self.port = port
        
        self.midiout = rtmidi.MidiOut()
        self.available_ports = self.midiout.get_ports()
        
        print(self. available_ports)
        if self.available_ports:
            self.midiout.open_port(self.port)
        else:
            self.midiout.open_virtual_port("Virtual output")