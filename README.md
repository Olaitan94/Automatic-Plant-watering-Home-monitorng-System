# Smart Home monitoring & Gardening System
Automatic Plant watering &amp; Home monitorng System using C++, html, Arduino etc
A web user interface was created for remote control of the system using html
System was connected to wifi to send data through thingspeaks and receive commands through pubnub
Hardware BOARDS USED: ESP32 & Arduino Uno

This project involves the design and development of an automatic indoor plant watering and monitoring system. The system is equipped with sensors, which measure the soil moisture, temperature and relative humidity, and a water pump which supplies water to the plant. 

The system can be operated in two different modes and the choice of mode can be selected by the user on the Web interface. The ESP 32 is connected to Wi-Fi and a cloud-based interface which enables it to receive control commands from the user interface and also send out sensor data to the monitoring dashboard. 
The operation of the pump is controlled by the ESP32 and Arduino Uno boards based on the mode selected by user.

The two modes are briefly explained below:
•	Sensor Based Mode: A soil moisture threshold value of 50% has been set as the ideal condition of the plant. Values below this threshold will trigger the activation of the pump while values above the threshold will trigger the deactivation of the pump.

•	Instant Watering Mode: The user can select this mode to activate the pump and water the plant irrespective of the soil moisture value.

