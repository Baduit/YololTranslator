import WebSocket from 'ws';

class YololClient {
	constructor (ws_host) {
		this.ws = null
		this.next_request_id = 0;
		this.request_promises = new Map();

		this.connect(ws_host)
	}

	connect(ws_host) {
		if (this.ws) {
			console.log("Connection rejected")
			return
		}

		console.log("Trying to connect")

		this.ws = new WebSocket(ws_host);
		this.ws.on('open', () => {
			console.log("Connected.")
		});
		

		this.ws.on('message', (message) => {
			try {
				let parsed_message = JSON.parse(message);
				let resolver = this.request_promises.get(parsed_message.data.request_id);
				if (resolver) {
					resolver(parsed_message.data.text);
				} else {
					console.log("Unknown request id");
				}
			} catch (error) {
				console.log(error);
			}
		})

		this.ws.on('error', (code, reason) => {
			this.ws = null
			setTimeout(() => { this.connect(ws_host) }, 1000 * 5)
		})
	}

	translate(text) {
		let current_request_id = this.next_request_id;
		let message = {
			type: "translate",
			text: text,
			request_id: current_request_id
		};
		let sended = false
		if (this.ws) {
			this.ws.send(JSON.stringify(message));
			sended = true
		}

		let resolver = null;
		let p = new Promise((resolve, reject) => {
			if (!sended) {
				reject("No connexion")
			}
			resolver = resolve;
			setTimeout(() => {
				this.request_promises.delete(current_request_id);
				reject("Timeout after 10s");
			}, 10 * 1000);
		});
		this.request_promises.set(current_request_id, resolver);

		this.next_request_id++;
		if (this.next_request_id == Number.MAX_SAFE_INTEGER) {
			this.next_request_id = 0
		}
		return p;
	}
}


const port = 4910;

let client = new YololClient("ws://localhost:4577");

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
