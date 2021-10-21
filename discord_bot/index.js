import WebSocket from 'ws';
import * as YololSDK from '../nodejs_sdk/YololSDK.mjs'

let client = new YololSDK.Client(WebSocket, "ws://localhost:4577");

// todo discord stuff

console.log("hey")