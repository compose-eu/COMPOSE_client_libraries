COMPOSE Arduino Example
================

This sketch uses the COMPOSE sketch for storing data into a SO that has a similar structure to the following:

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

The sketch is for the Arduino Yun, but can be easily adopted for working with an Ethernet or a WiFi shield.

Keep in mind, you need to always name the connection client object as 'client' (e.g., EthernectClient client;)
