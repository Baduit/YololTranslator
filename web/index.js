// Constants
const port = 4910;

const DICO_V1_PATH = '../core/v1/dico/'
const V2_WORD_TO_WORD = '../core/v2/assets/word_to_word_dict_fr.json'
const V2_WORD_TO_PHONEMS = '../core/v2/assets/fr.dict'
const V2_PHONEMS_TO_CHARS = '../core/v2/assets/french_dico.json'

// Depedencies
var exec = require("child_process").execFile;

const bodyParser = require("body-parser");
var express = require("express");
var app = express();

const ref = require('ref');
var ffi = require('ffi');

// LibYololHandling
var libYolol = ffi.Library('../core/v2/libYololTranslator', {
	'init': [ 'int', [ 'string', 'string', 'string' ] ],
	'translate': [ 'void*', [ 'string' ] ],
	'delete_string': [ 'void', [ 'void*' ] ],
	'destroy': [ 'void', [] ]
});
if (libYolol.init(V2_PHONEMS_TO_CHARS, V2_WORD_TO_PHONEMS, V2_WORD_TO_WORD) == 0)
{
	throw Error("Error while initializing libYolol")
}

// Proper cleanup
process.on('exit', function () {
	libYolol.destroy()
});



// App init
app.use(express.static("public"));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));


// Routes
app.route("/").get(function(req, res) {
	res.sendFile(__dirname + "/public/index.html");
});


app.route("/translate").post(function(req, res)
{
	var version = "v1";
	if (!req.body.text)
		return res.status(400).send('You need to specify the "text" parameter.');

	if (!req.body.version)
	{
		exec(
			"../core/v1/YololTranslator.exe",
			[req.body.text, DICO_V1_PATH],
			(error, stdout, stderr) => {
				res.status(200).send(stdout);
			}
		);
	} else if (req.body.version == "v1") {
		exec(
			"../core/v1/YololTranslator.exe",
			[req.body.text, DICO_V1_PATH],
			(error, stdout, stderr) => {
				res.status(200).send(stdout);
			}
		);
	} else if (req.body.version == "v2") {
		var translated_sentence = libYolol.translate(req.body.text);
		if (translated_sentence == null)
		{
			res.status(200).send("Invalid input");
		}
		else
		{
			res.status(200).send(ref.readCString(translated_sentence, 0));
			libYolol.delete_string(translated_sentence); // maybe better in a then of send
		}
	}
});

app.route("/test").post(function(req, res) {
	res.status(200).send(req.body.text);
});

// Start
app.listen(port);

console.log("Server is running on port: " + port);
