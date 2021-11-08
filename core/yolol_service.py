#!/usr/bin/env python3

import ctypes
import sys
import json

import asyncio
from websockets import serve

class YololTranslation(ctypes.Structure):
	_fields_ = [
		('size', ctypes.c_int),
		('translation', ctypes.c_char_p)
	]


word_to_phonem = b'./assets/fr.dict'
word_to_word = b'./assets/word_to_word_dict_fr.json'
phonems_to_chars = b'./assets/french_dico.json'


class YololTranslator:
	def __init__(self, lib_path) -> None:
		# './build/src/Debug/YololTranslator.dll'
		# './gcc_build/src/libYololTranslator.so'
		self.lib = ctypes.CDLL(lib_path)

		self.lib.yolol_init.argtypes = [
			ctypes.c_char_p,
			ctypes.c_char_p,
			ctypes.c_char_p
		]
		self.lib.yolol_init.restype = None

		self.lib.yolol_destroy.argtypes = []
		self.lib.yolol_destroy.restype = None

		self.lib.yolol_translate.argtypes = [ctypes.c_char_p, ctypes.c_int]
		self.lib.yolol_translate.restype = YololTranslation

		self.lib.yolol_free.argtypes = [YololTranslation]
		self.lib.yolol_free.restype = None

		self.init()

	def init(self):
		self.lib.yolol_init(phonems_to_chars, word_to_phonem, word_to_word)

	def destroy(self):
		self.lib.yolol_destroy()

	def translate(self, str):
		buff = str.encode()
		translation = self.lib.yolol_translate(buff, len(buff))
		res = translation.translation.decode()
		self.lib.yolol_free(translation)
		return res

async def translate(websocket, path):
	async for message in websocket:
		request = json.loads(message)
		translation = yolol.translate(request['text'])
		answer = {
			"text": translation,
			"request_id": request['request_id']
		}
		await websocket.send(json.dumps(answer))

async def main():
	#print(yolol.translate("Salut, comment ça va ?"))
	async with serve(translate, "0.0.0.0", 4577):
		await asyncio.Future()

yolol = YololTranslator(sys.argv[1])
asyncio.run(main())