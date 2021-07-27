// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>
#include<SoftwareSerial.h>
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String data;
String ontime = "";
String offtime = "";
String temp;
boolean run= true;

String off_hour = "";
String off_min = "";
String off_sec= "";
String o_hour= "";
String o_min = "";
String o_sec = "";
int req_time;
SoftwareSerial mySerial(9,10);

void setup () {

  
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  digitalWrite(8,HIGH);
  EEPROM.write(0,0);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  run = true;

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled

    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
      rtc.adjust(DateTime(F(__DATE__ ), F(__TIME__ )));
      DateTime t = DateTime(rtc.now().unixtime() + 6);
      rtc.adjust(t);

}



void loop () {


  
  DateTime now = rtc.now();

  
    if(mySerial.available()>0) {
     
     data=mySerial.readString();
     
    run = true;
     EEPROM.put(0,data);
    
    }

    if(EEPROM.read(0)!=NULL){
       while(run){
    
              EEPROM.get(0,temp);
              
          Serial.println(temp + "  EEPROM DATA");

          Serial.println(data + "  SEND DATA");
            Serial.println(data.length());

     offtime = "";
     ontime = "";
     o_hour = "";
     o_min = "";
     o_sec = "";
     off_hour = "";
     off_min = "";
     off_sec = "";
      for(int i=0;i<temp.length();i++){
          if(temp.charAt(i)=='*'){
            for(int j = i+1;j<temp.length();j++){
                offtime = offtime + temp.charAt(j);
            }

            break;
            
          }
          ontime = ontime + temp.charAt(i);
          
        
      }
//     
//
//
//
//        for(int k = 0;k<ontime.length();k++){
//
//      if(ontime.charAt(k)=='$'){
//
//        for(int l = k+1;l<ontime.length();l++){
//
//          if(ontime.charAt(l)==':'){
//
//            for(int m = l+1;m<ontime.length();m++){
//              o_sec = o_sec + ontime.charAt(m);
//              
//            }
//            break;
//          }
//
//          o_min = o_min + ontime.charAt(l);
//          
//        }
//        
//      }
//      if(o_min.equals("") && o_sec.equals("")){
//        o_hour = o_hour + ontime.charAt(k);
//      }
//      
//    }
//
//
//    for(int offh = 0;offh<offtime.length();offh++){
//
//      if(offtime.charAt(offh)=='$'){
//
//        for(int offm = offh+1;offm<offtime.length();offm++){
//
//          if(offtime.charAt(offm)==':'){
//
//            for(int offs = offm+1;offs<offtime.length();offs++){
//              off_sec = off_sec + offtime.charAt(offs);
//              
//            }
//            break;
//          }
//
//          off_min = off_min + offtime.charAt(offm);
//          
//        }
//        
//      }
//
//      if(off_min.equals("") && off_sec.equals("")){
//        off_hour = off_hour + off_hour.charAt(offh);
//      }
//      
//    }
    Serial.println(ontime + " ontime");
    Serial.println(offtime + " offtime" );
    Serial.println(o_hour);
    Serial.println(o_min);
    Serial.println(o_sec);
    Serial.println(off_hour);
    Serial.println(off_min);
    Serial.println(off_sec);


      run = false;
    
    }
    }

   
 
   

    

  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
 

String on = (String)now.hour()+'$'+(String)now.minute()+':'+(String)now.second();
 
 
 if(on.equals(ontime)){
  digitalWrite(8,LOW);
 }

 if(on.equals(offtime)){
  digitalWrite(8,HIGH);
 }

// if((String)now.minute() > o_min&&(String)now.minute()<off_min){
//  digitalWrite(8,LOW);
// }
// else if((String)now.minute() == off_min && (String)now.second() >= o_sec && (String)now.second()<off_sec){
//  digitalWrite(8,LOW);
// }
  


  //    Serial.print(" since midnight 1/1/1970 = ");
  //    Serial.print(now.unixtime());
  //    Serial.print("s = ");
  //    Serial.print(now.unixtime() / 86400L);
  //    Serial.println("d");

  // calculate a date which is 7 days and 30 seconds into the future
  //    DateTime future (now + TimeSpan(1,1,0,0));
  //
  //    Serial.print(" now + 7d + 30s: ");
  //    Serial.print(future.year(), DEC);
  //    Serial.print('/');
  //    Serial.print(future.month(), DEC);
  //    Serial.print('/');
  //    Serial.print(future.day(), DEC);
  //    Serial.print(' ');
  //    Serial.print(future.hour(), DEC);
  //    Serial.print(':');
  //    Serial.print(future.minute(), DEC);
  //    Serial.print(':');
  //    Serial.print(future.second(), DEC);
  //    Serial.println();
  ////
  //    Serial.println();
  delay(1000);
  
}
