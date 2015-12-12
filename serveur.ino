/*
  WiFi Web Server
 */
 
#include <SPI.h>
#include <WiFi.h>
 
 
char ssid[] = "Ajou 7526";      // your network SSID (name) 
char pass[] = "75267526";   // your network password
 
int status = WL_IDLE_STATUS;
 
WiFiServer server(80);
 
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ;
  }
 
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
 
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);   
    status = WiFi.begin(ssid, pass);
 
    // wait 10 seconds for connection:
    delay(10000);
  } 
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}
 
 
void loop() {
  // listen for incoming phones
  WiFiClient phone = server.available();
  if (phone) {
    Serial.println("new phone");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (phone.connected()) {
      if (phone.available()) {
        int c = phone.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        
    
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          phone.println("HTTP/1.1 200 OK");
          phone.println("Content-Type: text/html");
          phone.println("Connection: close");  // the connection will be closed after completion of the response
          phone.println("Refresh: 5");  // refresh the page automatically every 5 sec
          phone.println();
          phone.println("<!DOCTYPE HTML>");
          phone.println("<html>");
          
          
          if (c ==1)
  {
     digitalWrite(9,HIGH);
     digitalWrite(7,LOW);
     digitalWrite(6,LOW);
     delay(10000);
   };
   
     if (c==2)
  {
     digitalWrite(9,LOW);
     digitalWrite(7,HIGH);
     digitalWrite(6,LOW);
     delay(10000);
   };
   
     if (c==3)
  {
     digitalWrite(9,LOW);
     digitalWrite(7,LOW);
     digitalWrite(6,HIGH);
     delay(10000);
   };
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
 
    // close the connection:
    phone.stop();
    Serial.println("phone disonnected");
  }
}
 
 
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
 
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
