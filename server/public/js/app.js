'use strict';

/*-----------------
 Components
 -----------------*/

let drinkeritem = Vue.component(
	'drinker-item',
	{
		template: "<div class='panel panel-default'> \
		                <div class='panel-heading'> \
		                     <h1 class='cover-heading'>{{drinker.name | uppercase }}'s quantity. </h1> \
						</div> \
						<div class='panel-body'> \
							{{drinker.quantity}} \
							<!--ul class='item-list'> \
							<li v-for='platform in platforms'> \
								{{platform.name}} : {{platform.quantity}} \
							</li> \
							</ul--> \
						</div> \
						</div>",

		props: ['drinker'],

		methods: {
			gravatarURL: function (email) {
				return "https://www.gravatar.com/avatar/" + CryptoJS.MD5(email);
			}
		}
	}
);

let drinkerItem = Vue.component(
	'drinker-item2',
	{
		template: "#drinker-item2",

		props: ['drinker'],

		methods: {
			gravatarURL: function (email) {
				return "https://www.gravatar.com/avatar/" + CryptoJS.MD5(email);
			}
		}
	}
);

/*-----------------
 Filters
 -----------------*/

Vue.filter('uppercase', function (value) {
	return value.toUpperCase();
});

/*-----------------
 APP
 -----------------*/
new Vue({

	// We want to target the div with an id of 'drinkersList'
	el: '#drinkersList',

	data: {
		ws: null, // Our websocket
		drinkers: [
			{
				"name": "Gwen",
				"quantity": 0,
				"email": "gwennael.buchet@gmail.com",
				"platforms": []
			},
			{
				"name": "Adrien",
				"quantity": 0,
				"email": "legrand.ax@gmail.com",
				"platforms": []
			}
		]
	},

	created: function () {
		let self = this;
		this.ws = new WebSocket("ws://" + window.location.hostname + ":8081");

		this.ws.onopen = function (event) {
			console.log("Websocket connection opened.");
		};
		this.ws.onmessage = function (event) {
			let msg = JSON.parse(event.data);
			self.addQuantityToDrinker(msg);
		};
		this.ws.onerror = function (event) {
			console.log("Websocket connection error : " + event);
		};
	},

	methods: {
		addQuantityToDrinker: function (message) {

			let drinker = this._getDrinkerByName(message.name);
			drinker.quantity = message.quantity;
			drinker.platforms = message.platforms;
			//this._setPlatformQuantityByDrinkerAndName(message.name, message.platform, message.quantity);
		},

		/*_setPlatformQuantityByDrinkerAndName: function (drinker, platformName, quantity) {
			let platform = null;
			for (platform of drinker.platforms) {
				if (platformName === platform.name) {
					platform.quantity = quantity;
				}
			}

			//no platform ? create a new one
			let newPlatform = {"name": name, "quantity": quantity};
			drinker.platforms.push(newPlatform);

			return newPlatform;
		},*/

		/**
		 * Try to find the drinker with that name in the database (here : the list) or create a new one.
		 * @param drinkerName
		 * @returns {*}
		 * @private
		 */
		_getDrinkerByName: function (drinkerName) {
			let drinker = null;
			for (drinker of this.drinkers) {
				if (drinkerName === drinker.name) {
					return drinker;
				}
			}

			//no drinker found? create a new one
			let newDrinker = {"name": drinkerName, "quantity": 0};
			this.drinkers.push(newDrinker);

			return newDrinker;
		}
	},

	computed: {}
});
