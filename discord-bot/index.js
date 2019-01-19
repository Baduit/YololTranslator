const exec = require('child_process').exec;

const Discord = require('discord.js')
const bot = new Discord.Client()

function extract_usefull_content(message_content, command_name) {
	let i = command_name.length;
	while (i < message_content.length) {
		if (message_content[i] != ' ' && message_content[i] != '\t')
			break;
		i++;
	}
	return message_content.substr(i, message_content.length)
}

bot.on('message', function (message) {
	const cmd_name = "!yolol"
    if (message.content.search(cmd_name) == 0) {
		let sentence = extract_usefull_content(message.content, cmd_name)
		if (!(sentence === "")) {
			exec('../YololTranslator.exe "' + sentence + '" ../dico/', (error, stdout, stderr) => {
				message.channel.send(stdout)
			});
		} else {
			message.channel.send('Please, do not send empty an empty sentence, it is even more useless than this bot.')
		}
    }
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
