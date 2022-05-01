//Based on example code from SEEED studio wiki
//for 125kHz GROVE RFID reader
//GPL V3

/*
  link between the computer and the SoftSerial Shield
 at 9600 bps 8-N-1
 Computer is connected to Hardware UART
 SoftSerial Shield is connected to the Software UART:D2&D3
 */

#include <SoftwareSerial.h>
#include <millisDelay.h>

SoftwareSerial SoftSerial(10, 8);
unsigned char buffer[64];       // buffer array for data receive over serial port
String intest="";                //input string
char buffchar;
int count = 0;                    // counter for buffer array
int coin = 9;
int trigs = 15;
millisDelay trigDelay;

void setup()
{
  SoftSerial.begin(9600);     // the SoftSerial baud rate
  Serial.begin(9600);         // the Serial port of Arduino baud rate.
  pinMode(coin, OUTPUT);
  pinMode(trigs, OUTPUT);
  digitalWrite(trigs, HIGH);  //turn switch reed on so boards stays on after magnet switch triggered
  trigDelay.start(10000);
}


void loop()

{
  if (trigDelay.justFinished()) {
  digitalWrite(trigs, LOW);
}
  // if date is coming from software serial port ==> data is coming from SoftSerial shield
RFIDread();
if (intest.equals("000000201434"))
{
  Serial.println(" match ");     // if no data transmission ends, write buffer to hardware serial port
  Serial.println(intest);
  SoftSerial.end();
  for(int l=0; l < 6; ++l)
    {
      digitalWrite(coin, HIGH);
      delay(100);  
      digitalWrite(coin, LOW);
      delay(100);
    }
  SoftSerial.begin(9600);
  intest = "";
  delay(2000);
}
else if (intest.endsWith(""))
{

  
  Serial.println(intest);
  intest="";
  
}
    
}

void RFIDread()
{
    if (SoftSerial.available())              
  {
    while(SoftSerial.available())               // reading data into char array
    {
      buffchar = SoftSerial.read();      // writing data into array
      //Serial.println(int(buffchar));
      intest += buffchar;
      if (int(buffchar)= 3)break;
      //count++;
//      if(buffchar=' ')break;

    }
}
}

void clearBufferArray()                 // function to clear buffer array
{
  // clear all index of array with command NULL
  for (int i=0; i<count; i++)
  {
    buffer[i]=NULL;
  } 
intest = "";  

}
