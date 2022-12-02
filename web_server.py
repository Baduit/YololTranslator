#!/usr/bin/env python3

import platform

from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel

from core.Yolol import YololTranslator


# Ugly but it works for now
if platform.system() == "Windows":
	lib_path = 'core/build/src/Debug/YololTranslator'
else:
	lib_path = 'core/build/src/libYololTranslator.so'
yolol = YololTranslator(lib_path)

class TextToTranslate(BaseModel):
    text: str

app = FastAPI()

@app.post("/translate")
async def guess_pokemon(text: TextToTranslate):
	return yolol.translate(text.text)

app.mount("/", StaticFiles(directory="public", html=True), name="Yolol")