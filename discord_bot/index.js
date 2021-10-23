// Init Yolol
import WebSocket from 'ws';
import * as YololSDK from '../nodejs_sdk/YololSDK.mjs'

let yololClient = new YololSDK.Client(WebSocket, "ws://localhost:4577");

// Init Discord
import { Client, Intents } from 'discord.js';
import { token } from './config.json';

const bot = new Client({ intents: [Intents.FLAGS.GUILDS] });
bot.once('ready', () => {
	console.log('Ready!');
});

function extract_usefull_content(message_content, command_name) {
	let i = command_name.length;
	while (i < message_content.length) {
		if (message_content[i] != ' ' && message_content[i] != '\t')
			break;
		i++;
	}
	return message_content.substr(i, message_content.length)
}

function translate_v2(message, sentence) {
	yololClient.translate(req.body.text).then((translation) => {
		message.channel.send(ref.readCString(translation, 0));
	}).catch((error) => {
		message.channel.send(error);
	});
}

async function translate_vdd(message) {
	try {

		let message_map = await message.channel.fetchMessages({ limit: 10 });
		let messages = message_map.array();
		let my_message_found = false;
		for (let i = 0; i < messages.length; ++i) {
			if (my_message_found) {
				translate_v2(message, messages[i].content);
				break;
			} else if (messages[i].id == message.id) {
				my_message_found = true;
			}
		}
	} catch (e) {
		++nbException;
	}
}

bot.on('message', (message) => {
	try {
		if (message.author.bot) {
			return;
		}

		const cmd_name = "!yolol "
		const vdd_cmd_name = "!vdd"
		if (message.content.search(cmd_name) == 0) {
			let sentence = extract_usefull_content(message.content, cmd_name)
			translate_v2(message, sentence)
		} else if (message.content.search(vdd_cmd_name) == 0) {
			translate_vdd(message);
		}
	} catch (exception) {
		nbException++;
		console.log(exception);
	}
})


bot.on('error', (error) => {
	console.log(error)
})

var fs = require('fs');

fs.readFile(require('os').homedir() + '/bot_tokens/yolol', 'utf8', function (err, contents) {
	if (err) {
		console.log(err)
	} else {
		bot.login(contents.trim())
		console.log("running")
	}
});

// Login to Discord with your client's token
client.login(token);

console.log("hey")