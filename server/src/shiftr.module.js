/**
 * Created by gwennael.buchet on 01/01/17.
 */

var keys = require("secretKeys.js");
var mqtt = require('mqtt');

var client = mqtt.connect('mqtt://' + SHIFTR_DEVICE_LOGIN + ':' + SHIFTR_DEVICE_PWD + '@broker.shiftr.io', {
	clientId: 'WebServer' //javascript
});

client.on('connect', function () {
	console.log('Shiftr.io client has connected!');

	client.subscribe(SHIFTR_NAMESPACE);
});

client.on('message', function (topic, message) {
	console.log('  * New message from Shiftr.io :', topic, message.toString());
});
