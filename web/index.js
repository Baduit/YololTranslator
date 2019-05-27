const port = 4910;

var exec = require('child_process').exec;

var app = require('express')();

const bodyParser = require('body-parser');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }))

app.route('/').get(function(req, res) { 
    res.status(200).send('Welcome on Yolol Translator API! Send a POST request on /translate with the text you want to translate in a parameter named "text".'); 
});

app.route('/translate').post(function(req, res) {
	if (!req.body.text)
		return res.status(400).send('You need to specify the "text" parameter.');
	exec('../YololTranslator.exe "' + req.body.text + '" ../dico/', (error, stdout, stderr) => {
		res.status(200).send(stdout);
	});
}); 

app.listen(port);

console.log("Server is running on port: " + port);