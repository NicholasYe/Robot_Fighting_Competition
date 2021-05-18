/*
 Name:		Final_version.ino
 Created:	2021/3/24 14:10:21
 Author:	NicholasYe
*/

#include <math.h>

const int lightGA = 31; //光电传感器GA（左前）
int lightnumGA;		  //光电传感器GA返回数值
int *ligGA = NULL;	  //存储光电传感器数值lightnumGA的指针

const int lightGB = 33; //光电传感器GB（右前）
int lightnumGB;
int *ligGB = NULL;

const int lightGC = 30; //光电传感器GC（左后）
int lightnumGC;
int *ligGC = NULL;

const int lightGD = 32; //光电传感器GD（右后）
int lightnumGD;
int *ligGD = NULL;

const int lightGE = 29; //光电传感器GG（左）
int lightnumGE;
int *ligGE = NULL;

const int lightGF = 37; //光电传感器GH（右）
int lightnumGF;
int *ligGF = NULL;

const int gray1 = A8;		 //灰度传感器GR1
int graynum1;			 //灰度传感器返回数值
int *gray_level1 = NULL; //存储灰度传感器数值graynum的指针
int gray_arrtest_result; //存贮gray快排后的中值

int Timer = 0; //追敌跳出计时器

boolean on_stage = false; //台上台下判定

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600); //打开接口9600
	Serial.println("Hello World:");

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

	pinMode(gray1, INPUT); //灰度传感器GR1

	pinMode(LED_BUILTIN, OUTPUT); //LED闪烁

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

void loop()
{
	sensor_test();
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
	gray_test();

	//输出检测
	Serial.print(*ligGA);
	Serial.print("\t");
	Serial.print(*ligGB);
	Serial.print("\t");
	Serial.print(*ligGC);
	Serial.print("\t");
	Serial.print(*ligGD);
	Serial.print("\t");
	Serial.print(*ligGE);
	Serial.print("\t");
	Serial.print(*ligGF);
	Serial.print("\t");
	Serial.print(gray_arrtest_result);
	Serial.println();

	// //边缘传感器状态检测
	// if ((*ligGA == 0) && (*ligGB == 0) && (*ligGC == 0) && (*ligGD == 0))
	// {
	// 	Serial.print("Nomal");
	// 	Serial.println();
	// }
	// else
	// {
	// 	Serial.print("Error!");
	// 	Serial.println();
	// }

  delay(500);
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

	gray_arrtest_result = quickSort(gray_arr, 0, 20); //中值gray
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

//灰度传感器Gray1
int Gray1()
{
	graynum1 = analogRead(8);
	gray_level1 = &graynum1;
	return graynum1;
}
