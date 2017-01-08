"use strict";

let express = require('express');
let app = express();
let http = require('http').Server(app);
let ws = require("nodejs-websocket");

// START : INIT CONNCETORS //////////////////////////////
//init connectors
let shiftr = require("./connectors/shiftr.module");
shiftr.init(openBottle);

let thingspeak = require("./connectors/thingspeak.module");
thingspeak.init(openBottle);

// END : INIT CONNCETORS //////////////////////////////

let bodyParser = require('body-parser');
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({extended: true})); // support encoded bodies

app.use(express.static('./public/'));
app.use(express.static('./node_modules/'));
app.get('/', function (req, res) {
	res.sendfile("public/index.html");
});

/**
 * Server itself
 * @type {http.Server}
 */
let server = app.listen(8090, function () {
	//print few information about the server
	let host = server.address().address;
	let port = server.address().port;
	console.log("Server running and listening @ " + host + ":" + port);
});

let serverws = ws.createServer(function (conn) {
	console.log("New connection");

	conn.on("text", function (str) {
		console.log("Received " + str);
	});

	conn.on("close", function (code, reason) {
		console.log("Connection closed");
	})
}).listen(8081);

/** list of current connected drinkers */
let drinkers = [
	{
		"name": "Gwen",
		"quantity": 0,
		"platforms": []
	},
	{
		"name": "Adrien",
		"quantity": 0,
		"platforms": []
	}
];

/**
 * Try to find the drinker with that name in the database (here : the list) or create a new one.
 * @param name
 * @returns {*}
 * @private
 */
function _getDrinkerByName(name) {
	let drinker = null;
	for (drinker of drinkers) {
		if (name === drinker.name) {
			return drinker;
		}
	}

	//no drinker ? create a new one
	let newDrinker = {"name": name, "quantity": 0, "platforms": []};
	drinkers.push(newDrinker);

	return newDrinker;
}

function _setPlatformQuantityByDrinkerAndName(drinker, platformName, quantity) {
	let platform = null;
	for (platform of drinker.platforms) {
		if (platformName === platform.name) {
			platform.quantity = quantity;
			return;
		}
	}

	//no platform ? create a new one
	let newPlatform = {"name": platformName, "quantity": quantity};
	drinker.platforms.push(newPlatform);
}

/**
 * Send new values to the front end.
 * Called by each connector when they received a message from their platform.
 *
 * @param drinkerName
 * @param quantity
 * @param platform
 */
function openBottle(drinkerName, quantity, platform) {

	let drinker = _getDrinkerByName(drinkerName);
	//let oldQty = parseInt(drinker.quantity);
	drinker.quantity = /*oldQty +*/ quantity;

	_setPlatformQuantityByDrinkerAndName(drinker, platform, quantity);

	console.log(drinker.name + " opened " + drinker.quantity + " bottles.");

	serverws.connections.forEach(function (conn) {
		conn.sendText(JSON.stringify(drinker));
	})
}

/**
 * Get a list of JSON for all registered drinkers
 * @path /drinkers
 * @HTTPMethod GET
 * @returns {string}
 */
app.get("/drinkers", function (req, res) {
	//encode result to Base64 to ensure there is no special character in the string
	//res.send(crypto.encode(cipher));

	res.send(drinkers);
});



