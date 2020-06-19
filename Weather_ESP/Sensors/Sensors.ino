#include <WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <hp_BH1750.h>
//#include <FirebaseESP32.h>


const char* ssid = "Redmi";
const char* password = "qwertyui";
//const char* FIREBASE_HOST = "weather-station-3bfb2.firebaseio.com";
//const char* FIREBASE_AUTH = "wbeB6VYLh1smxSKVRfnh6E7wMYh3eDYYQYO6Mipz";
//FirebaseData firebaseData;
const char* DbServer = "http://13.235.238.94:3000/storeData";

int DHT_pin = 4;
int CSM_pin = 36;
Adafruit_BME280 bme;
hp_BH1750 lux_snsr;

float temperture = 0;
float humidity = 0;
float rainfall = 0;
float wind_spd = 0;
float lux = 0;
float pressure = 0;
float moisture = 0;

DHT dht(DHT_pin, DHT22);

void setup()
{
  Serial.begin(115200);
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("IP:");
  Serial.println(WiFi.localIP());

  pinMode(DHT_pin, INPUT);

  //  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
  bme.begin(0x76);
  lux_snsr.begin(0x23);
  lux_snsr.calibrateTiming();
  lux_snsr.start();
}

void loop()
{
  temperture = dht.readTemperature();
  humidity = dht.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  lux = lux_snsr.getLux();
  lux_snsr.start();
  //moisture = analogRead(CSM_pin);

  Serial.print("Temperature: "); Serial.println(temperture);
  Serial.print("Humidity   : "); Serial.println(humidity);
  Serial.print("Rainfall   : "); Serial.println(rainfall);
  Serial.print("Wind Speed : "); Serial.println(wind_spd);
  Serial.print("Light-LUX  : "); Serial.println(lux);
  Serial.print("Pressure   : "); Serial.println(pressure);
  Serial.print("Moisture   : "); Serial.println(moisture);
  Serial.println("");
  delay(60000);

  HTTPClient http;
  http.begin(DbServer);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String weather_data = "val_temp="+String(temperture)+"&val_humi="+String(humidity)+"&val_rain="+String(rainfall)+"&val_wind="+String(wind_spd)+"&val_light="+String(lux)+"&val_press="+String(pressure)+"&val_soil="+String(moisture);
  int result = http.POST(weather_data);

  if(result==200)
  {
    Serial.println("Valid data   : Accepted");
  }
  else
  {
    Serial.println("Invalid data : Rejected");
  }
  http.end();

  
  //  Firebase.pushString(firebaseData, "Temperature", String(temperture) + "°C");
  //  Firebase.pushString(firebaseData, "Humidity", String(humidity) + "%");
  //  Firebase.pushString(firebaseData, "Pressure", String(pressure) + "Pa");
  //  Firebase.pushString(firebaseData, "Light-LUX", String(lux) + "Lux");
  //  Firebase.pushString(firebaseData, "Moisture", String(moisture) + "%");


}
