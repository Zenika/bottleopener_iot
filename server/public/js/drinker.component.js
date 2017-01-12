/**
 * Created by gwennael.buchet on 09/01/17.
 */

let drinkeritem = Vue.component(
	'drinker-item',
	{
		template: '\
		<div class="container"> \
			<div class="row text-center"> \
				<div class="col-md-12" style="margin-top: 20px;"> \
					<div class="pricing-table"> \
						<div class="panel panel-primary" style="border: none;"> \
							<div class="controle-header panel-heading panel-heading-landing"> \
								<h1 class="panel-title panel-title-landing" > \
									{{drinker.name}} \
								</h1> \
							</div> \
							<div class="controle-panel-heading panel-heading panel-heading-landing-box"> \
								{{drinker.quantity}} opened bottles \
							</div> \
							<div class="panel-body panel-body-landing"> \
								<table class="table"> \
									<tr v-for="(platform, index) in drinker.platforms"> \
										<td width="50px"><i class="fa fa-check"></i></td> \
										<td>{{platform.name}}</td> \
										<td>{{platform.quantity}}</td> \
									</tr> \
								</table> \
							</div> \
							<div class="panel-footer panel-footer-landing"> \
								<img :src="gravatarURL(drinker.email)" class="gravatar"> \
							</div> \
						</div> \
					</div> \
				</div> \
			</div> \
		</div>',

		props: ['drinker'],

		methods: {
			gravatarURL: function (email) {
				console.log(email);
				return "https://www.gravatar.com/avatar/" + CryptoJS.MD5(email);
			}
		}
	}
);