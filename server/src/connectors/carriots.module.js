"use strict";

let https = require('https');


let keys = require("./secretKeys.js");

exports.init = function (mainCallback) {

	let options = {
		host: "api.carriots.com",
		path: "/streams/?max=1&order=-1",
		port: 443,
		method: "GET",
		headers: {
			"Accept": "application/json",
			"carriots.apiKey": keys.CARRIOTS_APIKEY,
			"Connection": "keep-alive",
			"Content-Type": "application/json",
			"Host": "api.carriots.com"
		}
	};

	setInterval(function () {
		let req = https.request(options, (res) => {
			res.on('data', (chunk) => {
				let body = [];
				body.push(chunk);
				let msg = JSON.parse(body.toString());
				let data = msg.result[0].data;

				mainCallback(data.sender, data.quantity, "Carriots");
			});
		});

		req.on('error', (e) => {
			console.error(e);
		});
		req.end();

	}, 5000);

};
