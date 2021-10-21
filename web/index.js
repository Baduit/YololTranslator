import WebSocket from 'ws';

const port = 4910;

class Client {
	constructor (ws_host) {
		this.next_request_id = 0;
		this.request_promises = new Map();
		this.ws = new WebSocket('ws://localhost:4577'); // replace by ws_host
		this.ws.on('open', () => {
			client.translate("salut").then((translation) => {
				console.log(translation);
			}).catch((error) => {
				console.log(error);
			});
		});

		this.ws.on('message', (message) => {
			console.log('received: %s', message);
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
	}

	translate(text) {
		let current_request_id = this.next_request_id;
		let message = {
			type: "translate",
			text: text,
			request_id: current_request_id
		};
		this.ws.send(JSON.stringify(message));

		let resolver = null;
		let p = new Promise((resolve, reject) => {
			resolver = resolve;
			setTimeout(() => {
				reject("Timeout after 10s");
			}, 10 * 1000);
		});
		this.request_promises.set(current_request_id, resolver);

		this.next_request_id++;
		return p;
	}
}

let client = new Client("ws://localhost:4577");

/* import express from "express";
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

// todo add WS route

// Start
app.listen(port);

console.log("Server is running on port: " + port); */
