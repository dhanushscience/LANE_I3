//tested verified,but to be fine tuned
#include <Wire.h>
#include <Adafruit_VL53L0X.h>


#define DS_pin 4
#define STCP_pin 3
#define SHCP_pin 2 

#define ir1 5 //left
#define ir2 6 //right

#define cam_pin 1

#define rtoggle_pin 8
#define ltoggle_pin 9

#define r_led 10
#define g_led 11

#define r_blind 12
#define l_blind 13

// #define trigger_pin 12
// #define eco_pin 13

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int dec_digits  [10] {126,123,127,112,95,91,51,121,109,48};

//active low
int error = 0;
int n_error = 1;

int toggle_time= 10;
int toggle_time2=7;

int threshold_distance=50;

void setup()
{
  Serial.begin(9600);
  pinMode(ir1,INPUT);
   pinMode(ir2,INPUT);
  pinMode(cam_pin,INPUT);
  pinMode(rtoggle_pin,INPUT);
  pinMode(ltoggle_pin,INPUT);
  pinMode(r_led,OUTPUT);
  pinMode(g_led,OUTPUT);
  pinMode(DS_pin,OUTPUT);
  pinMode(STCP_pin,OUTPUT);
  pinMode(SHCP_pin,OUTPUT);
  pinMode(r_blind,OUTPUT);
  pinMode(l_blind,OUTPUT);
  // pinMode(trigger_pin,OUTPUT);
  // pinMode(eco_pin,INPUT);

  if (!lox.begin())
  {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  Serial.println(F("VL53L0X ready!"));

  digitalWrite(g_led,LOW);
  digitalWrite(r_led,LOW);
  digitalWrite(r_blind,LOW);
  digitalWrite(l_blind,LOW);
}

void loop() 
{
  // digitalWrite(trigger_pin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigger_pin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigger_pin, LOW);
  // long duration = pulseIn(eco_pin, HIGH);
  // float distance = duration * 0.034 / 2;
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  int ir1_out=digitalRead(ir1);
  // Serial.println("ir1-");
  // Serial.println(ir1_out);

  int ir2_out=digitalRead(ir2);
  // Serial.println("ir2-");
  // Serial.println(ir2_out);

  int cam_out=digitalRead(cam_pin);
  // Serial.println("cam_pin");
  // Serial.println(cam_pin);

  int rtoggle_out=digitalRead(rtoggle_pin);
  // Serial.println("rtoggle");
  // Serial.println(rtoggle_out);

  int ltoggle_out=digitalRead(ltoggle_pin);
  // Serial.println("ltoggle");
  // Serial.println(ltoggle_out);


  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  float distance =measure.RangeMilliMeter;
  // if (measure.RangeStatus != 4) {  // phase failures have incorrect data
  //   Serial.print(F("Distance (mm): "));
  //   Serial.println(measure.RangeMilliMeter);
  // } else {
  //   Serial.println(F("Out of range"));
  // }e
  //when all clear
  if(ir1_out==error)
  {
    digitalWrite(l_blind,HIGH);
    digitalWrite(r_blind,LOW);
  }
  else if(ir2_out==error)
  {
    digitalWrite(r_blind,HIGH);
    digitalWrite(l_blind,LOW);
  }
  else
  {
  digitalWrite(r_blind,LOW);
  digitalWrite(l_blind,LOW);
  }
  if(cam_out==n_error && ir1_out==n_error && ir2_out==n_error && distance>=threshold_distance)
  {
    if(ltoggle_out==error && rtoggle_out==error)
    {
      digitalWrite(g_led,HIGH);
      digitalWrite(r_led,LOW);
      Serial.println("yess");
      display();
    }
    else
    {
      digitalWrite(r_led,HIGH);
      digitalWrite(g_led,LOW);
      Serial.println("no");
    }
  }
  else
  {
    digitalWrite(r_led,HIGH);
    digitalWrite(g_led,LOW);
    Serial.println("no");
  }
 delay(500);
}

void display()
{
  // for (int j=0;j<toggle_time;j++)
  // {  
    for (int i=0;i<toggle_time;i++)
    {
      int rtoggle_out=digitalRead(rtoggle_pin);
      int ltoggle_out=digitalRead(ltoggle_pin);
       VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  long distance =measure.RangeMilliMeter;
  int ir1_out=digitalRead(ir1);
  int ir2_out=digitalRead(ir2);
  int cam_out=digitalRead(cam_pin);
      if(cam_out==error || ir1_out==error || ir2_out==error || distance<=threshold_distance || ltoggle_out==n_error || rtoggle_out==n_error )
      {
        Serial.println("no");
        break;
      }
      digitalWrite(STCP_pin,LOW);
      shiftOut(DS_pin, SHCP_pin, LSBFIRST,dec_digits[i]);
      shiftOut(DS_pin, SHCP_pin, LSBFIRST,dec_digits[0]);
      digitalWrite(STCP_pin,  HIGH);
      delay(1000);
    }
  // }
}
