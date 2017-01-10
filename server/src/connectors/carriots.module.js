"use strict";

let https = require('https');


let keys = require("./secretKeys.js");
let mqtt = require('mqtt');

exports.init = function (mainCallback) {

	let device = keys.CARRIOTS_DEVICEKEY;
	let apikey = keys.CARRIOTS_APIKEY;

	let options = {
		host: "api.carriots.com",
		path: "/streams",
		method: "GET",
		headers: {
			"User-Agent": "NodeJS-carriots.com-Client",
			"Content-Type": "application/vnd.carriots.api.v2+json;q=7",
			"Accept": "application/vnd.carriots.api.v2+json;q=7",
			"Carriots.apikey": apikey
		}
	};

	setInterval(function () {
		let callback = function (response) {
			let str = '';
			response.on('data', function (chunk) {
				str += chunk;
				mainCallback(chunk);
			});

			response.on('end', function () {
				console.log(str);
			});
		};

		let req = https.request(options, callback);
		req.on("error", function (e) {
			console.log("problem with request: " + e.message);
		});
		req.end();
	}, 10000);
};
