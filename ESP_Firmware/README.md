Wiring
===
The Arduino and ESP8266 will communicate through serial, the wiring between ESP8266 and Arduino should be like this:
1. 3.3V ESP to 3.3V Arduino  or 5V ESP to 5V Arduino (depend on ESP module type)
2. GND  ESP to GND  Arduino
3. Tx   ESP to Rx   Arduino
4. Rx   ESP to Tx   Arduino
---

How to Flash
===
Via Arduino IDE (work for both ESP8266 and ESP32)
---
1. Choose Arduino sketch that suits your devices
2. open the .ino file
3. make sure you have ESP32 or ESP8266 board manager installed, check this if not installed for [ESP8266](<https://arduino-esp8266.readthedocs.io/en/latest/installing.html>) or [ESP32](<https://www.hackster.io/abdularbi17/how-to-install-esp32-board-in-arduino-ide-1cd571>)
4. setup ssid and password of your network in //wifi config section
5. in //ethernet setup section, configure your ip address setup to fit your network configuration to make ESP has static IP and set it as your TCP server adddress
6. in //rs-server config section, configure your tcp server port
7. in // rs port config section, configure your serial connection
---

Via NodeMCU-PyFlasher(only for esp8266 using ESP-Link firmware)
---
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
