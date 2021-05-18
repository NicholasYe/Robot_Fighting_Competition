/*
 Name:		VS_Whole_Car_FinalVersion.ino
 Created:	2021/3/22 19:23:40
 Author:	NicholasYe
*/

#include <math.h>

const int negLF = 3;//��ǰ����
const int posLF = 4;//��ǰ����
const int negRF = 5;//��ǰ����
const int posRF = 6;//��ǰ����

const int negLB = 9;//��󸺼�
const int posLB = 10;//�������
const int negRB = 11;//�Һ󸺼�
const int posRB = 12;//�Һ�����

const int lightGA = 22;//��紫����GA����ǰ��
int lightnumGA;//��紫����GA������ֵ
int* ligGA = NULL;//�洢��紫������ֵlightnumGA��ָ��

const int lightGB = 18;//��紫����GB����ǰ��
int lightnumGB;
int* ligGB = NULL;

const int lightGC = 21;//��紫����GC�����
int lightnumGC;
int* ligGC = NULL;

const int lightGD = 33;//��紫����GD���Һ�
int lightnumGD;
int* ligGD = NULL;

const int lightGE = 45;//��紫����GE��ǰ��
int lightnumGE;
int* ligGE = NULL;

const int lightGF = 45;//��紫����GF����
int lightnumGF;
int* ligGF = NULL;

const int lightGG = 45;//��紫����GG����
int lightnumGG;
int* ligGG = NULL;

const int lightGH = 45;//��紫����GH���ң�
int lightnumGH;
int* ligGH = NULL;

const int gray1 = A1;//�Ҷȴ�����GR1
int graynum1;//�Ҷȴ�����������ֵ
int* gray_level1 = NULL;//�洢�Ҷȴ�������ֵgraynum��ָ��
int gray_arrtest_result = 0;//����gray���ź����ֵ

int Timer = 0;//׷��������ʱ��

boolean on_stage = false;

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600);//�򿪽ӿ�9600
	Serial.println("Senesor:");

	pinMode(negLF, OUTPUT);//����3
	pinMode(posLF, OUTPUT);//����4
	pinMode(negRF, OUTPUT);//����5
	pinMode(posRF, OUTPUT);//����6

	pinMode(negLB, OUTPUT);//����9
	pinMode(posLB, OUTPUT);//����10
	pinMode(negRB, OUTPUT);//����11
	pinMode(posRB, OUTPUT);//����12

	pinMode(lightGA, INPUT);//��紫����GA
	digitalWrite(lightGA, LOW);

	pinMode(lightGB, INPUT);//��紫����GB
	digitalWrite(lightGB, LOW);

	pinMode(lightGC, INPUT);//��紫����GC
	digitalWrite(lightGC, LOW);

	pinMode(lightGD, INPUT);//��紫����GD
	digitalWrite(lightGD, LOW);

	pinMode(lightGE, INPUT);//��紫����GE
	digitalWrite(lightGE, LOW);

	pinMode(lightGF, INPUT);//��紫����GF
	digitalWrite(lightGF, LOW);

	pinMode(lightGG, INPUT);//��紫����GG
	digitalWrite(lightGG, LOW);

	pinMode(lightGH, INPUT);//��紫����GH
	digitalWrite(lightGH, LOW);

	pinMode(gray1, INPUT);//�Ҷȴ�����GR1

	pinMode(LED_BUILTIN, OUTPUT);//LED��˸ 

	//����С�ƺ���
	//digitalWrite(LED_BUILTIN, HIGH);

	//��˸ָʾ
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

//ѭ������Ƿ�����С��
void loop()
{
	light_test();

	//��ʽ��ʼ������ѭ��
	if (*ligGG == 0)//��β��紫�������
	{
		start_setup();
	}
}

void start_setup()//���γ���
{
	//���γ���
	back();
	delay();//��̨
	rotate_counterclockwise();
	delay();//��ת135
	forward();
	delay();//�ߵ��м�

	//ѭ������
	if (1)
	{
		start_loop();
	}
}

//ѭ������
void start_loop()
{
	on_stage_test();//λ�ü��

	switch (on_stage)//ѡ�����
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


//�߼��������

//̨��̨�¼��
void on_stage_test()
{
	gray_test();

	if (*gray_level1 < 600)					//��ֵ������
	{
		on_stage = true;
	}
	else
	{
		on_stage = false;
	}
}

//̨�Ͻ�������
void attack_mode()
{
	light_test();
	forward();

	if (*ligGA == 0)
	{
		rotate_clockwise();
		delay();//��ת90
		goto Reset;
	}
	else if (*ligGB == 0)
	{
		rotate_counterclockwise();
		delay();//��ת90
		goto Reset;
	}
	else if (*ligGC == 0)
	{
		rotate_counterclockwise();
		delay();//��ת30
		forward();
		delay(1000);//ǰ��1s
		rotate_clockwise();
		delay();//��ת45
		goto Reset;
	}
	else if (*ligGD == 0)
	{
		rotate_clockwise();
		delay();//��ת30
		forward();
		delay(1000);//ǰ��1s
		rotate_counterclockwise();
		delay();//��ת45
		goto Reset;
	}

	//׷�в���
	//do...whileд��
	else if (*ligGE == 0)//ǰ���⵽����
	{
		forward();
		delay();//��ʱ2s
	}
	else if (*ligGF == 0)//��߼�⵽����
	{
		Timer = 0;
		do {
			rotate_counterclockwise();
			light_test();
			Timer++;
		} while ((*ligGE == 0) || (Timer < 2000));
		goto Reset;
	}
	else if (*ligGG == 0)//�ұ߼�⵽����
	{
		Timer = 0;
		do {
			rotate_clockwise();
			light_test();
			Timer++;
		} while ((*ligGE == 0) || (Timer < 2000));
		goto Reset;
	}
	else if (*ligGH == 0)//�����⵽����
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

//̨�·��س���
void return_stage()
{
	light_test();

	if (*ligGE == 0)//ǰ�濿ǽ
	{
		back();
		delay();//������̨
		goto Return_Reset;
	}
	else if (*ligGF == 0)//��࿿ǽ
	{
		rotate_clockwise();
		delay();//��ת90
		forward();
		delay();//ֱ����̨
		goto Return_Reset;
	}
	else if (*ligGG == 0)//�Ҳ࿿ǽ
	{
		rotate_counterclockwise();
		delay();//��ת90
		forward();
		delay();//ֱ����̨
		goto Return_Reset;
	}
	else if (*ligGH == 0);//���濿ǽ
	{
		forward();
		delay();//ֱ����̨
		goto Return_Reset;
	}

Return_Reset:
	analogWrite(LED_BUILTIN, HIGH);
	delay(200);
	analogWrite(LED_BUILTIN, LOW);
	delay(200);
}

//��紫����ȫ��
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

	////������
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

	////��Ե������״̬���
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

//�Ҷȴ���������
void gray_test()
{
	int gray_arr[21] = {};

	for (int n = 0; n < 21; n++)
	{
		gray_test();
		gray_arr[n] = *gray_level1;
	}

	gray_arrtest_result = quickSort(gray_arr, 0, 20);//��ֵgray
}

//��ѧ�������

//ȡ��ֵ����
int quickSortPartition(int s[], int l, int r) {
	//Swap(s[l], s[(l + r) / 2]); //�����м���Ϊ��׼�����Ƚ��м��������͵�һ������������
	int i = l, j = r, x = s[l]; //������Ԫ�ؼ�¼��x��
	while (i < j)
	{
		// ���������ҵ�һ��<x����
		// ���迼���±�Խ��
		while (i < j && s[j] >= x)
			j--;
		if (i < j)
			s[i++] = s[j]; //ֱ���滻������Ԫ�أ�����x�д��б��ݣ�

		// ���������ҵ�һ��>x����
		while (i < j && s[i] <= x)
			i++;
		if (i < j)
			//�滻������Ԫ��(��������Ԫ�����б��ݣ�
			//����Ԫ��һ�������ǹ�����û�У�������Ҳ�����Ԫ�ض�>x����ô�㷨����ֹ
			s[j--] = s[i];
	}
	s[i] = x;  //i��λ�÷���x����������඼С��x���Ҳ�y������x
	return i;
}

int quickSort(int s[], int l, int r)
{
	//�������<�ҽ�������壬����˵�������źã�ֱ�ӷ��ؼ���
	if (l >= r) {
		return s[11];
	}

	// ���֣����ػ�׼��λ��
	int i = quickSortPartition(s, l, r);

	// �ݹ鴦�����������֣�i��Ϊ�ֽ�㣬���ù�i��
	quickSort(s, l, i - 1);
	quickSort(s, i + 1, r);

	return s[11];
}

////�÷�
//int main()
//{
//    int a[21] = {};
//    quickSort(a, 0, 20);//ע�����һ��������n-1
//}

//������ʹ�ú���

//ǰ������
void forward()
{
	digitalWrite(posLF, HIGH);//��ǰ��ǰ
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, HIGH);//��ǰ��ǰ
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, HIGH);//�����ǰ
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, HIGH);//�Һ���ǰ
	digitalWrite(negRB, LOW);
}

//���˺���
void back()
{
	digitalWrite(posLF, LOW);//��ǰ���
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, LOW);//��ǰ���
	digitalWrite(negRF, HIGH);
	digitalWrite(posLB, LOW);//������
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, LOW);//�Һ����
	digitalWrite(negRB, HIGH);
}

//ֹͣ����
void brake()
{
	digitalWrite(posLF, LOW);//��ǰͣ
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, LOW);//��ǰͣ
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW);//���ͣ
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, LOW);//�Һ�ͣ
	digitalWrite(negRB, LOW);
}

//��ת
void right()
{
	digitalWrite(posLF, HIGH);//��ǰ��ǰ
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, LOW);//��ǰ���
	digitalWrite(negRF, HIGH);
	digitalWrite(posLB, HIGH);//�����ǰ
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, LOW);//�Һ����
	digitalWrite(negRB, HIGH);
}

//��ת
void left()
{
	digitalWrite(posLF, LOW);//��ǰ��
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, HIGH);//��ǰ��
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW);//�����
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, HIGH);//�Һ���
	digitalWrite(negRB, LOW);
}

//˳ʱ����ת
void rotate_clockwise()
{
	digitalWrite(posLF, HIGH);//��ǰ��ǰ
	digitalWrite(negLF, LOW);
	digitalWrite(posRF, HIGH);//��ǰ���
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW);//�����ǰ
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, LOW);//�Һ����
	digitalWrite(negRB, HIGH);
}

//��ʱ����ת
void rotate_counterclockwise()
{
	digitalWrite(posLF, LOW);//��ǰ��
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, LOW);//��ǰ��
	digitalWrite(negRF, HIGH);
	digitalWrite(posLB, HIGH);//�����
	digitalWrite(negLB, LOW);
	digitalWrite(posRB, HIGH);//�Һ���
	digitalWrite(negRB, LOW);
}

//��紫����GA
int GA()
{
	lightnumGA = digitalRead(lightGA);
	ligGA = &lightnumGA;
}

//��紫����GB
int GB()
{
	lightnumGB = digitalRead(lightGB);
	ligGB = &lightnumGB;
}

//��紫����GC
int GC()
{
	lightnumGC = digitalRead(lightGC);
	ligGC = &lightnumGC;
}

//��紫����GD
int GD()
{
	lightnumGD = digitalRead(lightGD);
	ligGD = &lightnumGD;
}

//��紫����GE
int GE()
{
	lightnumGE = digitalRead(lightGE);
	ligGE = &lightnumGE;
}

//��紫����GF
int GF()
{
	lightnumGF = digitalRead(lightGF);
	ligGF = &lightnumGF;
}

//��紫����GG
int GG()
{
	lightnumGG = digitalRead(lightGG);
	ligGG = &lightnumGG;
}

//��紫����GH
int GH()
{
	lightnumGH = digitalRead(lightGH);
	ligGH = &lightnumGH;
}

//�Ҷȴ�����Gray1
int Gray1()
{
	graynum1 = analogRead(0);
	gray_level1 = &graynum1;
	return graynum1;
}