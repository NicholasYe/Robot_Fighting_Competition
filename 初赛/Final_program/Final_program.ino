/*
 Name:    Final_program.ino
 Created: 2020/12/15 22:55:49
 Author:  NicholasYe
*/

#include <math.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>

const int negLF = 4;//��ǰ����
const int posLF = 5;//��ǰ����
const int negRF = 6;//��ǰ����
const int posRF = 7;//��ǰ����

const int negLB = 8;//��󸺼�
const int posLB = 9;//�������
const int negRB = 10;//�Һ󸺼�
const int posRB = 11;//�Һ�����

const int gray1 = A0;//�Ҷȴ�����GR1������ǰ��
int graynum1;//�Ҷȴ�����������ֵ
int* level1 = NULL;//�洢�Ҷȴ�������ֵgraynum��ָ��

const int gray2 = A1;//�Ҷȴ�����GR2������ǰ)
int graynum2;
int* level2 = NULL;

const int gray3 = A14;//�Ҷȴ�����GR3�������
int graynum3;
int* level3 = NULL;

const int gray4 = A15;//�Ҷȴ�����GR4�����Һ�
int graynum4;
int* level4 = NULL;

const int lightGA = 22;//��紫����GAǰ��
int lightnumGA;//��紫����GA������ֵ
int* ligGA = NULL;//�洢��紫������ֵlightnumGA��ָ��

const int lightGB = 18;//��紫����GB��
int lightnumGB;
int* ligGB = NULL;

const int lightGC = 21;//��紫����GC��
int lightnumGC;
int* ligGC = NULL;

const int lightGD = 33;//��紫����GD��
int lightnumGD;
int* ligGD = NULL;

//const int lightGE = 45;//��紫����GE����
//int lightnumGE;
//int* ligGE = NULL;

const int trigCA = 49;//������������CA(��ǰ)
const int echoCA = 50;
float distanceCA;//A���������ؾ���
float* disCA = NULL;//�洢��������������ֵdistance��ָ��

const int trigCB = 17;//������������CB����ǰ��
const int echoCB = 16;
float distanceCB;
float* disCB = NULL;

Servo myservo_left;  // ����Servo���������ƶ��
int pos_left = 0;    // �Ƕȴ洢����

Servo myservo_right;  // ����Servo���������ƶ��
int pos_right = 0;    // �Ƕȴ洢����

boolean on_stage = false;//�ж�С���Ƿ���̨��
boolean defend = false;//�ж�С���Ƿ���Ҫ����

VL53L1X sensor;//ToF���⴫����
int* tof_feedback = NULL;
int tof_temp;

//�������

//�������ر߽�Ҷ�ֵ
int attack_gray_edge = 500;

//ѭ���Ƚϲ���ֵ
int circle_compare = 25;

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);//�򿪽ӿ�9600
    Serial.println("Senesor:");

    //ToF���⴫����
    //ToF�������ĺ���
    //sensor.read();

    //Serial.begin(115200);//�򿪽ӿ�115200
    Wire.begin();
    Wire.setClock(400000); // use 400 kHz I2C
    sensor.setTimeout(500);
    if (!sensor.init())
    {
        Serial.println("Failed to detect and initialize sensor!");
        while (1);
    }
    // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
    // You can change these settings to adjust the performance of the sensor, but
    // the minimum timing budget is 20 ms for short distance mode and 33 ms for
    // medium and long distance modes. See the VL53L1X datasheet for more
    // information on range and timing limits.

    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(50000);
    // Start continuous readings at a rate of one measurement every 50 ms (the
    // inter-measurement period). This period should be at least as long as the
    // timing budget.
    sensor.startContinuous(50);

    pinMode(negLF, OUTPUT);//����3
    pinMode(posLF, OUTPUT);//����4
    pinMode(negRF, OUTPUT);//����5
    pinMode(posRF, OUTPUT);//����6

    pinMode(negLB, OUTPUT);//����9
    pinMode(posLB, OUTPUT);//����10
    pinMode(negRB, OUTPUT);//����11
    pinMode(posRB, OUTPUT);//����12

    pinMode(gray1, INPUT);//�Ҷȴ�����GR1
    pinMode(gray2, INPUT);//�Ҷȴ�����GR2
    pinMode(gray3, INPUT);//�Ҷȴ�����GR3
    pinMode(gray4, INPUT);//�Ҷȴ�����GR4

    pinMode(lightGA, INPUT);//��紫����GA
    digitalWrite(lightGA, LOW);
    pinMode(lightGB, INPUT);//��紫����GB
    digitalWrite(lightGB, LOW);
    pinMode(lightGC, INPUT);//��紫����GC
    digitalWrite(lightGC, LOW);
    pinMode(lightGD, INPUT);//��紫����GD
    digitalWrite(lightGD, LOW);
    //pinMode(lightGE, INPUT);//��紫����GD
    //digitalWrite(lightGE, LOW);

    pinMode(trigCA, OUTPUT);//������������CA
    pinMode(echoCA, INPUT);
    pinMode(trigCB, OUTPUT);//������������CB
    pinMode(echoCB, INPUT);


    //myservo_left.attach(42);  //�����������������
    //myservo_left.write(180);
    //delay(1800);

    //myservo_right.attach(45);//�����������������
    //myservo_right.write(0);
    //delay(1800);

    pinMode(LED_BUILTIN, OUTPUT);//LED��˸ 

}



void loop()
{


    GA();
    GB();
    GC();
    GD();
    //Serial.print(*ligGA);
    //Serial.print("\t");
    //Serial.print(*ligGB);
    //Serial.print("\t");
    //Serial.print(*ligGC);
    //Serial.print("\t");
    //Serial.print(*ligGD);
    //Serial.print("\t");
    //Serial.println();

   // Gray_all();

    if ((*ligGA == 0) && (*ligGD == 0))
    {
        begin();
    }
}

void begin()
{
    //���ֳ�ʼ��
    back();
    delay(2400);
    rotate_counterclockwise();
    delay(1000);
    forward();
    delay(300);

    while (1)
    {
        return_center();
    }

}

//�Ҷȴ�����һ��ⶨ
int Gray_all()
{
    int gray_void_num1[201] = { 0 };
    int gray_void_num2[201] = { 0 };
    int gray_void_num3[201] = { 0 };
    int gray_void_num4[201] = { 0 };

    for (int m = 0; m < 201; m++)
    {
        gray_void_num1[m] = analogRead(0);
        gray_void_num2[m] = analogRead(1);
        gray_void_num3[m] = analogRead(14);
        gray_void_num4[m] = analogRead(15);
    }

    graynum1 = quickSort(gray_void_num1, 0, 200);
    graynum2 = quickSort(gray_void_num2, 0, 200) + 5;
    graynum3 = quickSort(gray_void_num3, 0, 200) + 55;
    graynum4 = quickSort(gray_void_num4, 0, 200) - 7;

    level1 = &graynum1;
    level2 = &graynum2;
    level3 = &graynum3;
    level4 = &graynum4;




    // �����������
    Serial.print(graynum1);
    Serial.print("\t");
    Serial.print(graynum2);
    Serial.print("\t");
    Serial.print(graynum3);
    Serial.print("\t");
    Serial.print(graynum4);
    Serial.print("\t");
    Serial.println();
}

//�ع����ĺ���
int return_center()
{
    Gray_all();
    GA();
    GB();
    GC();
    GD();
    tof_sensor();


    if ((*level1 > *level3) && (*level2 > *level4) && (*ligGA == 0))
    {
        Serial.print("2");
        Serial.println();
        do
        {
            forward();
            delay(25);
            Gray_all();
        } while ((*level1 < attack_gray_edge) && (*level2 < attack_gray_edge));
        back();
        delay(100);
    }

    else  if (tof_temp > 200)
    {
        do
        {
            forward();
            delay(25);
            tof_sensor();
        } while (tof_temp > 125);
        forward();
        delay(25);
    }

    //������࿿����
    else  if ((*level1 > *level2) && (*level3 > *level4))
    { 
        Serial.print("4");
        Serial.println();
        rotate_counterclockwise();
        delay(640);
        do
        {
            forward();
            delay(25);
            Gray_all();
        } while ((*level1 > *level3) && (*level2 > *level4));
        forward();
        delay(25);
    }

    //�����Ҳ࿿����
    else if ((*level1 < *level2) && (*level3 < *level4))
    {
        Serial.print("5");
        Serial.println();
        rotate_clockwise();
        delay(640);
        do
        {
            forward();
            delay(25);
            Gray_all();
        } while ((*level1 > *level3) && (*level2 > *level4));
        forward();
        delay(25);
    }

    //������������
    else if ((*level1 > *level3) && (*level2 > *level4))
    {
        Serial.print("1");
        Serial.println();
        do
        {
            forward();
            delay(25);
            Gray_all();
        } while ((*level1 > *level3) && (*level2 > *level4));
        forward();
        delay(25);
    }



    ////�������Ͽ���
    //else if ((*level1 > *level4) && (abs(*level2 - *level3) < 25))
    //{
    //    Serial.print("6");
    //    Serial.println();
    //    rotate_counterclockwise();
    //    delay(320);
    //    do
    //    {
    //        forward();
    //        Gray_all();
    //    } while ((*level1 > *level3) && (*level2 > *level4));
    //    forward();
    //    delay(50);
    //}
    ////�������Ͽ���
    //else if ((*level2 > *level3) && (abs(*level1 - *level4) < 25))
    //{
    //    Serial.print("7");
    //    Serial.println();
    //    rotate_clockwise();
    //    delay(320);
    //    do
    //    {
    //        forward();
    //        Gray_all();
    //    } while ((*level1 > *level3) && (*level2 > *level4));
    //    forward();
    //    delay(50);
    //}
    ////�������¿���
    //else if ((*level3 > *level2) && (abs(*level1 - *level4) < 25))
    //{
    //    rotate_clockwise();
    //    delay(320);
    //    do
    //    {
    //        back();
    //        Gray_all();
    //    } while ((*level1 < *level3) && (*level2 < *level4));
    //    back();
    //    delay(50);
    //}
    ////�������¿���
    //else if ((*level1 < *level4) && (abs(*level2 - *level3) < 25))
    //{
    //    Serial.print("8");
    //    Serial.println();
    //    rotate_counterclockwise();
    //    delay(320);
    //    do
    //    {
    //        back();
    //        Gray_all();
    //    } while ((*level1 < *level3) && (*level2 < *level4));
    //    back();
    //    delay(50);
    //}
}
























//��ѧ����

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
        return s[100];
    }

    // ���֣����ػ�׼��λ��
    int i = quickSortPartition(s, l, r);

    // �ݹ鴦�����������֣�i��Ϊ�ֽ�㣬���ù�i��
    quickSort(s, l, i - 1);
    quickSort(s, i + 1, r);

    return s[100];
}
































//�����ҶȺ���
int gray_retest()
{
    Gray_all();

    //����������λ��
    int median1 = *level1;
    int median2 = *level2;
    int median3 = *level3;
    int median4 = *level4;


    // �����������
    Serial.print(median1);
    Serial.print("\t");
    Serial.print(median2);
    Serial.print("\t");
    Serial.print(median3);
    Serial.print("\t");
    Serial.print(median4);
    Serial.print("\t");
    Serial.print(on_stage);
    Serial.println();
}


//������̨
int back_stage()
{
    GA();
    GB();
    GC();
    GD();

    Serial.print(*ligGA);
    Serial.print("\t");
    Serial.print(*ligGB);
    Serial.print("\t");
    Serial.print(*ligGC);
    Serial.print("\t");
    Serial.print(*ligGD);
    Serial.print("\t");
    Serial.println();

    if (*ligGD == 0)//��������̨
    {
        forward();
        delay(1000);
    }
    else if (*ligGA == 0)//��������̨
    {
        back();
        delay(1000);
    }
    else if (*ligGB == 0)//���ұ߿���̨
    {
        rotate_clockwise();
        delay(620);
        forward();
        delay(1000);
    }
    else if (*ligGC == 0)//����߿���̨
    {
        rotate_counterclockwise();
        delay(620);
        forward();
        delay(1000);
    }
}

//�ж��Ƿ�����̨
void judge_stage()
{
    Gray_all();

    //����������λ��
    int median1 = *level1;
    int median2 = *level2;
    int median3 = *level3;
    int median4 = *level4;

    //// �����������
    // Serial.print(median1);
    // Serial.print("\t");
    // Serial.print(median2);
    // Serial.print("\t");
    // Serial.print(median3);
    // Serial.print("\t");
    // Serial.print(median4);
    // Serial.print("\t");
    // Serial.print(on_stage);
    // Serial.println();

     //ѭ���Ƚ�
    if ((abs(median1 - median2) < circle_compare) && (abs(median2 - median3) < circle_compare) && (abs(median3 - median1) < circle_compare))
    {
        on_stage = true;
    }
    else if ((abs(median1 - median2) < circle_compare) && (abs(median2 - median4) < circle_compare) && (abs(median4 - median1) < circle_compare))
    {
        on_stage = true;
    }
    else if ((abs(median2 - median3) < circle_compare) && (abs(median3 - median4) < circle_compare) && (abs(median4 - median2) < circle_compare))
    {
        on_stage = true;
    }
    else if ((abs(median1 - median3) < circle_compare) && (abs(median3 - median4) < circle_compare) && (abs(median4 - median1) < circle_compare))
    {
        on_stage = true;
    }
    else
    {
        on_stage = false;
    }
}

//����С������
int attack_car()
{
    //���չ��
    change_servo_angle();

    //�����Է�С��
    do
    {
        //�����Է�С������
        do
        {
            rotate_clockwise();
            tof_sensor();
        } while ((*tof_feedback > 90));
        brake();

        forward();
        CA();
        CB();
        Gray_all();
    } while ((*level1 > attack_gray_edge) && (*level2 > attack_gray_edge) && (*level3 > attack_gray_edge) && (*level4 > attack_gray_edge));

    //�������
    back_servo_angle();
}

//int fully_attack()
//{
//    //���չ��
//    change_servo_angle();
//     
//    Gray_all();
//    if (on_stage == false);
//    {
//        goto gg;
//    }
//
//    //���¹���
//    restart:
//    //������������
//    if ((*level1 > *level3) && (*level2 > *level4))
//    {
//        do
//        {
//            forward();
//            Gray_all();
//        } while ((*level1 > *level3) && (*level2 > *level4));
//        forward();
//        delay(50);
//    }
//    //���ӱ�������
//    else if ((*level1 < *level3) && (*level2 < *level4))
//    {
//        do
//        {
//            back();
//            Gray_all();
//        } while ((*level1 < *level3) && (*level2 < *level4));
//        back();
//        delay(50);
//    }
//    //������࿿����
//    else if ((*level1 > *level2) && (*level3 > *level4))
//    {
//        rotate_counterclockwise_90();
//        do
//        {
//            forward();
//            Gray_all();
//        } while ((*level1 > *level3) && (*level2 > *level4));
//        forward();
//        delay(50);
//    }
//    //�����Ҳ࿿����
//    else if ((*level1 < *level2) && (*level3 < *level4))
//    {
//        rotate_clockwise_90();
//        do
//        {
//            forward();
//            Gray_all();
//        } while ((*level1 > *level3) && (*level2 > *level4));
//        forward();
//        delay(50);
//    }
//    //�������Ͽ���
//    else if ((*level1 > *level4) && (abs(*level2 - *level3) < 25))
//    {
//        rotate_counterclockwise_45();
//        do
//        {
//            forward();
//            Gray_all();
//        } while ((*level1 > *level3) && (*level2 > *level4));
//        forward();
//        delay(50);
//    }
//    //�������Ͽ���
//    else if ((*level2 > *level3) && (abs(*level1 - *level4) < 25))
//    {
//        rotate_clockwise_45();
//        do
//        {
//            forward();
//            Gray_all();
//        } while ((*level1 > *level3) && (*level2 > *level4));
//        forward();
//        delay(50);
//    }
//    //�������¿���
//    else if ((*level3 > *level2) && (abs(*level1 - *level4) < 25))
//    {
//        rotate_clockwise_45();
//        do
//        {
//            back();
//            Gray_all();
//        } while ((*level1 < *level3) && (*level2 < *level4));
//        back();
//        delay(50);
//    }
//    //�������¿���
//    else if ((*level1 < *level4) && (abs(*level2 - *level3) < 25))
//    {
//        rotate_counterclockwise_45();
//        rotate_clockwise_45();
//        do
//        {
//            back();
//            Gray_all();
//        } while ((*level1 < *level3) && (*level2 < *level4));
//        back();
//        delay(50);
//    }
//
//    Gray_all();
//    if (on_stage == false);
//    {
//        goto gg;
//    }
//
//    //�����Է�С��
//    do
//    {
//        //�����Է�С������
//        do
//        {
//            tof_sensor();
//            rotate_clockwise();
//            delay(40);
//        } while ((*tof_feedback > 90));
//
//        forward();
//        CA();
//        CB();
//        Gray_all();
//    } while ((*level1 > attack_gray_edge) && (*level2 > attack_gray_edge) && (*level3 > attack_gray_edge) && (*level4 > attack_gray_edge));
//
//    Gray_all();
//    if (on_stage == false);
//    {
//        goto gg;
//    }
//    if (on_stage == true);
//    {
//        goto restart;
//    }
//
//    //�������
//    back_servo_angle();
//
//    //������ת  
//gg:
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(100);
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(100);
//
//}



////�÷�
//int main()
//{
//    int a[21] = {};
//    quickSort(a, 0, 20);//ע�����һ��������n-1
//}






//�����С���ƶ�����

//ǰ������
int forward()
{
    digitalWrite(posLF, HIGH);//��ǰ��ǰ
    digitalWrite(negLF, LOW);
    digitalWrite(posRF, LOW);//��ǰ��ǰ
    digitalWrite(negRF, HIGH);
    digitalWrite(posLB, LOW);//�����ǰ
    digitalWrite(negLB, HIGH);
    digitalWrite(posRB, HIGH);//�Һ���ǰ
    digitalWrite(negRB, LOW);
}

//���˺���
int back()
{
    digitalWrite(posLF, LOW);//��ǰ��ǰ
    digitalWrite(negLF, HIGH);
    digitalWrite(posRF, HIGH);//��ǰ��ǰ
    digitalWrite(negRF, LOW);
    digitalWrite(posLB, HIGH);//�����ǰ
    digitalWrite(negLB, LOW);
    digitalWrite(posRB, LOW);//�Һ���ǰ
    digitalWrite(negRB, HIGH);
}

//ֹͣ����
int brake()
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

//˳ʱ����ת��600ms��

//˳ʱ����ת
int rotate_clockwise()
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
int rotate_counterclockwise()
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

//��ת
int left()
{
    digitalWrite(posLF, LOW);//��ǰ��
    digitalWrite(negLF, LOW);
    digitalWrite(posRF, LOW);//��ǰ��
    digitalWrite(negRF, HIGH);
    digitalWrite(posLB, LOW);//�����
    digitalWrite(negLB, LOW);
    digitalWrite(posRB, HIGH);//�Һ���
    digitalWrite(negRB, LOW);
}

//��ת
int right()
{
    digitalWrite(posLF, HIGH);//��ǰ��
    digitalWrite(negLF, LOW);
    digitalWrite(posRF, LOW);//��ǰ��
    digitalWrite(negRF, LOW);
    digitalWrite(posLB, LOW);//�����
    digitalWrite(negLB, HIGH);
    digitalWrite(posRB, LOW);//�Һ���
    digitalWrite(negRB, LOW);
}


//�Ķ��ӿ�ʱע��Ķ�������analogRead();



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

////��紫����GE
//int GE()
//{
//    lightnumGE = digitalRead(lightGE);
//    ligGE = &lightnumGE;
//}

//���������CA
int CA()
{
    digitalWrite(trigCA, LOW);
    delayMicroseconds(2);
    digitalWrite(trigCA, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigCA, LOW);
    distanceCA = (pulseIn(echoCA, HIGH) / 58.00);
    disCA = &distanceCA;
}

//���������CB
int CB()
{
    digitalWrite(trigCB, LOW);
    delayMicroseconds(2);
    digitalWrite(trigCB, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigCB, LOW);
    distanceCB = (pulseIn(echoCB, HIGH) / 58.00);
    disCB = &distanceCB;
}

//���⴫����
int tof_sensor()
{
    tof_temp = (sensor.read() / 10);
    tof_feedback = &tof_temp;
}
//int tof_sensor()
//{
//    int tof_distance = sensor.read();
//    tof_feedback = &tof_distance;
//}

//�����תչ������
int change_servo_angle()
{
    for (int i = 0; i < 180; i++)
    {
        myservo_left.write(180 - i);
        myservo_right.write(i);
        delay(10);
    }
}

//�����ת�ջغ���
int back_servo_angle()
{
    for (int i = 0; i < 180; i++)
    {
        myservo_left.write(i);
        myservo_right.write(180 - i);
        delay(10);
    }
}



// //the loop function runs over and over again until power down or reset
//void loop()
//{
//    judge_stage();
//    switch (on_stage)
//    {
//    case true://̨�Ͻ���
//        do
//        {
//            fully_attack();
//        } while (on_stage == true);
//        break;
//
//    case false://̨�·���
//        do
//        {
//            back_stage();
//        } while(on_stage == false);
//        break;
//    }
//}


//
//Wire.begin();
//Wire.setClock(400000); // use 400 kHz I2C
//sensor.setTimeout(500);
//if (!sensor.init())
//{
//    Serial.println("Failed to detect and initialize sensor!");
//    while (1);
//}

