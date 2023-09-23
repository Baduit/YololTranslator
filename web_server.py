#!/usr/bin/env python3

import platform

from fastapi import FastAPI, WebSocket
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel

from core.build.yolol import Translator


yolol = Translator(word_to_phonem_file='core/assets/french_dico.json', phonem_to_chars_file='core/assets/fr.dict', word_to_word_file='core/assets/word_to_word_dict_fr.json')

class TextToTranslate(BaseModel):
    text: str

app = FastAPI()

@app.post("/translate")
async def translate(text: TextToTranslate):
	return yolol.translate(text.text)

@app.websocket("/ws/translate")
async def websocker_translate(websocket: WebSocket):
      await websocket.accept()
      while True:
            data = await websocket.receive_text()
            await websocket.send_text(yolol.translate(data))

app.mount("/", StaticFiles(directory="public", html=True), name="Yolol")