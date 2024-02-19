int vr_pin = A0;
int led_pin =11;
void setup()
{
  pinMode(vr_pin,INPUT);
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Test
  int vr = analogRead(vr_pin);
  int vr1= map (vr,0,1023,0,10);
  analogWrite(led_pin,vr1);
  Serial.println(vr1);
  delay(500);
}
