QFirmata Over WiFi
===
Description
---
This is a modified QFirmata for connecting [wall follower robot](<https://github.com/rusmanr/QFirmataWallFollower>) to computer via WiFi.
To communicate via Wifi you can use ESP8266 module as TCP server to bridge communication from serial to TCP, you need an ESP8266 module that flashed with serial-to-wifi-bridge firmwares, like [ESP-link](<https://github.com/jeelabs/esp-link>) firmware. If you're using NodeMCU you can use the file on ESP-firmware folder. 





Wiring
---
The Arduino and ESP8266 will communicate through serial, the wiring between ESP8266 and Arduino should be like this:
1. 3.3V ESP8266 to 3.3V Arduino
2. GND  ESP8266 to GND  Arduino
3. Tx   ESP8266 to Rx   Arduino
4. Rx   ESP8266 to Tx   Arduino

Usage
---
There is two methedes for the robot communicate with the PC:
1. Using [virtual serial port](<https://www.hw-group.com/software/hw-vsp3-virtual-serial-port>), This methode will work flawlessly with normal code that communicate through cable. Just input your ESP8266 IP address to the app and select the serial port number (COMxx).
    
2. Direct connection using TCP, This methode require modified QFirmata by using QFirmataTCP and modify your mainWindow UI connect methodes.
You have to add and modify this files:

a. Add QFirmataTCP.pri to your folder and modify the following line on your .pro file
```
QT       += core gui network
```

and

```
include(/path/to/your/libs/QFirmata/QFirmataTCP.pri)
```
b. Add qfirmataTCP.cpp and qfirmataTCP.h to your src folder and don't forget to modify the QFirmataTCP.pri path and all #include line on your header code to thr TCP version.

c. modify your mainWindow files to create UI for TCP connection.

---
License
---
GPLv3
