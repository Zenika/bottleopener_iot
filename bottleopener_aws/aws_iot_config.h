#define AWS_IOT_MQTT_HOST "xxxxxxxxxxxxxx.amazonaws.com" 
// your endpoint
#define AWS_IOT_MQTT_PORT 8883
// your port (default is 8883)
#define AWS_IOT_CLIENT_ID ""
// your client ID
#define AWS_IOT_MY_THING_NAME ""
// your thing name
#define AWS_IOT_ROOT_CA_FILENAME "xxxxxxxxxxxx.pem.crt"
// your root-CA filename
#define AWS_IOT_CERTIFICATE_FILENAME "xxxxxxxxxxx.pem.crt"
// your certificate filename
#define AWS_IOT_PRIVATE_KEY_FILENAME "xxxxxxxxxxx.pem.key"
// your private key filename
//===============================================================
#define AWS_IOT_PATH_PREFIX "/path/to/your/certs/"
#define AWS_IOT_ROOT_CA_PATH AWS_IOT_PATH_PREFIX AWS_IOT_ROOT_CA_FILENAME
#define AWS_IOT_CERTIFICATE_PATH AWS_IOT_PATH_PREFIX AWS_IOT_CERTIFICATE_FILENAME
#define AWS_IOT_PRIVATE_KEY_PATH AWS_IOT_PATH_PREFIX AWS_IOT_PRIVATE_KEY_FILENAME
