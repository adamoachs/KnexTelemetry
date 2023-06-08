
## Introduction
[The Works Museum](https://theworks.org/about-us/) is a children's museum in Bloomington, Minnesota, that teaches engineering skills to children through a variety of fun exhibits. Among this exhibits is a K'nex ball machine, which sends balls down a variety of winding paths to a ball lift, which returns the balls to the top to continue their journey.

The ball machine utilizes an Arduino and a variety of sensors to provide remote, browser-based monitoring of the status of the machine.

This code consists of three parts:
- KnexTelemetryApi: A RESTful web API service to receive status updates. Written in (not yet written) and runs on (don't know yet)
- KnexTelemetryClient: A client app to consume KnexTelemetryApi. Written in C++ and built for an Arduino Nano RP2040 Connect.
- KnexTelemetryWeb: A web app to display status. Written in (not yet written) and runs on (don't know yet)



## KnexTelemetryClient

### Config

Create a `KnexTelemetryClient_config.h` file and place it in your project folder. This file will define wifi and application credentials. `DOMAIN` and `ACCESS_TOKEN` must match the domain and access_token configured with KnexTelemetryApi. 

    #ifndef  KnexTelemetryClient_config_h
    #define  KnexTelemetryClient_config_h
    
    #define  DOMAIN  "www.example.com"
    #define  ACCESS_TOKEN  "authtoken"
    #define  WIFI_SSID  "Wifi Name"
    #define  WIFI_PASSWORD  "Wifi Password"
    
    #endif //KnexTelemetryClient_config_h

### Instantiation

Create a `KnexTelemetryClient` object. Call KnexTelemetryClient::Init() before use 

	KnexTelemetryClient client;
	
	void  setup()  {
		Serial.begin(9600);
		client.Init();
	}

### Sending data to KnexTelemetryApi
The KnexTelemetryClient library includes a number of premade methods to send data to KnexTelemetryApi.
More methods to come

	void KnexTelemetryClient::SendVar(string varName, string varValue)
	
	client.SendVar("balls-in-last-hour","240");
	client.SendVar("total-balls", "12345");




## KnexTelemetryApi
Not done yet



## KnexTelemetryWeb
Not done yet
