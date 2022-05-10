How to Flash
1. open NodeMCU-PyFlasher-with-ResetLocale.exe
2. in NodeMCU Firmware section choose the target.bin file in this folder
3. select Baud rate at "115200", Flash mode at "DIO", erase flash at "no"
4. connect your NodeMCU to computer, then select your NodeMCU serial port
5. Flash NodeMCU and wait until it finished

How to setup
1. Once the NodeMCU boot into ESP-Link firmware it will act as access point, find the access point named ESP-(last 4 character of your MAC address) and conect
2. Open the ESP-Link default web server at 192.168.4.1
3. Go to WiFi Station Configuration and Switch to STA+AP mode
4. Connect to your WiFi network and wait until getting an IP address
5. I prefer to use static IP instead DHCP for easier connection
6. Reconnect to your Wifi network and go to IP address of your ESP-link and it will show you the web server
7. Go to Microcontroller Console, make sure the fmt on 8N1 and select the baud rate that match your arduino and firmata baud rate
