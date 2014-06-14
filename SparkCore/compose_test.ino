// This #include statement was automatically added by the Spark IDE.
#include "HttpClient.h"
#include "PubSubClient.h"

#define auth_token  "OWIzZjk4MmUtMjNlOC00ZTZkLWI3YjItY2JkMGEwYzNiMzJmYzI4Y2RlNTMtNzFmYy00MzY5LWE5M2YtZmUyYzUzOTVkYTFj"
#define SO_ID "139973385949113af8188748f43a0b9a59d9d7dd4c06a"

byte broker_ip[] = {  147, 83, 30, 150 };
long temp_time = 0;

void callback(char* topic, byte* payload, unsigned int length) {
    int i=0;
    char buff[length+1];
    
    for(i=0; i<length; i++) {
        buff[i] = payload[i];
    }
    buff[i] = '\0';
    
    String message(buff);
    
    Serial.println(message);
}

TCPClient tcpClient;
PubSubClient client(broker_ip, 1883, callback, tcpClient);


//Setup
void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println("Starting...");
    delay(1000);
    

    Serial.println(Time.now());
    delay(2000);
    
    
    Serial.println("connecting to broker and subscribing...");
    if (client.connect("spark", "compose", "shines")) { // uid:pwd based authentication
        client.subscribe("1398680352030c33b8197ce354479adf39a3931a19a7f/actions");
        
        Serial.println("Connected and subscribed..");
  }
  
  temp_time = millis();
    
}


void loop(){
  
  if(check_time(10000)) {
     Serial.println("sending sensor data...");
     Serial.println(updateSensor("neuroscience", "date", "300"));
  }
  client.loop();
  
}

bool check_time(long interval) {
    if((millis() - temp_time) > interval) {
        temp_time = millis();
        
        return true;
    }
    else {
        return false;
    }
}

String updateSensor(String stream, String channel, String value) {
    HttpClient http;
    String path;

    http_header_t headers[] = {
      { "Content-Type", "application/json" },
      { "Authorization" , auth_token},
      { NULL, NULL } // NOTE: Always terminate headers will NULL
    };


    http_request_t request;
    http_response_t response;
    
    request.hostname = "api.servioticy.com";
    request.port = 80;
    
    path = "/";
    path.concat(SO_ID);
    path.concat("/streams/");
    path.concat(stream);
    
    request.path = path;
    
    String json = "{\"channels\": {\"";
    json.concat(channel);
    json.concat("\": {\"current-value\": \"");
    json.concat(value);
    json.concat("\"}}, \"lastUpdate\": ");
    json.concat(Time.now());
    json.concat("}");
    
    request.body = json;
    
    http.put(request, response, headers);
    
    return response.body;
    
}

