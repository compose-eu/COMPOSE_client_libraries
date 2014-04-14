//This example is for the Arduino Yun
//You can easily adopt it for WiFi Shield, etc.
#include <SPI.h>
#include <Ethernet.h>
#include <YunClient.h>

//Make sure you name your connection object as client (EthernetClient client;, WiFiClient client;, etc.)
YunClient client;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  Bridge.begin();
  digitalWrite(11, LOW);
 
  //Set the Authorisation key from COMPOSE:
  setAuthkey("YOUR_KEY_GOES_HERE");
  
  //as an example, read an analog pin input:
  String value = String(analogRead(A0));

  //Given that you have created a SO with streams and channels, use these functions to populate the channel with data:
  setChannelData("temperature", value);
  setChannelData("user", "arduino");
  setChannelData("location", "universe");
 
  //Store the data into the SO, defining the stream name and the Service Object ID:
  submitSO("ArduinoSensor", "1395851631319a3fe402338134ca498cfef5d00fd8ace");
 

}

void loop() {
  // put your main code here, to run repeatedly:

}
