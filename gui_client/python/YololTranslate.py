import argparse
import requests

import tkinter as tk
from tkinter import ttk

class Translator:
	def __init__(self, endpoint, version='v1'):
		self.endpoint = endpoint
		self.version = version

	def translate(self, text_to_translate):
		if text_to_translate == '':
			return ''

		data = {'text': text_to_translate, 'version': self.version}	
		r = requests.post(self.endpoint, data)
		return r.text	

class GUI:
	def __init__(self, translator):
		self.translator = translator

		self.main_form = tk.Tk()
		self.main_form.winfo_toplevel().title('Yolol Translator')
		self.main_form.geometry("1500x500")

		#T = tk.Text(root, height=2, width=30)
		self.input_widget = tk.Text(self.main_form)
		self.input_widget.bind('<KeyRelease>', self.on_text_entered)
		self.input_widget.grid(row = 0, column = 0)

		self.output_widget = tk.Text(self.main_form)
		self.output_widget.grid(row = 0, column = 1)
		self.output_widget.config(state = 'disabled')

		self.action_frame = tk.Frame(self.main_form)
		self.action_frame.grid(row = 0, column = 2)
		
		self.combo_box_version = ttk.Combobox(self.action_frame)
		self.combo_box_version['values'] = ('v1', 'v2')
		if self.translator.version == 'v1':
			self.combo_box_version.current(0)
		elif self.translator.version == 'v2':
			self.combo_box_version.current(1)
		self.combo_box_version.bind("<<ComboboxSelected>>", self.on_version_changed)
		self.combo_box_version.grid()

		self.copy_button = tk.Button(self.action_frame, text = 'copy', command = self.add_translated_text_to_clipboard)
		self.copy_button.grid()

		self.translation_needed = False

		self.main_form.after(500, self.update_translated_text)

	def modify_output_text(self, new_text):
		self.output_widget.config(state = 'normal')
		self.output_widget.delete('1.0', tk.END)
		self.output_widget.insert(tk.END, new_text)
		self.output_widget.config(state = 'disabled')

	def on_text_entered(self, event):
		self.translation_needed = True

	def on_version_changed(self, event):
		if self.translator.version != self.combo_box_version.get():
			self.translator.version = self.combo_box_version.get()
			self.translation_needed = True

	def update_translated_text(self):
		self.main_form.after(500, self.update_translated_text)
		if self.translation_needed:
			text_to_translate = self.input_widget.get('1.0', tk.END)
			translated_text = self.translator.translate(text_to_translate)
			self.modify_output_text(translated_text)
			self.translation_needed = False

	def add_translated_text_to_clipboard(self):
		self.main_form.clipboard_clear()
		self.main_form.clipboard_append(self.output_widget.get('1.0', tk.END))

	def run(self):
		self.main_form.mainloop()

def main():
	parser = argparse.ArgumentParser(description='Graphical user interface for YololTranslator')
	parser.add_argument('-e', '--endpoint', default='https://yololtranslate-api.baduit.eu/translate', help='The address of the Yolol Translator API used. The default address is the official API.')
	args = parser.parse_args()

	translator = Translator(args.endpoint, 'v2')
	gui = GUI(translator)
	gui.run()

if __name__ == "__main__":
	main()