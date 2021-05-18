const int trig =4;
const int echo =5;
float distance;

void setup()
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.println("Ultrasonic senesor:");
}

void loop()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  distance = (pulseIn(echo,HIGH)/58.00);
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(500);
}
