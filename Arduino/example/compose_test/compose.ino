//change to 1 for printing debug messages on Serial Monitor
int DEBUG = 0;

//COMPOSE defaults
int compose_port = 80;
char compose_server[] = "api.servioticy.com";

int channel_counter = 0;
String channels[10];
char time[10]; 
String ntp = "";

char *auth_key;



void setAuthkey(char *key) {
     auth_key = key;
}

void setChannelData(String channel_name, String value) {
  channels[channel_counter] = "\""+channel_name+"\": {\"current-value\": \""+value+"\"}";
  channel_counter++;
}

 
int submitSO(String stream_name, char *id) {
 
  int recv_counter, i = 0;
  //get epoch time:
  getEpoch();
  
  
  //construct the JSON:
  String json1 = "{\"channels\": {";
  String json2 = "";
  for(i=0;i<channel_counter-1;i++) {
      json2 = json2+channels[i]+","; 
  }
  String json3 = json2 + channels[i] +"},\"lastUpdate\": "+time[0]+time[1]+time[2]+time[3]+time[4]+time[5]+time[6]+time[7]+time[8]+time[9]+"}";
   
  int totallength = json1.length() + json3.length();
 
  
  if (client.connect(compose_server, compose_port)) {
    if(DEBUG)
    Serial.println("connected...");
    // send the HTTP PUT request:
    client.print("PUT /");
    client.print(id);
    client.print("/streams/");
    client.print(stream_name);
    client.println(" HTTP/1.1");
    client.println("Host: api.servioticy.com");
    client.print("Authorization: ");
    client.println(auth_key);
    client.print("User-Agent: ");
    client.println("Arduino");
    client.print("Content-Length: ");

    // print the length of the body request in bytes:
    client.println(totallength);
    
    //Serial.println(66+valueLength+channel_length);

    // last pieces of the HTTP PUT request:
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();

    // here's the actual content of the PUT request:
    client.print(json1);
    client.println(json3);
  
    if(DEBUG) {
    while(true){
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
        recv_counter++;
        if (recv_counter>500) break;
      }
      
     }
    }

  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    return 0;
  }
 
  return 1;
}


void getEpoch() {
  int stringPos = 0;
  
  int linecounter=0;
 
  if (client.connect("192.168.9.243", 8000)) {
    // Make a HTTP request:
    client.println("GET / HTTP/1.1");
    client.println("Host: 192.168.9.243");
    client.println("Connection: close");
    client.println();
    while(true){
      if (client.available()) {
        char c = client.read();
        if(c=='\n') {
         linecounter++;
        }
        if(linecounter==5) {
          time[stringPos] = c;
          stringPos ++;
        }
        if(linecounter==6) {
          break;
        }
       
      }
      
    }
  }
  else {
    Serial.println("Error getting time");
    client.stop();
  }
  
  
}
