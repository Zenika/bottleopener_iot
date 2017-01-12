/**
 * Created by gwennael.buchet on 01/01/17.
 */
"use strict";

/**
 * HOW-TO :
 * - rename this file into "secretKeys.js"
 * - replace values with your own
 */

module.exports = Object.freeze(
	{
		//ThingSpeak API keys
		THINGSPEAK_CHANNEL_NUMBER: 0,
		THINGSPEAK_WRITE_API_KEY: "",
		THINGSPEAK_READ_API_KEY: "",

		//Shiftr.io tokens
		SHIFTR_NAMESPACE: "/xxxx",
		SHIFTR_DEVICE_LOGIN: "",
		SHIFTR_DEVICE_PWD: "",

		//Carriots
		CARRIOTS_APIKEY: "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
		CARRIOTS_DEVICEKEY: "xxx@yyy",

		//AWS IoT Cas & config
		AWS_IOT_MQTT_HOST: "XXXXXXXXXXXXXXXXx.amazonaws.com",
		AWS_IOT_MQTT_PORT: 8883,
		// your port (default is 8883)
		AWS_IOT_CLIENT_ID: "",
		AWS_IOT_MY_THING_NAME: "",
		AWS_IOT_ROOT_CA_FILENAME: "/root/cert/path",
		AWS_IOT_CERTIFICATE_FILENAME: "/cert.pem/path",
		AWS_IOT_PRIVATE_KEY_FILENAME: "/private.key/path"
	}
);
