# NautiControl ST Tester
Tester for Sea Talk devices and instruments . This is an alternative firmware to the main ST Wireless V1 Firmware . This is used to test and simulate seatalk data using the existing ST Wireless V1 board design details of building / buying can be found over on the main repo https://github.com/nauti-control/STWirelessRemote . You can purchase a premade box in our shop https://nauti-control.com/product/st-wireless-controller-fully-built-with-4-button-remote/ .

I use this for testing functionality within the ST 

# Functions

Currently the tester can simulate a number of Seatalk data points and allows input over a web interface to enter simulated values. 

Depth - Tested with ST 60 depth and Tri -Data
Speed over ground - Tested with ST60 speed instrument
Speed through water - Tested with ST60 speed instrument
Apparent Wind Speed and Wind Angle - Tested with ST60 Wind Instrument 

# Software
The code is written in C++ using platform IO . I use Visual Code as my editor . The firmware uses soft serial with the parity bit acting at the 9th bit that seatalk protocol uses. The seatalk datagrams I have been using an excellent technical guide by Thomas Knauf http://thomasknauf.de/rap/seatalk2.htm . There is two parts to the code 1. The main firmware 2. A mini web application for settings the button mapping settings as well as allowing the device to be controlled from a mobile device . This is written to the esp32 spiffs. These get built and uploaded to the ESP32 seperately from with the platform IO extension in Visual Code.

# Hardware 
Just re-using my existing pcb design as it had all the seatalk interface stuff and the ESP32 for web hosting ready to go!

# Compatibility

So far i've tested with 
ST60 Depth Instrument
ST60 Speed Insturment
ST60 Tri-Data Insturment
ST60 Wind Insturment

