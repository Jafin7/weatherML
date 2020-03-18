#include <Wire.h>
#include <hp_BH1750.h>

hp_BH1750 lux_snsr;
 
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  lux_snsr.begin(0x23);
  lux_snsr.calibrateTiming();
  lux_snsr.start();
}
 
void loop()
{
    float lux = lux_snsr.getLux();
    Serial.println(lux);
    lux_snsr.start();
    delay(1000);
}
