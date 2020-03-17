import rtmidi

from signalthread import *


class RtMidi():
    def __init__(self, port, channel):
        self.port = port
        self.channel = channel

        self.midiout = rtmidi.MidiOut()
        self.available_ports = self.midiout.get_ports()
        
        print(self.available_ports)
        if self.available_ports:
            self.midiout.open_port(self.port)
        else:
            self.midiout.open_virtual_port("Virtual output")

    def send_signal(self, value):
        play_thread = midi_signal_thread(self.midiout, value)
        play_thread.start()