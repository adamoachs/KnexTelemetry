

## Introduction
[The Works Museum](https://theworks.org/about-us/) is a children's museum in Bloomington, Minnesota, that teaches engineering skills to children through a variety of interactive and non-interactive exhibits. 
Among theses exhibits is a K'nex ball machine, which sends balls down a variety of winding paths to a ball lift, which returns the balls to the top to continue their journey.

The ball machine utilizes an Arduino and a variety of sensors to provide remote, browser-based, real-time monitoring of the status of the machine.

This code consists of two parts:
- KnexTelemetryClient: A library to send data to KnexTelemetryWeb. Encapsulates wifi and http connectivity. Written in C++ and built for an Arduino Nano RP2040 Connect. This library is intended for use in a larger Arduino project. It only facilitates sending of data, not collection of data from sensors
- KnexTelemetryWeb: Contains both a RESTful API for receiving data and a UI app to display it. Build with Node.js.



## KnexTelemetryClient

### Dependencies

In the Arduino IDE Library Manager, install the following libraries:
- WiFiNINA
- ArduinoJson

### Config

Create a `KnexTelemetryClient_config.h` file and place it in your project folder. This file will define wifi and application credentials. `DOMAIN` and `ACCESS_TOKEN` must match the domain and access_token configured with KnexTelemetryWeb. 

    #ifndef KnexTelemetryClient_config_h
    #define KnexTelemetryClient_config_h
    
	//mandatory
    #define DOMAIN  "www.example.com"
    #define ACCESS_TOKEN  "authtoken"
    #define WIFI_SSID  "Wifi Name"
    #define WIFI_PASSWORD  "Wifi Password"
	
	//optional
	#define PORT 3000 //will use 443 if undefined
	#define VERBOSE //enable verbose Serial monitor logging
    
    #endif //KnexTelemetryClient_config_h
	
### Include

Include the `KnexTelemetryClient.h` file in your .ino file

	#include "KnexTelemetryClient.h"

### Instantiation

Create a `KnexTelemetryClient` object. In the project `setup` method, call KnexTelemetryClient::Init() before use 

	KnexTelemetryClient client;
	
	void  setup()  {
		Serial.begin(9600);
		client.Init();
	}

### Sending data to KnexTelemetryWeb

The client supports two methods to send data
- `SendData` is for metrics to may want to be tracked over time to monitor trends. Data is timestamped and kept for a configurable length of time.
- `SendStatus` is for current status only. Data is timestamped to track it's last update, but only the most recent update is stored.

	string KnexTelemetryClient::SendData(string dataKey, string dataValue)
	
Parameters
- dataKey: The name of the sensor or calculated variable to update
- dataValue: The new value

Example
	client.SendData("balls-in-last-hour","240");
	client.SendData("total-balls", "12345");
	
	string KnexTelemetryClient::SendStatus(string statusName, string statusValue)
	
Parameters
- statusName: The name of the status to update
- statusValue: The new value

Example
	client.SendStatus("lift-1", "online");
	client.SendStatus("lift-2", "online");
	client.SendStatus("lift-3", "offline");

The `KnexTelemetryClient.ino` file also contains example code


## KnexTelemetryWeb

(This section still in progress)

### Dependencies

Run `npm install` to download dependencies

	npm install
	
### Config

Create a `app.env` file and place it in your project folder. This file will define application credentials. `DOMAIN` and `ACCESS_TOKEN` must match the domain and access_token configured with KnexTelemetryClient. 

	#mandatory
	ACCESS_TOKEN=authtoken

	#optional
	PORT=3000 #defaults to 443 if unspecified
	ENV=dev #set to dev for full error messages

