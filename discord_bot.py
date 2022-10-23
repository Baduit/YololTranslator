#!/usr/bin/env python3

import platform
import discord
import sys

from core.Yolol import YololTranslator

# Ugly but it works for now
if platform.system() == "Windows":
	lib_path = 'core/build/src/Debug/YololTranslator'
else:
	lib_path = 'core/build/src/libYololTranslator.so'
yolol = YololTranslator(lib_path)

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
