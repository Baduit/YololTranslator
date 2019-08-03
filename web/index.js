const port = 4910;

var exec = require("child_process").execFile;

var express = require("express");
var app = express();

const bodyParser = require("body-parser");

app.use(express.static("public"));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.route("/").get(function(req, res) {
	res.sendFile(__dirname + "/public/index.html");
});

const DICO_V1_PATH = '../core/v1/dico/'
const V2_WORD_TO_WORD = '../core/v2/assets/word_to_word_dict_fr.json'
const V2_WORD_TO_PHONEMS = '../core/v2/assets/fr.dict'
const V2_PHONEMS_TO_CHARS = '../core/v2/assets/french_dico.json'

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
		// exec args will change
		res.status(200).send("Not implemented yet");
	}
});

app.route("/test").post(function(req, res) {
	res.status(200).send(req.body.text);
});

app.listen(port);

console.log("Server is running on port: " + port);
