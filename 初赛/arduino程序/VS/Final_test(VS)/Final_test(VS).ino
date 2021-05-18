/*
 Name:		Final_test_VS_.ino
 Created:	2020/11/29 20:37:18
 Author:	NicholasYe
*/

const int negLF = 3;//��ǰ����
const int posLF = 4;//��ǰ����
const int negRF = 5;//��ǰ����
const int posRF = 6;//��ǰ����
int pwmLF = 7;//��ǰ��pwm
int pwmRF = 8;//��ǰ��pwm

const int negLB = 9;//��󸺼�
const int posLB = 10;//�������
const int negRB = 11;//�Һ󸺼�
const int posRB = 12;//�Һ�����
int pwmLB = 13;//�����pwm
int pwmRB = 14;//�Һ���pwm

const int trigCA = 15;//������������CA
const int echoCA = 16;
float distanceCA;//A���������ؾ���

const int trigCB = 17;//������������CB
const int echoCB = 18;
float distanceCB;//B���������ؾ���

const int trigCC = 23;//������������CC
const int echoCC = 24;
float distanceCC;//C���������ؾ���

const int trigCD = 25;//������������CD
const int echoCD = 26;
float distanceCD;//D���������ؾ���

const int lightGA = 19;//��紫����GA
int lightnumGA;//��紫����GA������ֵ

const int lightGB = 20;//��紫����GB
int lightnumGB;//��紫����GB������ֵ

const int lightGC = 21;//��紫����GC
int lightnumGC;//��紫����GC������ֵ

const int lightGD = 22;//��紫����GD
int lightnumGD;//��紫����GD������ֵ

const int gray1 = A1;//�Ҷȴ�����GR1
int graynum1;//�Ҷȴ�����������ֵ

boolean on_stage = false;
boolean car_detect = false;

//���ó�ֵ
void setup()
{
	Serial.begin(9600);
	Serial.println("Senesor:");
	pinMode(negLF, OUTPUT);//����3
	pinMode(posLF, OUTPUT);//����4
	pinMode(negRF, OUTPUT);//����5
	pinMode(posRF, OUTPUT);//����6
	pinMode(pwmLF, OUTPUT);//����7
	pinMode(pwmRF, OUTPUT);//����8

	pinMode(negLB, OUTPUT);//����9
	pinMode(posLB, OUTPUT);//����10
	pinMode(negRB, OUTPUT);//����11
	pinMode(posRB, OUTPUT);//����12
	pinMode(pwmLB, OUTPUT);//����13
	pinMode(pwmRB, OUTPUT);//����14

	pinMode(trigCA, OUTPUT);//������������CA
	pinMode(echoCA, INPUT);

	pinMode(trigCB, OUTPUT);//������������CB
	pinMode(echoCB, INPUT);

	pinMode(trigCC, OUTPUT);//������������CC
	pinMode(echoCC, INPUT);

	pinMode(trigCD, OUTPUT);//������������CD
	pinMode(echoCD, INPUT);

	pinMode(lightGA, INPUT);//��紫����GA
	digitalWrite(lightGA, LOW);

	pinMode(lightGB, INPUT);//��紫����GB
	digitalWrite(lightGB, LOW);

	pinMode(lightGC, INPUT);//��紫����GC
	digitalWrite(lightGC, LOW);

	pinMode(lightGD, INPUT);//��紫����GD
	digitalWrite(lightGD, LOW);

	pinMode(gray1, INPUT);//�Ҷȴ�����GR1

	pinMode(LED_BUILTIN, OUTPUT);//LED��˸ 
}


//��ѭ��
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

//�ж��Ƿ�����̨
void judge_stage()
{

}

//������̨
void back_stage()
{

}

//�����Է�С��
void detect_car()
{

}

//ײ��С��
void attact()
{

}

//������ת
void defence()
{

}







































//ǰ������
void forward(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed);//��ǰpwm
	analogWrite(pwmRF, RFmotorSpeed);//��ǰpwm
	analogWrite(pwmLB, LBmotorSpeed);//���pwm
	analogWrite(pwmRB, RBmotorSpeed);//�Һ�pwm
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
void back(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed);//��ǰpwm
	analogWrite(pwmRF, RFmotorSpeed);//��ǰpwm
	analogWrite(pwmLB, LBmotorSpeed);//���pwm
	analogWrite(pwmRB, RBmotorSpeed);//�Һ�pwm
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
void brake(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed);//��ǰpwm
	analogWrite(pwmRF, RFmotorSpeed);//��ǰpwm
	analogWrite(pwmLB, LBmotorSpeed);//���pwm
	analogWrite(pwmRB, RBmotorSpeed);//�Һ�pwm
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
void right(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed);//��ǰpwm
	analogWrite(pwmRF, RFmotorSpeed);//��ǰpwm
	analogWrite(pwmLB, LBmotorSpeed);//���pwm
	analogWrite(pwmRB, RBmotorSpeed);//�Һ�pwm
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
void left(unsigned short LFmotorSpeed, unsigned short RFmotorSpeed, unsigned short LBmotorSpeed, unsigned short RBmotorSpeed)
{
	analogWrite(pwmLF, LFmotorSpeed);//��ǰpwm
	analogWrite(pwmRF, RFmotorSpeed);//��ǰpwm
	analogWrite(pwmLB, LBmotorSpeed);//���pwm
	analogWrite(pwmRB, RBmotorSpeed);//�Һ�pwm
	digitalWrite(posLF, LOW);//��ǰ��
	digitalWrite(negLF, HIGH);
	digitalWrite(posRF, HIGH);//��ǰ��
	digitalWrite(negRF, LOW);
	digitalWrite(posLB, LOW);//�����
	digitalWrite(negLB, HIGH);
	digitalWrite(posRB, HIGH);//�Һ���
	digitalWrite(negRB, LOW);
}

//���������CA
int CA()
{
	digitalWrite(trigCA, LOW);
	digitalWrite(trigCA, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigCA, LOW);
	distanceCA = (pulseIn(echoCA, HIGH) / 58.00);
	return distanceCA;
}

//���������CB
int CB()
{
	digitalWrite(trigCB, LOW);
	digitalWrite(trigCB, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigCB, LOW);
	distanceCB = (pulseIn(echoCB, HIGH) / 58.00);
	return distanceCB;
}

//���������CC
int CC()
{
	digitalWrite(trigCC, LOW);
	digitalWrite(trigCC, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigCC, LOW);
	distanceCC = (pulseIn(echoCC, HIGH) / 58.00);
	return distanceCC;
}

//���������CD
int CD()
{
	digitalWrite(trigCD, LOW);
	digitalWrite(trigCD, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigCD, LOW);
	distanceCD = (pulseIn(echoCD, HIGH) / 58.00);
	return distanceCD;
}

//��紫����GA
int GA()
{
	int valueA = 0;
	lightnumGA = digitalRead(lightGA);
	valueA = lightnumGA;
	return valueA;
}

//��紫����GB
int GB()
{
	int valueB = 0;
	lightnumGB = digitalRead(lightGB);
	valueB = lightnumGB;
	return valueB;
}

//��紫����GC
int GC()
{
	int valueC = 0;
	lightnumGC = digitalRead(lightGC);
	valueC = lightnumGC;
	return valueC;
}

//��紫����GD
int GD()
{
	int valueD = 0;
	lightnumGD = digitalRead(lightGD);
	valueD = lightnumGD;
	return valueD;
}

//�Ҷȴ�����Gray1
int Gray1()
{
	int level1 = 0;
	graynum1 = analogRead(1);
	level1 = graynum1;
	return level1;
}
