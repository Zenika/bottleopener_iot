"use strict";

let https = require('https');
let deviceModule = require('aws-iot-device-sdk').device;

let keys = require("./secretKeys.js");
let mqtt = require('mqtt');

exports.init = function (mainCallback) {
	console.log(keys.AWS_IOT_PRIVATE_KEY_FILENAME);
	let device = deviceModule({
	   keyPath: keys.AWS_IOT_PRIVATE_KEY_FILENAME,
	   certPath: keys.AWS_IOT_CERTIFICATE_FILENAME,
	   caPath: keys.AWS_IOT_ROOT_CA_FILENAME,
	   clientId: keys.AWS_IOT_CLIENT_ID,
	   region: 'us-east-1',
	   baseReconnectTimeMs: 4000,
	   keepalive: 30,
	   protocol: 'mqtts',
	   port: keys.AWS_IOT_MQTT_PORT,
	   host: keys.AWS_IOT_MQTT_HOST,
	   debug: true
	});

	var timeout;
	var count = 0;
	const minimumDelay = 250;

	device.subscribe('beer_sub');

	device
	   .on('connect', function() {
		  console.log('connect');
	   });
	device
	   .on('close', function() {
		  console.log('close');
	   });
	device
	   .on('reconnect', function() {
		  console.log('reconnect');
	   });
	device
	   .on('offline', function() {
		  console.log('offline');
	   });
	device
	   .on('error', function(error) {
		  console.log('error', error);
	   });
	device
	   .on('message', function (topic, message) {
			console.log('new message:', topic, message.toString());
			let json = JSON.parse(message);

			mainCallback(json.sender, json.quantity, "AWS IoT");
		});
};
