

## Introduction
[The Works Museum](https://theworks.org/about-us/) is a children's museum in Bloomington, Minnesota, that teaches engineering skills to children through a variety of interactive and non-interactive exhibits. 
Among theses exhibits is a K'nex ball machine, which sends balls down a variety of winding paths to a ball lift, which returns the balls to the top to continue their journey.

The ball machine utilizes an Arduino and a variety of sensors to provide remote, browser-based, real-time monitoring of the status of the machine.

This code consists of two parts:
- KnexTelemetryClient: A client app to consume KnexTelemetryApi. Encapsulates wifi and http connectivity. Written in C++ and built for an Arduino Nano RP2040 Connect.
- KnexTelemetryWeb: Contains both a RESTful API for receiving data and a UI app to display it. Written in Node.js.



## KnexTelemetryClient

### Dependencies

Install the following libraries:
- WiFiNINA
- ArduinoJson

### Config

Create a `KnexTelemetryClient_config.h` file and place it in your project folder. This file will define wifi and application credentials. `DOMAIN` and `ACCESS_TOKEN` must match the domain and access_token configured with KnexTelemetryApi. 

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

### Instantiation

Create a `KnexTelemetryClient` object. Call KnexTelemetryClient::Init() before use 

	KnexTelemetryClient client;
	
	void  setup()  {
		Serial.begin(9600);
		client.Init();
	}

### Sending data to KnexTelemetryWeb
Given the light weight nature of the API, only one method is needed to send data. 

	string KnexTelemetryClient::SendData(string dataKey, string dataValue)
	
Parameters
- dataKey : The name of the sensor or calculated variable to update
- dataValue : The new value

Returns
- The new dataValue accepted and stored by the server

Example

	string newBallsInLastHour = client.SendData("balls-in-last-hour","240");
	string newTotalBalls = client.SendData("total-balls", "12345");

The `KnexTelemetryClient.ino` file also contains example code


## KnexTelemetryWeb
Not done yet
