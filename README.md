# bottleopener_iot
Small application to test some IoT platforms with an Arduino Yùn based bottle opener.

----------

# Folders
#### :open_file_folder: /bottleopener 
Arduino Yùn code with a simple button. When the button is pressed, the total counter for his device is then send to several IoT platforms.
#### :open_file_folder: /bottleopener_aws 
Arduino Yùn code dedicated to AWS IoT platform.
#### :open_file_folder: /counter 
Arduino Yùn code to display total quantity from all IoT platforms to a 7 segments LED matrix
#### :open_file_folder: /Server 
simple NodeJS server + webpage to display total quantity
