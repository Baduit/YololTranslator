import WebSocket from 'ws';
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import * as YololSDK from '../nodejs_sdk/YololSDK.mjs'

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const port = 4910;

let client = new YololSDK.Client(WebSocket, "ws://localhost:4577");

import express from "express";
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

	client.translate(req.body.text).then((translation) => {
		return res.send(translation);
	}).catch((error) => {
		return res.status(400).send(error);
	});
});

// todo add WS route

// Start
app.listen(port);

console.log("Server is running on port: " + port);
