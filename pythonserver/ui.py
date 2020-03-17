from tkinter import *

window = Tk()
window.title("Heart Beats to MIDI")
window.geometry('350x200')
padx, pady = 10, 5
# window.pack(fill=BOTH, expand=True)

frame1 = Frame(window)
frame1.pack(fill=X)

# scale name
scale_name_lbl = Label(frame1, text="Scale Name")
scale_name_lbl.grid(column=0, row=0, padx=padx, pady=pady)
scale_name = Entry(frame1,width=10)
scale_name.grid(column=1, row=0, padx=padx, pady=pady)

# scale type
scale_type_lbl = Label(frame1, text="Scale Type")
scale_type_lbl.grid(column=0, row=1, padx=padx, pady=pady)
default_scale_type_txt = StringVar(frame1, value='1')
scale_type = Entry(frame1,width=10, textvariable=default_scale_type_txt)
scale_type.grid(column=1, row=1, padx=padx, pady=pady)

# MIDI port
midi_port_lbl = Label(frame1, text="MIDI Port")
midi_port_lbl.grid(column=0, row=2, padx=padx, pady=pady)
default_midi_port_txt = StringVar(frame1, value='2')
midi_port = Entry(frame1,width=10, textvariable=default_midi_port_txt)
midi_port.grid(column=1, row=2, padx=padx, pady=pady)

# MIDI channel
midi_channel_lbl = Label(frame1, text="MIDI Channel")
midi_channel_lbl.grid(column=0, row=3, padx=padx, pady=pady)
default_midi_channel_txt = StringVar(frame1, value='1')
midi_channel = Entry(frame1,width=10, textvariable=default_midi_channel_txt)
midi_channel.grid(column=1, row=3, padx=padx, pady=pady)

frame2 = Frame(window)
frame2.pack(fill=X)

# result
result_lbl = Label(frame2, text="", justify=LEFT)
result_lbl.grid(column=0, row=5, padx=padx, pady=pady)


def clicked():
    res = "Welcome to " + scale_name.get() + " and " + scale_type.get() + " and " + midi_port.get() + " and " + midi_channel.get()
    result_lbl.configure(text= res)

btn = Button(frame1, text="Click Me", command=clicked)
btn.grid(column=0, row=4, pady=pady)

window.mainloop()