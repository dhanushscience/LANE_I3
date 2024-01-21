//final 4
//fromright
#define ir2 4
#define ir1 5
#define ir4 6
#define ir3 7
// #define ir5 13

//active high

#define top 8
#define bottom 9
#define top_right 10
#define bottom_right 11

int error=1;
void setup() 
{
  Serial.begin(9600);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);
  pinMode(top,OUTPUT);
  pinMode(top_right,OUTPUT);
  pinMode(bottom,OUTPUT);
  pinMode(bottom_right,OUTPUT);

  // pinMode(ir5,INPUT);
}


void loop() {
  int ir1_out=digitalRead(ir1);
  Serial.println("ir1-");
  Serial.println(ir1_out);

  int ir2_out=digitalRead(ir2);
  // Serial.println("ir2-");
  // Serial.println(ir2_out);

  int ir3_out=digitalRead(ir3);
  // Serial.println("ir3-");
  // Serial.println(ir3_out);

  int ir4_out=digitalRead(ir4);
  // Serial.println("ir4-");
  // Serial.println(ir4_out);
if (ir1_out==0)
{
  digitalWrite(top,HIGH);
  digitalWrite(bottom,LOW);
  digitalWrite(top_right,LOW);
  digitalWrite(bottom_right,LOW);
}

else if (ir2_out==0)
{
  digitalWrite(top,LOW);
  digitalWrite(bottom,HIGH);
  digitalWrite(top_right,LOW);
  digitalWrite(bottom_right,LOW);
}
else if (ir3_out==0)
{
  digitalWrite(top,LOW);
  digitalWrite(bottom,LOW);
  digitalWrite(top_right,HIGH);
  digitalWrite(bottom_right,LOW);
}
else if (ir4_out==0)
{
  digitalWrite(top,LOW);
  digitalWrite(bottom,LOW);
  digitalWrite(top_right,LOW);
  digitalWrite(bottom_right,HIGH);
}
else
{
  digitalWrite(top,LOW);
  digitalWrite(bottom,LOW);
  digitalWrite(top_right,LOW);
  digitalWrite(bottom_right,LOW);
}
}
