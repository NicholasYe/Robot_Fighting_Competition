/*
 Name:		Sensor_test_Motor.ino
 Created:	2021/3/22 15:48:40
 Author:	NicholasYe
*/

#include <math.h>

const int negLF = 25; //左前负极
const int posLF = 24; //左前正极
const int negRF = 44; //右前负极
const int posRF = 45; //右前正极
const int pwmLF = 9;  //左前轮pwm
const int pwmRF = 5;  //右前轮pwm

const int negLB = 22; //左后负极
const int posLB = 23; //左后正极
const int negRB = 42; //右后负极
const int posRB = 43; //右后正极
const int pwmLB = 6;  //左后轮pwm
const int pwmRB = 3;  //右后轮pwm

void setup()
{
	Serial.begin(9600);//打开接口9600
	Serial.println("Senesor:");

	pinMode(negLF, OUTPUT);//引脚
	pinMode(posLF, OUTPUT);//引脚
	pinMode(negRF, OUTPUT);//引脚
	pinMode(posRF, OUTPUT);//引脚
	pinMode(pwmLF, OUTPUT);//引脚
	pinMode(pwmRF, OUTPUT);//引脚

	pinMode(negLB, OUTPUT);//引脚
	pinMode(posLB, OUTPUT);//引脚
	pinMode(negRB, OUTPUT);//引脚
	pinMode(posRB, OUTPUT);//引脚
	pinMode(pwmLB, OUTPUT);//引脚
	pinMode(pwmRB, OUTPUT);//引脚

  pinMode(LED_BUILTIN, OUTPUT);//LED闪烁
}

void loop()
{
    motor_test();
}

void motor_test()
{
	//rotate_clockwise(200,200,200,200);

    // forward(0,0,0,0);
    // forward(255,255,255,255);
    // back(0,0,0,0);
    // back(255,255,255,255);
    // left(0,0,0,0);
    // left(255,255,255,255);
    // right(0,0,0,0);
    // right(255,255,255,255);
    // brake(0,0,0,0);
    // brake(255,255,255,255);
    // rotate_clockwise(0,0,0,0);
    // rotate_clockwise(255,255,255,255);
    // rotate_counterclockwise(0,0,0,0);
    // rotate_counterclockwise(255,255,255,255);
    delay(220);
    brake(0,0,0,0);
    delay(2000);
}

//前进函数
void forward(byte LFmotorSpeed, byte RFmotorSpeed, byte LBmotorSpeed, byte RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed); //左前轮转速
	analogWrite(pwmRF, RFmotorSpeed); //右前轮转速
	analogWrite(pwmLB, LBmotorSpeed); //左后轮转速
	analogWrite(pwmRB, RBmotorSpeed); //右后轮转速
	digitalWrite(posLF, HIGH);		  //左前向前
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, HIGH); //右前向前
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, HIGH); //左后向前
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, HIGH); //右后向前
	digitalWrite(negRB, LOW);
}

//后退函数
void back(byte LFmotorSpeed, byte RFmotorSpeed, byte LBmotorSpeed, byte RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed); //左前轮转速
	analogWrite(pwmRF, RFmotorSpeed); //右前轮转速
	analogWrite(pwmLB, LBmotorSpeed); //左后轮转速
	analogWrite(pwmRB, RBmotorSpeed); //右后轮转速
	digitalWrite(posLF, LOW);		  //左前向后
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, LOW); //右前向后
	digitalWrite(negRF, HIGH);
	digitalWrite(posLB, LOW); //左后向后
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, LOW); //右后向后
	digitalWrite(negRB, HIGH);
}

//停止函数
void brake(byte LFmotorSpeed, byte RFmotorSpeed, byte LBmotorSpeed, byte RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed); //左前轮转速
	analogWrite(pwmRF, RFmotorSpeed); //右前轮转速
	analogWrite(pwmLB, LBmotorSpeed); //左后轮转速
	analogWrite(pwmRB, RBmotorSpeed); //右后轮转速
	digitalWrite(posLF, LOW);		  //左前停
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, LOW); //右前停
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW); //左后停
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, LOW); //右后停
	digitalWrite(negRB, LOW);
}

//顺时针旋转
void rotate_clockwise(byte LFmotorSpeed, byte RFmotorSpeed, byte LBmotorSpeed, byte RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed); //左前轮转速
	analogWrite(pwmRF, RFmotorSpeed); //右前轮转速
	analogWrite(pwmLB, LBmotorSpeed); //左后轮转速
	analogWrite(pwmRB, RBmotorSpeed); //右后轮转速
	digitalWrite(posLF, HIGH);		  //左前向前
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, LOW); //右前向后
	digitalWrite(negRF, HIGH);
	digitalWrite(posLB, HIGH); //左后向前
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, LOW); //右后向后
	digitalWrite(negRB, HIGH);
}

//逆时针旋转
void rotate_counterclockwise(byte LFmotorSpeed, byte RFmotorSpeed, byte LBmotorSpeed, byte RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed); //左前轮转速
	analogWrite(pwmRF, RFmotorSpeed); //右前轮转速
	analogWrite(pwmLB, LBmotorSpeed); //左后轮转速
	analogWrite(pwmRB, RBmotorSpeed); //右后轮转速
	digitalWrite(posLF, LOW);		  //左前向前
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, HIGH); //右前向后
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW); //左后向前
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, HIGH); //右后向后
	digitalWrite(negRB, LOW);
}
