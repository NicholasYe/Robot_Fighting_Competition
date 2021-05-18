const int gray1=A1;//灰度传感器GR1
int graynum1;//灰度传感器返回数值

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Senesor:");
  pinMode(gray1,INPUT);//灰度传感器GR1
}

void loop() {
  // put your main code here, to run repeatedly:
  Gray1();
  Serial.print(Gray1());
  Serial.println();
}

int Gray1()
{
  int level1=0;
  graynum1=analogRead(1);
  level1=graynum1;
  return level1;
}
