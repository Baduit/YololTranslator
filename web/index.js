const port = 4910;

class YololClient
{
	// todo
};

var express = require("express");
var app = express();

// App init
app.use(express.static("public"));
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Routes
app.route("/").get(function(req, res) {
	res.sendFile(__dirname + "/public/index.html");
});

app.route("/assets/vue").get(function(req, res) {
	res.sendFile(__dirname + "/node_modules/vue/dist/vue.min.js");
});


app.route("/translate").post(function(req, res)
{
	if (!req.body.text)
		return res.status(400).send('You need to specify the "text" parameter.');

	// todo call YololSDK
});

app.route("/test").post(function(req, res) {
	res.status(200).send(req.body.text);
});

// Start
app.listen(port);

console.log("Server is running on port: " + port);
