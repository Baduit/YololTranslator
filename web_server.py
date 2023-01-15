#!/usr/bin/env python3

import platform

from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel

from core.build.Debug.yolol import Translator


yolol = Translator(word_to_phonem_file='core/assets/french_dico.json', phonem_to_chars_file='core/assets/fr.dict', word_to_word_file='core/assets/word_to_word_dict_fr.json')

class TextToTranslate(BaseModel):
    text: str

app = FastAPI()

@app.post("/translate")
async def guess_pokemon(text: TextToTranslate):
	return yolol.translate(text.text)

app.mount("/", StaticFiles(directory="public", html=True), name="Yolol")