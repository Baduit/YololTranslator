var exec = require('child_process').execFile;

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


function exec_v1(message, sentence)
{
	if (!(sentence === "")) {
		exec('../core/v1/YololTranslator.exe', [ sentence, DICO_V1_PATH], (error, stdout, stderr) => {
			message.channel.send(stdout)
		});
	} else {
		message.channel.send(EMPTY_MESSAGE_ANSWER)
	}
}

bot.on('message', (message) => {
	try {
		const cmd_name = "!yolol "
		const v1_cmd_name = "!yolol-v1 "
		const v2_cmd_name = "!yolol-v2 "
		if (message.content.search(cmd_name) == 0) {
			let sentence = extract_usefull_content(message.content, cmd_name)
			exec_v1(message, sentence)
		} else if (message.content.search(v1_cmd_name) == 0) {
			let sentence = extract_usefull_content(message.content, v1_cmd_name)
			exec_v1(message, sentence)
		} else if (message.content.search(v2_cmd_name) == 0) {
			message.channel.send("not implemented yet");
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
 
fs.readFile(require('os').homedir() + '/bot_tokens/yolol', 'utf8', function(err, contents) {
	if (err) {
		console.log(err)
	} else {
		bot.login(contents.trim())
		console.log("running")
	}
});
