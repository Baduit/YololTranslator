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

		#T = tk.Text(root, height=2, width=30)
		self.input_widget = tk.Text(self.main_form)
		self.input_widget.bind('<KeyRelease>', self.on_text_entered)
		self.input_widget.grid(row = 0, column = 0)

		self.output_widget = tk.Text(self.main_form)
		self.output_widget.grid(row = 0, column = 1)
		self.output_widget.insert(tk.END, 'here the translated text')
		self.output_widget.config(state = 'disabled')

		self.main_form.geometry("1500x500")

		self.key_has_been_pressed = False

		self.main_form.after(500, self.update_translated_text)

	def modify_output_text(self, new_text):
		self.output_widget.config(state = 'normal')
		self.output_widget.delete('1.0', tk.END)
		self.output_widget.insert(tk.END, new_text)
		self.output_widget.config(state = 'disabled')

	def on_text_entered(self, event):
		self.key_has_been_pressed = True

	def on_version_changed(self, event):
		pass
		# get the entry of the lookup box
		# change the version of self.translator

	def update_translated_text(self):
		self.main_form.after(500, self.update_translated_text)
		if self.key_has_been_pressed:
			text_to_translate = self.input_widget.get('1.0', tk.END)
			translated_text = self.translator.translate(text_to_translate)
			self.modify_output_text(translated_text)
			self.key_has_been_pressed = False
		

	def run(self):
		self.main_form.mainloop()

def main():
	parser = argparse.ArgumentParser(description='Graphical user interface for YololTranslator')
	parser.add_argument('-e', '--endpoint', default='https://yololtranslate-api.baduit.eu/translate', help='The address of the Yolol Translator API used. The default address is the official API.')
	args = parser.parse_args()

	translator = Translator(args.endpoint, 'v2')
	print(translator.translate('salut'))

	gui = GUI(translator)
	gui.modify_output_text('efef')
	gui.run()

if __name__ == "__main__":
	main()