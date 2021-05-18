/*
 Name:		Final_version.ino
 Created:	2021/3/24 14:10:21
 Author:	NicholasYe
*/

#include <math.h>

const int negLF = 43; //左前负极
const int posLF = 42; //左前正极
const int negRF = 23; //右前负极
const int posRF = 22; //右前正极
const int pwmLF = 10; //左前轮pwm
const int pwmRF = 9;  //右前轮pwm

const int negLB = 45; //左后负极
const int posLB = 44; //左后正极
const int negRB = 25; //右后负极
const int posRB = 24; //右后正极
const int pwmLB = 5;  //左后轮pwm
const int pwmRB = 6;  //右后轮pwm

const int lightGA = 21; //光电传感器GA（左前）
int lightnumGA;			//光电传感器GA返回数值
int *ligGA = NULL;		//存储光电传感器数值lightnumGA的指针

const int lightGB = 27; //光电传感器GB（右前）
int lightnumGB;
int *ligGB = NULL;

const int lightGC = 40; //光电传感器GC（左后）
int lightnumGC;
int *ligGC = NULL;

const int lightGD = 19; //光电传感器GD（右后）
int lightnumGD;
int *ligGD = NULL;

const int lightGE = 26; //光电传感器GG（左）
int lightnumGE;
int *ligGE = NULL;

const int lightGF = 14; //光电传感器GH（右）
int lightnumGF;
int *ligGF = NULL;

const int lightGG = 20; //光电传感器GG（后）
int lightnumGG;
int *ligGG = NULL;

const int gray1 = A8;	 //灰度传感器GR1     //记得更改gray1函数中的analogRead()
int graynum1;			 //灰度传感器返回数值
int *gray_level1 = NULL; //存储灰度传感器数值graynum的指针
int gray_arr_result;	 //存储gray快排后的中值

const int trig = 37; //超声波传感器
const int echo = 36;
int sound_distance;		 //灰度传感器返回数值
int *sound_level = NULL; //存储超声波传感器数值distance的指针
int sound_arr_test;		 //储存sound快排后的中值

boolean on_stage = true; //台上台下判定

// the setup function runs once when you press reset or power the board
void setup()
{
	pinMode(negLF, OUTPUT); //引脚
	pinMode(posLF, OUTPUT); //引脚
	pinMode(negRF, OUTPUT); //引脚
	pinMode(posRF, OUTPUT); //引脚
	pinMode(pwmLF, OUTPUT); //引脚
	pinMode(pwmRF, OUTPUT); //引脚

	pinMode(negLB, OUTPUT); //引脚
	pinMode(posLB, OUTPUT); //引脚
	pinMode(negRB, OUTPUT); //引脚
	pinMode(posRB, OUTPUT); //引脚
	pinMode(pwmLB, OUTPUT); //引脚
	pinMode(pwmRB, OUTPUT); //引脚

	pinMode(lightGA, INPUT); //光电传感器GA
	digitalWrite(lightGA, LOW);

	pinMode(lightGB, INPUT); //光电传感器GB
	digitalWrite(lightGB, LOW);

	pinMode(lightGC, INPUT); //光电传感器GC
	digitalWrite(lightGC, LOW);

	pinMode(lightGD, INPUT); //光电传感器GD
	digitalWrite(lightGD, LOW);

	pinMode(lightGE, INPUT); //光电传感器GE
	digitalWrite(lightGE, LOW);

	pinMode(lightGF, INPUT); //光电传感器GF
	digitalWrite(lightGF, LOW);

	pinMode(lightGG, INPUT); //光电传感器GG
	digitalWrite(lightGG, LOW);

	pinMode(gray1, INPUT); //灰度传感器GR1

	pinMode(trig, OUTPUT); //超声波针脚输出
	pinMode(echo, INPUT);  //超声波针脚输入

	pinMode(LED_BUILTIN, OUTPUT); //LED闪烁

	//点亮小灯函数
	//digitalWrite(LED_BUILTIN, HIGH);

}

// the loop function runs over and over again until power down or reset
//循环检测是否启动小车
void loop()
{
	sensor_test();

	// //正式开始并跳入循环
	// if (*ligGG == 0) //车后光电传感器检测
	// {
	// 	start_setup();
	// }
}

//初始上台
void start_setup()
{
	//单次程序
	back(200, 200, 150, 150);
	delay(1200); //上台
	rotate_counterclockwise(255, 255, 255, 255);
	delay(360);
	forward(255, 255, 255, 255);
	delay(360);

	//循环程序
	if (1)
	{
		start_loop();
	}
}

//循环程序
void start_loop()
{
	on_stage_test(); //位置检测

	switch (on_stage) //选择程序
	{
	case true:
	{
		attack_mode();
		break;
	}
	case false:
	{
		return_stage();
		break;
	}
	}
}

//逻辑程序设计

//台上台下检测
void on_stage_test()
{
	sensor_test();
	if (*gray_level1 > 400) //数值待更改
	{
    	on_stage = true;
	}
	else
	{
		on_stage = false;
	}
}

//台上进攻程序
void attack_mode()
{
	sensor_test();

	//追敌部分
	//do...while写法
	if (*ligGA == 1)
	{
		back(255, 255, 255, 255);
		delay(200);
		back(200, 200, 200, 200);
		delay(400);
		rotate_clockwise(255, 255, 255, 255);
		delay(120); //旋转
		goto Reset;
	}
	else if (*ligGB == 1)
	{
		back(255, 255, 255, 255);
		delay(200);
		back(200, 200, 200, 200);
		delay(400);
		rotate_counterclockwise(255, 255, 255, 255);
		delay(120); //旋转
		goto Reset;
	}
	if ((*ligGE == 0) || (*ligGF == 0))
	{
		if (*ligGE == 0) //左边检测到车子
		{
			rotate_counterclockwise(255, 255, 255, 255);
			delay(75);
			goto Reset;
		}
		if (*ligGF == 0) //右边检测到车子
		{
			rotate_clockwise(255, 255, 255, 255);
			delay(75);
			goto Reset;
		}
	}
	// else if ((*ligGC == 1) || (*ligGD == 1)) //车子快被撞出去了
	// {
	// 	Serial.println("加速");
	// 	forward(220, 220, 220, 220);
	// 	delay(2);
	// 	goto Reset;
	// }
	else if (*sound_level <= 20)
	{
		forward(220, 220, 220, 220);
		delay(15);
		goto Reset;
	}

	forward(120,120,120,120);

Reset:
	start_loop();
}

void return_stage()
{
Reset_return_stage:
	digitalWrite(LED_BUILTIN, HIGH);
	rotate_clockwise(255, 255, 255, 255);
	sensor_test();

	if (*ligGG == 0)
	{
		rotate_clockwise(255, 255, 255, 255);
		delay(640); //需要测定转动时间！！
	}
	else
	{
		goto Reset_return_stage;
	}

	back(200, 200, 150, 150);
	delay(1400);
	digitalWrite(LED_BUILTIN, LOW);

	start_loop();
}

//传感器测试
void sensor_test()
{

	GA();
	GB();
	GC();
	GD();
	GE();
	GF();
	GG();
	gray_test();
	Ultrasound();

	// // 输出检测
	// Serial.print(*ligGA);
	// Serial.print("\t");
	// Serial.print(*ligGB);
	// Serial.print("\t");
	// Serial.print(*ligGC);
	// Serial.print("\t");
	// Serial.print(*ligGD);
	// Serial.print("\t");
	// Serial.print(*ligGE);
	// Serial.print("\t");
	// Serial.print(*ligGF);
	// Serial.print("\t");
	// Serial.print(*ligGG);
	// Serial.print("\t");
	// Serial.print(gray_arr_result);
	// Serial.print("\t");
	// Serial.print(sound_distance);
	// Serial.print("\t");

	// //边缘传感器状态检测
	// if ((*ligGA == 0) && (*ligGB == 0) && (*ligGC == 0) && (*ligGD == 0))
	// // if ((*ligGA == 0) && (*ligGB == 0))
	// {
	// 	Serial.print("Nomal");
	// }
	// else
	// {
	// 	Serial.print("Error!");
	// }
}

//灰度传感器测试
void gray_test()
{
	int gray_arr[21] = {};

	for (int n = 0; n < 21; n++)
	{
		Gray1();
		gray_arr[n] = *gray_level1;
	}

	gray_arr_result = quickSort(gray_arr, 0, 20); //中值gray
}

//超声波传感器测试
void ultrasound_test()
{
	int sound_arr[21] = {};

	for (int m = 0; m < 21; m++)
	{
		Ultrasound();
		sound_arr[m] = *sound_level;
	}

	sound_arr_test = quickSort(sound_arr, 0, 20); //中值sound
}

//数学程序设计
//取中值函数
int quickSortPartition(int s[], int l, int r)
{
	//Swap(s[l], s[(l + r) / 2]); //若以中间数为基准，则先将中间的这个数和第一个数交换即可
	int i = l, j = r, x = s[l]; //将最左元素记录到x中
	while (i < j)
	{
		// 从右向左找第一个<x的数
		// 无需考虑下标越界
		while (i < j && s[j] >= x)
			j--;
		if (i < j)
			s[i++] = s[j]; //直接替换掉最左元素（已在x中存有备份）

		// 从左向右找第一个>x的数
		while (i < j && s[i] <= x)
			i++;
		if (i < j)
			//替换掉最右元素(已在最左元素中有备份）
			//最左元素一定被覆盖过，若没有，则表明右侧所有元素都>x，那么算法将终止
			s[j--] = s[i];
	}
	s[i] = x; //i的位置放了x，所以其左侧都小于x，右侧y都大于x
	return i;
}

int quickSort(int s[], int l, int r)
{
	//数组左界<右界才有意义，否则说明都已排好，直接返回即可
	if (l >= r)
	{
		return s[11];
	}

	// 划分，返回基准点位置
	int i = quickSortPartition(s, l, r);

	// 递归处理左右两部分，i处为分界点，不用管i了
	quickSort(s, l, i - 1);
	quickSort(s, i + 1, r);

	return s[11];
}

////用法
//int main()
//{
//    int a[21] = {};
//    quickSort(a, 0, 20);//注意最后一个参数是n-1
//}

//传感器使用函数
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

//光电传感器GA
int GA()
{
	lightnumGA = digitalRead(lightGA);
	ligGA = &lightnumGA;
}

//光电传感器GB
int GB()
{
	lightnumGB = digitalRead(lightGB);
	ligGB = &lightnumGB;
}

//光电传感器GC
int GC()
{
	lightnumGC = digitalRead(lightGC);
	ligGC = &lightnumGC;
}

//光电传感器GD
int GD()
{
	lightnumGD = digitalRead(lightGD);
	ligGD = &lightnumGD;
}

//光电传感器GE
int GE()
{
	lightnumGE = digitalRead(lightGE);
	ligGE = &lightnumGE;
}

//光电传感器GF
int GF()
{
	lightnumGF = digitalRead(lightGF);
	ligGF = &lightnumGF;
}

//光电传感器GG
int GG()
{
	lightnumGG = digitalRead(lightGG);
	ligGG = &lightnumGG;
}

//灰度传感器Gray1
int Gray1()
{
	graynum1 = analogRead(gray1);
	gray_level1 = &graynum1;
	return graynum1;
}

//超声波传感器
int Ultrasound()
{
	//向引脚发送10us的高电平
	digitalWrite(trig, LOW);
	delayMicroseconds(2);
	digitalWrite(trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig, LOW);

	//测算距离
	sound_distance = (pulseIn(echo, HIGH) / 58.00);
	sound_level = &sound_distance;
	return sound_distance;
}
