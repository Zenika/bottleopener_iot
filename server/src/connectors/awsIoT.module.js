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

	device.subscribe('beer_sub');

	device
	   .on('connect', function() {
		  console.log('Connected to AWS IoT.');
	   });
	device
	   .on('close', function() {
		  console.log('Connexion to AWS IoT closed');
	   });
	device
	   .on('reconnect', function() {
		  console.log('Reconnecting to AWS IoT ...');
	   });
	device
	   .on('offline', function() {
		  console.log('Application\'s offline');
	   });
	device
	   .on('error', function(error) {
		  console.log('Error with AWS IoT connexion', error);
	   });
	device
	   .on('message', function (topic, message) {
			console.log('New message from AWS IoT :', topic, message.toString());
			let json = JSON.parse(message);

			mainCallback(json.sender, json.quantity, "AWS IoT");
		});
};
