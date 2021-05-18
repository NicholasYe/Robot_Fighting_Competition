/*
 Name:    Sensor_test.ino
 Created: 2020/12/8 15:00:30
 Author:  NicholasYe
*/



const int gray4 = A4;//灰度传感器GR4
int graynum4;//灰度传感器返回数值
int* level4;

// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(9600);
  Serial.println("Senesor:");
  pinMode(gray4, INPUT);//灰度传感器GR4

}

// the loop function runs over and over again until power down or reset
void loop() 
{
  Gray4();
  Serial.print(*level4);
  Serial.println();
}

//灰度传感器Gray(指针写法)  //未检测是否正确
int Gray4()
{
  graynum4 = analogRead(4);
  level4 = &graynum4;
}
