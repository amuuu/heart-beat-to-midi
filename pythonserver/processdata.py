from util import *

# scale_type 0:none /1:major /2:minor
scale_type = 1 # the place for this should change

def process_data(data):
    unit_size=400/(max_midi_note-min_midi_note) 
    value=(int)(data/unit_size)+min_midi_note # this should be tuned
    
    # quantize the value for minor/major scale
    if scale_type != 0:
        idx = (np.abs(notes-value)).argmin()
        value = notes[idx]

