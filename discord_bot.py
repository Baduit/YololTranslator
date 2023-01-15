#!/usr/bin/env python3

import platform
import discord
import sys

from core.build.yolol import Translator


yolol = Translator(word_to_phonem_file='core/assets/french_dico.json', phonem_to_chars_file='core/assets/fr.dict', word_to_word_file='core/assets/word_to_word_dict_fr.json')

yolol_prefix = '!yolol '

intents = discord.Intents.default()
intents.message_content = True

client = discord.Client(intents=intents)

@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')

@client.event
async def on_message(message):
    if message.author == client.user:
        return

    if message.content.startswith(yolol_prefix):
        message_to_translate = message.content[len(yolol_prefix):]
        translation = yolol.translate(message_to_translate)
        await message.channel.send(translation)


secret_path_file = sys.argv[1]

with open(secret_path_file) as f:
    secret = f.read()

client.run(secret)
