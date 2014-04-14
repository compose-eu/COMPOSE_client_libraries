COMPOSE Client Library for the Arduino
================

The COMPOSE Client Library for the Arduino is a sketch that can be imported into any project and provides functionality for:

- Easily storing sesnor data on a Service Object (SO) created through [Servioticy]


Installation
----

Simply import the Compose.ino sketch inside your current sketch (Sketch->Add file->Compose.ino)


Usage
----

You need to be a [user] of Serviocity with a valid API token (Authorisation key)
You need to have created a SO on Servioticy (more info [here]) and know the SO ID.

Suppose that your SO has the following structure:

```sh
{
    "name": "Arduino",
    "description": "My Arduino Analog Sensor",
    "streams": {
        "ArduinoSensor": {
            "channels": {
                "temperature": {
                    "type": "float",
                    "unit": "celcius"
                },
                "user": {
                    "type": "string",
                    "unit": ""
                },
                "location": {
                    "type": "string",
                    "unit": ""
                }
            },
            "type": "sensor"
        }
    },
    "customFields": {},
    "actions": [],
    "properties": []
}
```

To store data you need to do something like:
```sh
//Initialise the client object for connectivity:
EthernetClient client;
...
void setup() {
	
	.....
	//Set the Authorisation key from COMPOSE:
  	setAuthkey("YOUR_KEY_GOES_HERE");
  
  	//as an example, read an analog pin input:
  	String value = String(analogRead(A0));

  	//Populate the channels with data
  	setChannelData("temperature", value);
  	setChannelData("user", "arduino");
  	setChannelData("location", "universe");
 
  	//Store the data into the SO, defining the stream name and the Service Object ID:
  	submitSO("ArduinoSensor", "1395851631319a3fe402338134ca498cfef5d00fd8ace");
}

```
Keep in mind, you need to always name the connection client object as 'client' (e.g., EthernectClient client;)

Check also the example folder for a sample sketch that stores analog sensor data into a SO.






[Servioticy]:http://www.servioticy.com/
[here]:http://www.servioticy.com/?page_id=106
[user]:http://www.servioticy.com/?page_id=73
