var exec = require('child_process').execFile;

const ref = require('ref');
var ffi = require('ffi');

// LibYololHandling
const V2_WORD_TO_WORD = '../core/v2/assets/word_to_word_dict_fr.json'
const V2_WORD_TO_PHONEMS = '../core/v2/assets/fr.dict'
const V2_PHONEMS_TO_CHARS = '../core/v2/assets/french_dico.json'

var libYolol = ffi.Library('../core/v2/libYololTranslator', {
	'init': ['int', ['string', 'string', 'string']],
	'translate': ['void*', ['string']],
	'delete_string': ['void', ['void*']],
	'destroy': ['void', []]
});
if (libYolol.init(V2_PHONEMS_TO_CHARS, V2_WORD_TO_PHONEMS, V2_WORD_TO_WORD) == 0) {
	throw Error("Error while initializing libYolol")
}

// Proper cleanup
process.on('exit', function () {
	libYolol.destroy()
});

const Discord = require('discord.js')
const bot = new Discord.Client()

let nbError = 0;
let nbException = 0;

function extract_usefull_content(message_content, command_name) {
	let i = command_name.length;
	while (i < message_content.length) {
		if (message_content[i] != ' ' && message_content[i] != '\t')
			break;
		i++;
	}
	return message_content.substr(i, message_content.length)
}

const EMPTY_MESSAGE_ANSWER = 'Please, do not send empty an empty sentence, it is even more useless than this bot.'
const DICO_V1_PATH = '../core/v1/dico/'


function exec_v1(message, sentence) {
	if (!(sentence === "")) {
		exec('../core/v1/YololTranslator.exe', [sentence, DICO_V1_PATH], (error, stdout, stderr) => {
			message.channel.send(stdout)
		});
	} else {
		message.channel.send(EMPTY_MESSAGE_ANSWER)
	}
}

function translate_v2(message, sentence) {
	var translated_sentence = libYolol.translate(sentence);
	if (translated_sentence == null) {
		message.channel.send("Invalid input");
	} else {
		message.channel.send(ref.readCString(translated_sentence, 0));
		libYolol.delete_string(translated_sentence);
	}
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
		const v1_cmd_name = "!yolol-v1 "
		const v2_cmd_name = "!yolol-v2 "
		const vdd_cmd_name = "!vdd"
		if (message.content.search(cmd_name) == 0) {
			let sentence = extract_usefull_content(message.content, cmd_name)
			translate_v2(message, sentence)
		} else if (message.content.search(v1_cmd_name) == 0) {
			let sentence = extract_usefull_content(message.content, v1_cmd_name)
			exec_v1(message, sentence)
		} else if (message.content.search(v2_cmd_name) == 0) {
			let sentence = extract_usefull_content(message.content, v2_cmd_name)
			translate_v2(message, sentence)
		} else if (message.content.search(vdd_cmd_name) == 0) {
			translate_vdd(message);
		}
	} catch (exception) {
		nbException++;
		console.log(exception);
	}
})

bot.on('message', (message) => {
	try {
		const cmd_name = "!log-yolol"
		if (message.content.search(cmd_name) == 0) {
			message.channel.send('Errors: ' + nbError + '\nExceptions: ' + nbException)
		}
	} catch (exception) {
		nbException++;
		console.log(exception);
	}
})


bot.on('error', (error) => {
	nbError++;
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
