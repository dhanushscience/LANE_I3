#include <SoftwareSerial.h>

SoftwareSerial hc12(2, 3);

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String pythonData = Serial.readStringUntil('\n');
    pythonData.trim(); 


    if (pythonData.equals("detected"))
    {
      SendDKDP();
    }
  }
}

void SendDKDP()
{
  hc12.write("DKDP");
  delay(1000);
}
