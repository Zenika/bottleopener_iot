#ifndef SENDCARRIOTSYUN_H_
#define SENDCARRIOTSYUN_H_

#include <Arduino.h>

class SendCarriotsYun{
	public:
		//define the public method to send a JSON to Carriots from the array passed to the method
		String send(String array[][2], int elements, String apikey, String device);
};

#endif
