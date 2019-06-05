/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <BME280I2C.h>
#include <Wire.h>



BME280I2C bme; 

//

// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = "***";           // Put you AUTH key here
char server[] = "***";         //Put you server adress here
uint16_t port = ****;          //Put you port number here
char ssid[] = "***";           //Put you WiFi network here
char pass[] = "***";           //Put you wifi pass here


void setupSensorsBME280()
{
   Wire.begin();

   bme.begin();

   switch(bme.chipModel())
   {
      case BME280::ChipModel_BME280:
        Serial.println("Found BME280 sensor! Success.");
        break;
      case BME280::ChipModel_BMP280:
        Serial.println("Found BMP280 sensor! No Humidity available.");
        break;
      default:
        Serial.println("Found UNKNOWN sensor! Error!");
   }
}

//*********************** BME280 *********************
void runSensorsBME280()
{
   static unsigned long prevTimeBME = 0;
   int stepSpeed=1;
     
     unsigned long sensorCheckTime = (15000/stepSpeed);
     if (sensorCheckTime<=5001) {sensorCheckTime=5001;}
     if(millis() - prevTimeBME > sensorCheckTime) {
       prevTimeBME=millis();
       /* Display atmospheric pressue in hPa */
       //   / 100.0F)*0.75006375541921

      float temp(NAN), hum(NAN), pres(NAN);
         BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
    BME280::PresUnit presUnit(BME280::PresUnit_Pa);

    bme.read(pres, temp, hum, tempUnit, presUnit);


       Blynk.virtualWrite(V1, temp); //*C
       Blynk.virtualWrite(V2, 
((pres/100.0F)*0.75006375541921)); // мм рт ст
       Blynk.virtualWrite(V3, hum); //%
       Serial.println(temp);
     }
}




void setup()
{


  
   Serial.begin(115200);
   Blynk.connectWiFi(ssid, pass);
   Blynk.config(auth, server, port);
   Blynk.connect();

   setupSensorsBME280();

}

void loop()
{
  Blynk.run();
 runSensorsBME280(); 
}
