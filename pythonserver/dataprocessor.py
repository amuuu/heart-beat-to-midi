from util import *
import numpy as np


class DataProcessor():
    # scale_type 0:none /1:major /2:minor
    scale_type = 1 # the place for this should change
    scale_name = "D#m" # the place for this should change too.
    notes = []

    def __init__(self, scale_name, scale_type):
        self.scale_type = scale_type # this should be calculated based on the scale name. (M or m)
        self.scale_name = scale_name.lower().rsplit('m',1)[0]
        self.notes = compute_scale_notes(self.scale_name, self.scale_type)

    def process_data(self, data):
        unit_size=400/(max_midi_note-min_midi_note) # this should be tuned 
        value=(int)(data/unit_size)+min_midi_note 
        
        # quantize the value for minor/major scale
        if self.scale_type != 0:
            idx = (np.abs(notes-value)).argmin()
            value = self.notes[idx]
