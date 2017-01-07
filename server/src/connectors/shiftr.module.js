/**
 * Created by gwennael.buchet on 01/01/17.
 */
"use strict";

let keys = require("./secretKeys.js");
let mqtt = require('mqtt');

exports.init = function () {
	let shiftrClient = mqtt.connect(
		'mqtt://' + keys.SHIFTR_DEVICE_LOGIN + ':' + keys.SHIFTR_DEVICE_PWD + '@broker.shiftr.io', {
			clientId: 'Web Server'
		}
	);

	shiftrClient.on('connect', function () {
		console.log('shiftrClient has connected!');

		shiftrClient.subscribe(keys.SHIFTR_NAMESPACE);

		/*setInterval(function () {
			shiftrClient.publish(keys.SHIFTR_NAMESPACE, 'world');
		}, 1000);*/
	});

	shiftrClient.on('message', function (topic, message) {
		console.log('new message:', topic, message.toString());
	});
};
