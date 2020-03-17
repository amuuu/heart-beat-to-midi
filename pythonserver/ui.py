from tkinter import *

window = Tk()
window.title("Heart Beats to MIDI")
window.geometry('350x200')


scale_name_lbl = Label(window, text="Scale Name")
scale_name_lbl.grid(column=0, row=0)
scale_name = Entry(window,width=10)
scale_name.grid(column=1, row=0)

scale_type_lbl = Label(window, text="Scale Type")
scale_type_lbl.grid(column=0, row=1)
scale_type = Entry(window,width=10)
scale_type.grid(column=1, row=1)

midi_port_lbl = Label(window, text="MIDI Port")
midi_port_lbl.grid(column=0, row=2)
midi_port = Entry(window,width=10)
midi_port.grid(column=1, row=2)

midi_channel_lbl = Label(window, text="MIDI Channel")
midi_channel_lbl.grid(column=0, row=3)
midi_channel = Entry(window,width=10)
midi_channel.grid(column=1, row=3)

result_lbl = Label(window, text="")
result_lbl.grid(column=0, row=5)


def clicked():
    res = "Welcome to " + scale_name.get() + " and " + scale_type.get() + " and " + midi_port.get() + " and " + midi_channel.get()
    result_lbl.configure(text= res)

btn = Button(window, text="Click Me", command=clicked)
btn.grid(column=0, row=4)

window.mainloop()