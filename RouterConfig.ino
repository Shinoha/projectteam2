
 
#include <SoftwareSerial.h>
#include <TimerOne.h>

#define rxPin 2
#define txPin 3

SoftwareSerial mySerial(rxPin, txPin);
 
int flag;
 
void Callback()
{
  switch(flag)
  {
    // This command sets WPA Passphrase as “software”
    case 0: Serial.print("AT+WWPA=software\r\n");  mySerial.print("AT+WWPA=software\r\n");     break; 
    // This command sets WizFi210 as using fixed IP address (not DHCP). When the IP address is acquired by DHCP..                      
    case 1: Serial.print("AT+NDHCP=0\r\n");          mySerial.print("AT+NDHCP=0\r\n");             break;
    //This command sets the module with IP address (192.168.0.119), Subnet Mast (255.255.255.0), and Gateway Address (192.168.0.1).                     
    case 2: Serial.print("AT+NSET=192.168.0.119, 255.255.255.0, 192.168.0.1\r\n");        mySerial.print("AT+NSET=192.168.0.119, 255.255.255.0, 192.168.0.1\r\n");    break; 
    // This command sets WizFi210 with Server(1), TCP(1) and Port number (4000).
    case 3: Serial.print("AT+NAUTO=1,1,,4000\r\n");  mySerial.print("AT+NAUTO=1,1,,4000\r\n");     break;    
    // This command sets the AP’s Mode (0:Infrastructure), SSID(“dlink”), BSSID(Default)                  
    case 4: Serial.print("AT+WAUTO=0,dlink\r\n");    mySerial.print("AT+WAUTO=0,dlink\r\n");       break; 
    // This command initializes auto connection.                     
    case 5: Serial.print("ATA\r\n");                 mySerial.print("ATA\r\n");    flag++;         break;                      
    default: break;
  }
}
 
void setup()
{
   // define pin modes for tx, rx pins:
   flag = 0;                                         // init flag
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   mySerial.begin(9600);                             // setting baud to 9600
   Serial.begin(9600);
   Serial.println("Wifi Start ...");
   Timer1.initialize(1000000);                       // setting callback is 1s
   Timer1.attachInterrupt(Callback); 
}
 
void loop()
{
  int i = 0;
  char someChar[128] = {0};
  // when characters arrive over the serial port...
  if(Serial.available()) {
    do{
      someChar[i++] = Serial.read();
      delay(3);                  
    }while (Serial.available() > 0);  
    Serial.println(someChar);
    mySerial.println(someChar);
  }
 
  char someChar2[128] = {0};
  while(mySerial.available()) {
    do{
      someChar2[i++] = mySerial.read();
      delay(3);                  
    }while (mySerial.available() > 0);
    if( strstr(someChar2, "OK"))
    {
      Serial.print("OK\r\n");
      flag++;
    }
    else
      Serial.print(someChar2);
  }  
}


