#include <Servo.h>

Servo myservo;  // 定义Servo对象来控制
int pos = 180;    // 角度存储变量

void setup() 
{
    myservo.attach(7);  // 控制线连接数字7
    myservo.write(90);
    delay(2000);
}

void loop() 
{
  pos=pos-180;
  myservo.write(pos);
  delay(3000);
  pos=pos+360;
  myservo.write(pos);
  delay(3000);
  pos=pos-180;
  myservo.write(pos);
  delay(3000);
}
