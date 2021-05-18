#include <SCoop.h>

/*
 Name:    Final_test_VS_.ino
 Created: 2020/11/29 20:37:18
 Author:  NicholasYe
*/

const int negLF = 3;//左前负极
const int posLF = 4;//左前正极
const int negRF = 5;//右前负极
const int posRF = 6;//右前正极
int pwmLF = 7;//左前轮pwm
int pwmRF = 8;//右前轮pwm

const int negLB = 9;//左后负极
const int posLB = 10;//左后正极
const int negRB = 11;//右后负极
const int posRB = 12;//右后正极
int pwmLB = 13;//左后轮pwm
int pwmRB = 14;//右后轮pwm

const int trigCA = 15;//超声波传感器CA
const int echoCA = 16;
float distanceCA;//A传感器返回距离

const int trigCB = 17;//超声波传感器CB
const int echoCB = 18;
float distanceCB;//B传感器返回距离

const int trigCC = 23;//超声波传感器CC
const int echoCC = 24;
float distanceCC;//C传感器返回距离

const int trigCD = 25;//超声波传感器CD
const int echoCD = 26;
float distanceCD;//D传感器返回距离

const int lightGA = 19;//光电传感器GA
int lightnumGA;//光电传感器GA返回数值

const int lightGB = 20;//光电传感器GB
int lightnumGB;//光电传感器GB返回数值

const int lightGC = 21;//光电传感器GC
int lightnumGC;//光电传感器GC返回数值

const int lightGD = 22;//光电传感器GD
int lightnumGD;//光电传感器GD返回数值

const int gray1 = A1;//灰度传感器GR1
int graynum1;//灰度传感器返回数值

boolean on_stage = false;
boolean car_detect = false;

//设置初值
void setup()
{
  Serial.begin(9600);
  Serial.println("Senesor:");
  pinMode(negLF, OUTPUT);//引脚3
  pinMode(posLF, OUTPUT);//引脚4
  pinMode(negRF, OUTPUT);//引脚5
  pinMode(posRF, OUTPUT);//引脚6
  pinMode(pwmLF, OUTPUT);//引脚7
  pinMode(pwmRF, OUTPUT);//引脚8

  pinMode(negLB, OUTPUT);//引脚9
  pinMode(posLB, OUTPUT);//引脚10
  pinMode(negRB, OUTPUT);//引脚11
  pinMode(posRB, OUTPUT);//引脚12
  pinMode(pwmLB, OUTPUT);//引脚13
  pinMode(pwmRB, OUTPUT);//引脚14

  pinMode(trigCA, OUTPUT);//超声波传感器CA
  pinMode(echoCA, INPUT);

  pinMode(trigCB, OUTPUT);//超声波传感器CB
  pinMode(echoCB, INPUT);

  pinMode(trigCC, OUTPUT);//超声波传感器CC
  pinMode(echoCC, INPUT);

  pinMode(trigCD, OUTPUT);//超声波传感器CD
  pinMode(echoCD, INPUT);

  pinMode(lightGA, INPUT);//光电传感器GA
  digitalWrite(lightGA, LOW);

  pinMode(lightGB, INPUT);//光电传感器GB
  digitalWrite(lightGB, LOW);

  pinMode(lightGC, INPUT);//光电传感器GC
  digitalWrite(lightGC, LOW);

  pinMode(lightGD, INPUT);//光电传感器GD
  digitalWrite(lightGD, LOW);

  pinMode(gray1, INPUT);//灰度传感器GR1

  pinMode(LED_BUILTIN, OUTPUT);//LED闪烁 
}


//主循环
void loop()
{
  judge_stage();
  if (on_stage)
  {
    detect_car();
    if (car_detect)
    {
      attact();
    }
    else
    {
      defence();
    }
  }
  else
  {
    back_stage();
  }

}

//判断是否在擂台
void judge_stage()
{

}

//返回擂台
void back_stage()
{

}

//搜索对方小车
void detect_car()
{

}

//撞击小车
void attact()
{

}

//防御旋转
void defence()
{

}







































//前进函数
void forward(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
  analogWrite(pwmLF, LFmotorSpeed);//左前pwm
  analogWrite(pwmRF, RFmotorSpeed);//右前pwm
  analogWrite(pwmLB, LBmotorSpeed);//左后pwm
  analogWrite(pwmRB, RBmotorSpeed);//右后pwm
  digitalWrite(posLF, HIGH);//左前向前
  digitalWrite(negLF, LOW);
  digitalWrite(posRF, HIGH);//右前向前
  digitalWrite(negRF, LOW);
  digitalWrite(posLB, HIGH);//左后向前
  digitalWrite(negLB, LOW);
  digitalWrite(posRB, HIGH);//右后向前
  digitalWrite(negRB, LOW);
}

//后退函数
void back(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
  analogWrite(pwmLF, LFmotorSpeed);//左前pwm
  analogWrite(pwmRF, RFmotorSpeed);//右前pwm
  analogWrite(pwmLB, LBmotorSpeed);//左后pwm
  analogWrite(pwmRB, RBmotorSpeed);//右后pwm
  digitalWrite(posLF, LOW);//左前向后
  digitalWrite(negLF, HIGH);
  digitalWrite(posRF, LOW);//右前向后
  digitalWrite(negRF, HIGH);
  digitalWrite(posLB, LOW);//左后向后
  digitalWrite(negLB, HIGH);
  digitalWrite(posRB, LOW);//右后向后
  digitalWrite(negRB, HIGH);
}

//停止函数
void brake(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
  analogWrite(pwmLF, LFmotorSpeed);//左前pwm
  analogWrite(pwmRF, RFmotorSpeed);//右前pwm
  analogWrite(pwmLB, LBmotorSpeed);//左后pwm
  analogWrite(pwmRB, RBmotorSpeed);//右后pwm
  digitalWrite(posLF, LOW);//左前停
  digitalWrite(negLF, LOW);
  digitalWrite(posRF, LOW);//右前停
  digitalWrite(negRF, LOW);
  digitalWrite(posLB, LOW);//左后停
  digitalWrite(negLB, LOW);
  digitalWrite(posRB, LOW);//右后停
  digitalWrite(negRB, LOW);
}

//右转
void right(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
  analogWrite(pwmLF, LFmotorSpeed);//左前pwm
  analogWrite(pwmRF, RFmotorSpeed);//右前pwm
  analogWrite(pwmLB, LBmotorSpeed);//左后pwm
  analogWrite(pwmRB, RBmotorSpeed);//右后pwm
  digitalWrite(posLF, HIGH);//左前向前
  digitalWrite(negLF, LOW);
  digitalWrite(posRF, LOW);//右前向后
  digitalWrite(negRF, HIGH);
  digitalWrite(posLB, HIGH);//左后向前
  digitalWrite(negLB, LOW);
  digitalWrite(posRB, LOW);//右后向后
  digitalWrite(negRB, HIGH);
}

//左转
void left(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
  analogWrite(pwmLF, LFmotorSpeed);//左前pwm
  analogWrite(pwmRF, RFmotorSpeed);//右前pwm
  analogWrite(pwmLB, LBmotorSpeed);//左后pwm
  analogWrite(pwmRB, RBmotorSpeed);//右后pwm
  digitalWrite(posLF, LOW);//左前向
  digitalWrite(negLF, HIGH);
  digitalWrite(posRF, HIGH);//右前向
  digitalWrite(negRF, LOW);
  digitalWrite(posLB, LOW);//左后向
  digitalWrite(negLB, HIGH);
  digitalWrite(posRB, HIGH);//右后向
  digitalWrite(negRB, LOW);
}

//超声波检测CA
int CA()
{
  digitalWrite(trigCA, LOW);
  digitalWrite(trigCA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigCA, LOW);
  distanceCA = (pulseIn(echoCA, HIGH) / 58.00);
  return distanceCA;
}

//超声波检测CB
int CB()
{
  digitalWrite(trigCB, LOW);
  digitalWrite(trigCB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigCB, LOW);
  distanceCB = (pulseIn(echoCB, HIGH) / 58.00);
  return distanceCB;
}

//超声波检测CC
int CC()
{
  digitalWrite(trigCC, LOW);
  digitalWrite(trigCC, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigCC, LOW);
  distanceCC = (pulseIn(echoCC, HIGH) / 58.00);
  return distanceCC;
}

//超声波检测CD
int CD()
{
  digitalWrite(trigCD, LOW);
  digitalWrite(trigCD, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigCD, LOW);
  distanceCD = (pulseIn(echoCD, HIGH) / 58.00);
  return distanceCD;
}

//光电传感器GA
int GA()
{
  int valueA = 0;
  lightnumGA = digitalRead(lightGA);
  valueA = lightnumGA;
  return valueA;
}

//光电传感器GB
int GB()
{
  int valueB = 0;
  lightnumGB = digitalRead(lightGB);
  valueB = lightnumGB;
  return valueB;
}

//光电传感器GC
int GC()
{
  int valueC = 0;
  lightnumGC = digitalRead(lightGC);
  valueC = lightnumGC;
  return valueC;
}

//光电传感器GD
int GD()
{
  int valueD = 0;
  lightnumGD = digitalRead(lightGD);
  valueD = lightnumGD;
  return valueD;
}

//灰度传感器Gray1
int Gray1()
{
  int level1 = 0;
  graynum1 = analogRead(1);
  level1 = graynum1;
  return level1;
}
