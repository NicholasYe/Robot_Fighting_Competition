const int negR=4;//右负极
const int posR=5;//右正极
const int negL=6;//左负极
const int posL=7;//左正极
const int pwmR=9;//右轮pwm
const int pwmL=10;//左轮pwm

//设置初值
void setup()
{
  pinMode(posR,OUTPUT);//引脚4
  pinMode(negR,OUTPUT);//引脚5
  pinMode(posL,OUTPUT);//引脚6
  pinMode(negL,OUTPUT);//引脚7
  pinMode(pwmR,OUTPUT);//引脚9
  pinMode(negL,OUTPUT);//引脚10
}

void loop()
{
  right(200,200);
  delay(2000);
  pause(0,0);
  delay(2000);
  left(200,200);
  delay(2000);
  pause(0,0);
  delay(2000);
}

//右转
void right(byte RmotorSpeed,byte LmotorSpeed)
{
  analogWrite(pwmR,RmotorSpeed);//右轮转速
  analogWrite(pwmL,LmotorSpeed);//左轮转速
  digitalWrite(posR,LOW);//右轮停止
  digitalWrite(negR,LOW);
  digitalWrite(posL,LOW);//左轮反转
  digitalWrite(negL,HIGH);
}

//左转
void left(byte RmotorSpeed,byte LmotorSpeed)
{
  analogWrite(pwmR,RmotorSpeed);//右轮转速
  analogWrite(pwmL,LmotorSpeed);//左轮转速
  digitalWrite(posR,HIGH);//右轮正转
  digitalWrite(negR,LOW);
  digitalWrite(posL,LOW);//左轮停止
  digitalWrite(negL,LOW);
}

//停止函数
void pause(byte RmotorSpeed,byte LmotorSpeed)
{
  analogWrite(pwmR,RmotorSpeed);//右轮转速
  analogWrite(pwmL,LmotorSpeed);//左轮转速
  digitalWrite(posR,LOW);//右轮停止
  digitalWrite(negR,LOW);
  digitalWrite(posL,LOW);//左轮停止
  digitalWrite(negL,LOW);
}
