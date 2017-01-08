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

		created: function () {
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
			},
			{
				"name": "Adrien",
				"quantity": 0
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
			self.addQuantityToDrinker(msg.name, msg.quantity);
		};
		this.ws.onerror = function (event) {
			console.log("Websocket connection error : " + event);
		};
	},

	methods: {
		addQuantityToDrinker: function (drinkerName, quantity) {

			let drinker = this._getDrinkerByName(drinkerName);
			drinker.quantity = quantity;
		},

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
		},

		gravatarURL: function (email) {
			return "https://www.gravatar.com/avatar/" + CryptoJS.MD5(email);
		}
	},

	computed: {}
});
