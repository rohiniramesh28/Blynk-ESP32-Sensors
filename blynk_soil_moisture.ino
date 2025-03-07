#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <Wire.h>
#include <DHT.h>
#include <RTClib.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


char ssid[] = "Your_SSID";     
char pass[] = "Your_PASSWORD"; 


#define DHTPIN 25       
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);


RTC_DS3231 rtc;

const int soilMoisturePin = 34; 

#define VIRTUAL_SOIL V0      
#define VIRTUAL_HUMIDITY V1  
#define VIRTUAL_TEMP V2      
#define VIRTUAL_TIME V3      

void setup() {
  Serial.begin(115200);
  delay(1000);


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


  dht.begin();
  
  Wire.begin(21, 22);
  

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1); 
  }
  

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time to compile time!");
    rtc.adjust(DateTime(F(DATE), F(TIME)));
  }
}

void loop() {
  Blynk.run(); 


  float temperature = dht.readTemperature(); 
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }
  
  
  int soilValue = analogRead(soilMoisturePin);
  
 
  int moisturePercent = map(soilValue, 0, 4095, 100, 0); 

 
  DateTime now = rtc.now();
  String currentTime = String(now.year()) + "/" + 
                       String(now.month()) + "/" + 
                       String(now.day()) + " " +
                       String(now.hour()) + ":" + 
                       String(now.minute()) + ":" + 
                       String(now.second());


  Serial.println("----------- SENSOR DATA -----------");
  Serial.print("Time: ");
  Serial.println(currentTime);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println(" %");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.println("-----------------------------------");

  Blynk.virtualWrite(VIRTUAL_SOIL, moisturePercent);
  Blynk.virtualWrite(VIRTUAL_HUMIDITY, humidity);
  Blynk.virtualWrite(VIRTUAL_TEMP, temperature);
  Blynk.virtualWrite(VIRTUAL_TIME, currentTime); 

  delay(2000);
}
