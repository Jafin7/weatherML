#include <WiFi.h>
#include <DHT.h>

#define DHTTYPE DHT22

const char* ssid = "Redmi";
const char* password = "qwertyui";


uint8_t DHTPin = 4; 
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

}
void loop()
{
  Serial.println(dht.readTemperature());
  Serial.println(dht.readHumidity());
  Serial.println("");
  delay(1000);
}
