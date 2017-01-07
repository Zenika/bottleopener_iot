/**
 * Created by gwennael.buchet on 07/01/17.
 */

	// Install thingspeak client or include in your package.json
	// npm install thingspeakclient


let keys = require("./secretKeys.js");
let ThingSpeakClient = require('thingspeakclient');

exports.init = function () {
	let tsClient = new ThingSpeakClient();

	tsClient.attachChannel(keys.THINGSPEAK_CHANNEL_NUMBER,
	                       {
		                       readKey: keys.THINGSPEAK_READ_API_KEY
	                       },
	                       function (err, resp) {
		                       if (!err) {
			                       console.log('Connected to Thingspeak. response was: ' + resp);
		                       }
		                       else {
			                       console.log('Thingspeak connection error. response was: ' + err);
		                       }
	                       });


	setInterval(function () {
		tsClient.getLastEntryInChannelFeed(keys.THINGSPEAK_CHANNEL_NUMBER, function (err, resp) {
			if (!err) {
				console.log(resp);
			}
			else {
				console.log('Thingspeak reception error. response was: ' + err);
			}
		});
	}, 5000);
};
