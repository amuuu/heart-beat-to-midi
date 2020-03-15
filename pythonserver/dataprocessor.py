from util import *

# scale_type 0:none /1:major /2:minor
scale_type = 1 # the place for this should change
scale_name = "D#m" # the place for this should change too.
notes = []

def process_data(data):
    unit_size=400/(max_midi_note-min_midi_note) # this should be tuned 
    value=(int)(data/unit_size)+min_midi_note 
    
    # quantize the value for minor/major scale
    if scale_type != 0:
        idx = (np.abs(notes-value)).argmin()
        value = notes[idx]


def init_processor(scale_name, scale_type):
    scale_name = args['scale'].lower().rsplit('m',1)[0]
    notes = compute_scale_notes(scale_name, scale_type)
