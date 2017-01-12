"use strict";

let https = require('https');


let keys = require("./secretKeys.js");

exports.init = function (mainCallback) {

	let options = {
		host: "api.carriots.com",
		path: "/streams",
		method: "GET",
		headers: {
			"Accept": "application/json",
			"Accept-Encoding": "gzip, deflate, sdch, br",
			"Accept-Language": "fr-FR,fr;q=0.8,en-US;q=0.6,en;q=0.4",
			"carriots.apiKey": keys.CARRIOTS_APIKEY,
			"Connection": "keep-alive",
			"Content-Type": "application/json",
			"Host": "api.carriots.com"
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
	}, 5000);
};
