/**
 * Created by gwennael.buchet on 07/01/17.
 */

	// Install thingspeak client or include in your package.json
	// npm install thingspeakclient


let keys = require("./secretKeys.js");
let ThingSpeakClient = require('thingspeakclient');

exports.init = function () {
	let tsClient = new ThingSpeakClient();
	let _last_entryID = -1;

	tsClient.attachChannel(keys.THINGSPEAK_CHANNEL_NUMBER,
	                       {
		                       readKey: keys.THINGSPEAK_READ_API_KEY
	                       },
	                       function (err, resp) {
		                       if (!err) {
			                       console.log('Connected to Thingspeak.');
		                       }
		                       else {
			                       console.log('Thingspeak connection error. response was: ' + err);
		                       }
	                       });

	/**
	 * Because Thingspeak uses HTTP (not Websocket, neither MQTT) we have to manually refresh the data
	 */
	setInterval(function () {
		tsClient.getLastEntryInChannelFeed(keys.THINGSPEAK_CHANNEL_NUMBER, function (err, resp) {
			if (!err) {
				if (resp.entry_id != _last_entryID) {
					_last_entryID = resp.entry_id;
					console.log(resp);
				}
			}
			else {
				console.log('Thingspeak reception error. response was: ' + err);
			}
		});
	}, 5000);
};
