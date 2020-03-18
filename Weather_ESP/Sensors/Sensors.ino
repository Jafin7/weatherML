#include <WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <hp_BH1750.h>

const char* ssid = "Redmi";
const char* password = "qwertyui";

int DHT_pin = 4;
int CSM_pin = 36;
Adafruit_BME280 bme;
hp_BH1750 lux_snsr;

float temperture;
float humidity;
float pressure;
float lux;
int moisture=0;

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
  moisture = analogRead(CSM_pin);
	
	Serial.print("Temperature: "); Serial.println(temperture);
	Serial.print("Humidity   : "); Serial.println(humidity);
	Serial.print("Pressure   : "); Serial.println(pressure);
	Serial.print("Light-LUX  : "); Serial.println(lux);
  Serial.print("Moisture   : "); Serial.println(moisture);
  Serial.println(""); 
	delay(3000);
}
