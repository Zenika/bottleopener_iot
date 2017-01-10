#define AWS_IOT_MQTT_HOST "" 
// your endpoint
#define AWS_IOT_MQTT_PORT 8883
// your port (default is 8883)
#define AWS_IOT_CLIENT_ID ""
// your client ID
#define AWS_IOT_MY_THING_NAME ""
// your thing name
#define AWS_IOT_ROOT_CA_FILENAME ""
// your root-CA filename
#define AWS_IOT_CERTIFICATE_FILENAME ""
// your certificate filename
#define AWS_IOT_PRIVATE_KEY_FILENAME ""
// your private key filename
//===============================================================
#define AWS_IOT_PATH_PREFIX "/root/AWS-IoT-Python-Runtime/certs/" //usually this path is used
#define AWS_IOT_ROOT_CA_PATH AWS_IOT_PATH_PREFIX AWS_IOT_ROOT_CA_FILENAME
#define AWS_IOT_CERTIFICATE_PATH AWS_IOT_PATH_PREFIX AWS_IOT_CERTIFICATE_FILENAME
#define AWS_IOT_PRIVATE_KEY_PATH AWS_IOT_PATH_PREFIX AWS_IOT_PRIVATE_KEY_FILENAME
