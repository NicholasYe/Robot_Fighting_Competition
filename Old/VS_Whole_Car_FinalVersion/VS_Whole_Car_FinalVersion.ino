/*
 Name:		VS_Whole_Car_FinalVersion.ino
 Created:	2021/3/22 19:23:40
 Author:	NicholasYe
*/

#include <math.h>

const int negLF = 3;//左前负极
const int posLF = 4;//左前正极
const int negRF = 5;//右前负极
const int posRF = 6;//右前正极

const int negLB = 9;//左后负极
const int posLB = 10;//左后正极
const int negRB = 11;//右后负极
const int posRB = 12;//右后正极

const int lightGA = 22;//光电传感器GA（左前）
int lightnumGA;//光电传感器GA返回数值
int* ligGA = NULL;//存储光电传感器数值lightnumGA的指针

const int lightGB = 18;//光电传感器GB（右前）
int lightnumGB;
int* ligGB = NULL;

const int lightGC = 21;//光电传感器GC（左后）
int lightnumGC;
int* ligGC = NULL;

const int lightGD = 33;//光电传感器GD（右后）
int lightnumGD;
int* ligGD = NULL;

const int lightGE = 45;//光电传感器GE（前）
int lightnumGE;
int* ligGE = NULL;

const int lightGF = 45;//光电传感器GF（后）
int lightnumGF;
int* ligGF = NULL;

const int lightGG = 45;//光电传感器GG（左）
int lightnumGG;
int* ligGG = NULL;

const int lightGH = 45;//光电传感器GH（右）
int lightnumGH;
int* ligGH = NULL;

const int gray1 = A1;//灰度传感器GR1
int graynum1;//灰度传感器返回数值
int* gray_level1 = NULL;//存储灰度传感器数值graynum的指针
int gray_arrtest_result = 0;//存贮gray快排后的中值

int Timer = 0;//追敌跳出计时器

boolean on_stage = false;

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600);//打开接口9600
	Serial.println("Senesor:");

	pinMode(negLF, OUTPUT);//引脚3
	pinMode(posLF, OUTPUT);//引脚4
	pinMode(negRF, OUTPUT);//引脚5
	pinMode(posRF, OUTPUT);//引脚6

	pinMode(negLB, OUTPUT);//引脚9
	pinMode(posLB, OUTPUT);//引脚10
	pinMode(negRB, OUTPUT);//引脚11
	pinMode(posRB, OUTPUT);//引脚12

	pinMode(lightGA, INPUT);//光电传感器GA
	digitalWrite(lightGA, LOW);

	pinMode(lightGB, INPUT);//光电传感器GB
	digitalWrite(lightGB, LOW);

	pinMode(lightGC, INPUT);//光电传感器GC
	digitalWrite(lightGC, LOW);

	pinMode(lightGD, INPUT);//光电传感器GD
	digitalWrite(lightGD, LOW);

	pinMode(lightGE, INPUT);//光电传感器GE
	digitalWrite(lightGE, LOW);

	pinMode(lightGF, INPUT);//光电传感器GF
	digitalWrite(lightGF, LOW);

	pinMode(lightGG, INPUT);//光电传感器GG
	digitalWrite(lightGG, LOW);

	pinMode(lightGH, INPUT);//光电传感器GH
	digitalWrite(lightGH, LOW);

	pinMode(gray1, INPUT);//灰度传感器GR1

	pinMode(LED_BUILTIN, OUTPUT);//LED闪烁 

	//点亮小灯函数
	//digitalWrite(LED_BUILTIN, HIGH);

	//闪烁指示
	digitalWrite(LED_BUILTIN, HIGH);
	delay(25);
	digitalWrite(LED_BUILTIN, LOW);
	delay(25);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(25);
	digitalWrite(LED_BUILTIN, LOW);
	delay(25);
}

// the loop function runs over and over again until power down or reset

//循环检测是否启动小车
void loop()
{
	light_test();

	//正式开始并跳入循环
	if (*ligGG == 0)//车尾光电传感器检测
	{
		start_setup();
	}
}

void start_setup()//单次程序
{
	//单次程序
	back();
	delay();//上台
	rotate_counterclockwise();
	delay();//旋转135
	forward();
	delay();//走到中间

	//循环程序
	if (1)
	{
		start_loop();
	}
}

//循环程序
void start_loop()
{
	on_stage_test();//位置检测

	switch (on_stage)//选择程序
	{
	case false:
	{	attack_mode();
	break;
	}

	case true:
	{	return_stage();
	break;
	}
	}
}


//逻辑程序设计

//台上台下检测
void on_stage_test()
{
	gray_test();

	if (*gray_level1 < 600)					//数值待更改
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
	light_test();
	forward();

	if (*ligGA == 0)
	{
		rotate_clockwise();
		delay();//旋转90
		goto Reset;
	}
	else if (*ligGB == 0)
	{
		rotate_counterclockwise();
		delay();//旋转90
		goto Reset;
	}
	else if (*ligGC == 0)
	{
		rotate_counterclockwise();
		delay();//旋转30
		forward();
		delay(1000);//前进1s
		rotate_clockwise();
		delay();//旋转45
		goto Reset;
	}
	else if (*ligGD == 0)
	{
		rotate_clockwise();
		delay();//旋转30
		forward();
		delay(1000);//前进1s
		rotate_counterclockwise();
		delay();//旋转45
		goto Reset;
	}

	//追敌部分
	//do...while写法
	else if (*ligGE == 0)//前面检测到车子
	{
		forward();
		delay();//延时2s
	}
	else if (*ligGF == 0)//左边检测到车子
	{
		Timer = 0;
		do {
			rotate_counterclockwise();
			light_test();
			Timer++;
		} while ((*ligGE == 0) || (Timer < 2000));
		goto Reset;
	}
	else if (*ligGG == 0)//右边检测到车子
	{
		Timer = 0;
		do {
			rotate_clockwise();
			light_test();
			Timer++;
		} while ((*ligGE == 0) || (Timer < 2000));
		goto Reset;
	}
	else if (*ligGH == 0)//后面检测到车子
	{
		Timer = 0;
		do {
			rotate_clockwise();
			light_test();
			Timer++;
		} while ((*ligGE == 0) || (Timer < 2000));
		goto Reset;
	}

Reset:
	analogWrite(LED_BUILTIN, HIGH);
	delay(10);
	analogWrite(LED_BUILTIN, LOW);
}

//台下返回程序
void return_stage()
{
	light_test();

	if (*ligGE == 0)//前面靠墙
	{
		back();
		delay();//背靠上台
		goto Return_Reset;
	}
	else if (*ligGF == 0)//左侧靠墙
	{
		rotate_clockwise();
		delay();//旋转90
		forward();
		delay();//直行上台
		goto Return_Reset;
	}
	else if (*ligGG == 0)//右侧靠墙
	{
		rotate_counterclockwise();
		delay();//旋转90
		forward();
		delay();//直行上台
		goto Return_Reset;
	}
	else if (*ligGH == 0);//反面靠墙
	{
		forward();
		delay();//直行上台
		goto Return_Reset;
	}

Return_Reset:
	analogWrite(LED_BUILTIN, HIGH);
	delay(200);
	analogWrite(LED_BUILTIN, LOW);
	delay(200);
}

//光电传感器全测
void light_test()
{
	GA();
	GB();
	GC();
	GD();
	GE();
	GF();
	GG();
	GH();

	////输出检测
	//Serial.print(*ligGA);
	//Serial.print("\t");
	//Serial.print(*ligGB);
	//Serial.print("\t");
	//Serial.print(*ligGC);
	//Serial.print("\t");
	//Serial.print(*ligGD);
	//Serial.print("\t");
	//Serial.print(*ligGE);
	//Serial.print("\t");
	//Serial.print(*ligGF);
	//Serial.print("\t");
	//Serial.print(*ligGG);
	//Serial.print("\t");
	//Serial.print(*ligGH);
	//Serial.print("\t");
	//Serial.println();

	////边缘传感器状态检测
	//if ((*ligGA == 0) && (*ligGB == 0) && (*ligGC == 0) && (*ligGD == 0))
	//{
	//	Serial.print("Nomal");
	//	Serial.println();
	//}
	//else
	//{
	//	Serial.print("Error!");
	//	Serial.println();
	//}
}

//灰度传感器测试
void gray_test()
{
	int gray_arr[21] = {};

	for (int n = 0; n < 21; n++)
	{
		gray_test();
		gray_arr[n] = *gray_level1;
	}

	gray_arrtest_result = quickSort(gray_arr, 0, 20);//中值gray
}

//数学程序设计

//取中值函数
int quickSortPartition(int s[], int l, int r) {
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
	s[i] = x;  //i的位置放了x，所以其左侧都小于x，右侧y都大于x
	return i;
}

int quickSort(int s[], int l, int r)
{
	//数组左界<右界才有意义，否则说明都已排好，直接返回即可
	if (l >= r) {
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
void forward()
{
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
void back()
{
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
void brake()
{
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
void right()
{
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
void left()
{
	digitalWrite(posLF, LOW);//左前向
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, HIGH);//右前向
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW);//左后向
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, HIGH);//右后向
	digitalWrite(negRB, LOW);
}

//顺时针旋转
void rotate_clockwise()
{
	digitalWrite(posLF, HIGH);//左前向前
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, HIGH);//右前向后
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW);//左后向前
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, LOW);//右后向后
	digitalWrite(negRB, HIGH);
}

//逆时针旋转
void rotate_counterclockwise()
{
	digitalWrite(posLF, LOW);//左前向
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, LOW);//右前向
	digitalWrite(negRF, HIGH);
	digitalWrite(posLB, HIGH);//左后向
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, HIGH);//右后向
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

//光电传感器GH
int GH()
{
	lightnumGH = digitalRead(lightGH);
	ligGH = &lightnumGH;
}

//灰度传感器Gray1
int Gray1()
{
	graynum1 = analogRead(0);
	gray_level1 = &graynum1;
	return graynum1;
}