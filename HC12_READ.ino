#include <SoftwareSerial.h>

#define HRX 2
#define HTX 3
#define OUT 4
#define BOOM 5

SoftwareSerial hc12(HRX, HTX);

void setup()
{
  Serial.begin(9600);
  hc12.begin(9600);

  pinMode(OUT, OUTPUT);
  pinMode(BOOM, OUTPUT);
}

void loop()
{
  if (hc12.available() > 0)
  {
    String receivedData = hc12.readString();

    if (receivedData == "DKDP")
    {
      Serial.println("BOOM...!");
      digitalWrite(OUT, HIGH);
      digitalWrite(BOOM, HIGH);
      delay(7000);
      digitalWrite(OUT, LOW);
      digitalWrite(BOOM, LOW);
    }
  }
}
