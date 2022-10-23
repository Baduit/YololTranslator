import ctypes

word_to_phonem = b'core/assets/fr.dict'
word_to_word = b'core/assets/word_to_word_dict_fr.json'
phonems_to_chars = b'core/assets/french_dico.json'

class YololTranslation(ctypes.Structure):
	_fields_ = [
		('size', ctypes.c_int),
		('translation', ctypes.c_char_p)
	]

class YololTranslator:
	def __init__(self, lib_path) -> None:
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