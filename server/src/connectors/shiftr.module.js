/**
 * Created by gwennael.buchet on 01/01/17.
 */
"use strict";

require("./secretKeys.js");
let mqtt = require('mqtt');

let shiftrClient;

shiftrClient.on('connect', function () {
	console.log('Shiftr.io client has connected!');

	shiftrClient.subscribe(SHIFTR_NAMESPACE);
});

shiftrClient.on('message', function (topic, message) {
	console.log('  * New message from Shiftr.io :', topic, message.toString());
});


exports.init = function () {
	shiftrClient = mqtt.connect('mqtt://' + SHIFTR_DEVICE_LOGIN + ':' + SHIFTR_DEVICE_PWD + '@broker.shiftr.io', {
		clientId: 'WebServer' //javascript
	});
};