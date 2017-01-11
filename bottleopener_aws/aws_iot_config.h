#define AWS_IOT_MQTT_HOST "a13byqleafkxa1.iot.us-west-2.amazonaws.com" 
// your endpoint
#define AWS_IOT_MQTT_PORT 8883
// your port (default is 8883)
#define AWS_IOT_CLIENT_ID "decap"
// your client ID
#define AWS_IOT_MY_THING_NAME "decap"
// your thing name
#define AWS_IOT_ROOT_CA_FILENAME "root-ca.pem.crt"
// your root-CA filename
#define AWS_IOT_CERTIFICATE_FILENAME "d1d0dc3351-certificate.pem.crt"
// your certificate filename
#define AWS_IOT_PRIVATE_KEY_FILENAME "d1d0dc3351-private.pem.key"
// your private key filename
//===============================================================
#define AWS_IOT_PATH_PREFIX "/root/AWS-IoT-Python-Runtime/certs/"
#define AWS_IOT_ROOT_CA_PATH AWS_IOT_PATH_PREFIX AWS_IOT_ROOT_CA_FILENAME
#define AWS_IOT_CERTIFICATE_PATH AWS_IOT_PATH_PREFIX AWS_IOT_CERTIFICATE_FILENAME
#define AWS_IOT_PRIVATE_KEY_PATH AWS_IOT_PATH_PREFIX AWS_IOT_PRIVATE_KEY_FILENAME
