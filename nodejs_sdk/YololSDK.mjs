export class Client {
	constructor (WebSocket, ws_host) {
		this.next_request_id = 0;
		this.request_promises = new Map();
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

		// Todo handle automatic reconnection
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
				this.request_promises.delete(current_request_id);
				reject("Timeout after 10s");
			}, 10 * 1000);
		});
		this.request_promises.set(current_request_id, resolver);

		this.next_request_id++;
		return p;
	}
}
