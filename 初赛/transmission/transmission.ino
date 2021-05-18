/*
 Name:    Final_program.ino
 Created: 2020/12/15 22:55:49
 Author:  NicholasYe
*/

#include <math.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>

const int negLF = 4;//左前负极
const int posLF = 5;//左前正极
const int negRF = 6;//右前负极
const int posRF = 7;//右前正极

const int negLB = 8;//左后负极
const int posLB = 9;//左后正极
const int negRB = 10;//右后负极
const int posRB = 11;//右后正极

const int gray1 = A0;//灰度传感器GR1（车左前）
int graynum1;//灰度传感器返回数值
int* level1 = NULL;//存储灰度传感器数值graynum的指针

const int gray2 = A1;//灰度传感器GR2（车右前)
int graynum2;
int* level2 = NULL;

const int gray3 = A14;//灰度传感器GR3（车左后）
int graynum3;
int* level3 = NULL;

const int gray4 = A15;//灰度传感器GR4（车右后）
int graynum4;
int* level4 = NULL;

const int lightGA = 22;//光电传感器GA前上
int lightnumGA;//光电传感器GA返回数值
int* ligGA = NULL;//存储光电传感器数值lightnumGA的指针

const int lightGB = 18;//光电传感器GB左
int lightnumGB;
int* ligGB = NULL;

const int lightGC = 21;//光电传感器GC右
int lightnumGC;
int* ligGC = NULL;

const int lightGD = 33;//光电传感器GD后
int lightnumGD;
int* ligGD = NULL;

//const int lightGE = 45;//光电传感器GE后上
//int lightnumGE;
//int* ligGE = NULL;

const int trigCA = 49;//超声波传感器CA(左前)
const int echoCA = 50;
float distanceCA;//A传感器返回距离
float* disCA = NULL;//存储超声波传感器数值distance的指针

const int trigCB = 17;//超声波传感器CB（右前）
const int echoCB = 16;
float distanceCB;
float* disCB = NULL;

Servo myservo_left;  // 定义Servo对象来控制舵机
int pos_left = 0;    // 角度存储变量

Servo myservo_right;  // 定义Servo对象来控制舵机
int pos_right = 0;    // 角度存储变量

boolean on_stage = false;//判断小车是否在台上
boolean defend = false;//判断小车是否需要防御

VL53L1X sensor;//ToF红外传感器
int* tof_feedback = NULL;
int tof_temp;

//场外参数

//攻击返回边界灰度值
int attack_gray_edge = 900;

//循环比较参数值
int circle_compare = 25;

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);//打开接口9600
    Serial.println("Senesor:");

    //ToF红外传感器
    //ToF传感器的函数
    //sensor.read();

    //Serial.begin(115200);//打开接口115200

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

    pinMode(negLF, OUTPUT);//引脚3
    pinMode(posLF, OUTPUT);//引脚4
    pinMode(negRF, OUTPUT);//引脚5
    pinMode(posRF, OUTPUT);//引脚6

    pinMode(negLB, OUTPUT);//引脚9
    pinMode(posLB, OUTPUT);//引脚10
    pinMode(negRB, OUTPUT);//引脚11
    pinMode(posRB, OUTPUT);//引脚12

    pinMode(gray1, INPUT);//灰度传感器GR1
    pinMode(gray2, INPUT);//灰度传感器GR2
    pinMode(gray3, INPUT);//灰度传感器GR3
    pinMode(gray4, INPUT);//灰度传感器GR4

    pinMode(lightGA, INPUT);//光电传感器GA
    digitalWrite(lightGA, LOW);
    pinMode(lightGB, INPUT);//光电传感器GB
    digitalWrite(lightGB, LOW);
    pinMode(lightGC, INPUT);//光电传感器GC
    digitalWrite(lightGC, LOW);
    pinMode(lightGD, INPUT);//光电传感器GD
    digitalWrite(lightGD, LOW);
    //pinMode(lightGE, INPUT);//光电传感器GD
    //digitalWrite(lightGE, LOW);

    pinMode(trigCA, OUTPUT);//超声波传感器CA
    pinMode(echoCA, INPUT);
    pinMode(trigCB, OUTPUT);//超声波传感器CB
    pinMode(echoCB, INPUT);


    //myservo_left.attach(42);  //舵机控制线连接引脚
    //myservo_left.write(180);
    //delay(1800);

    //myservo_right.attach(45);//舵机控制线连接引脚
    //myservo_right.write(0);
    //delay(1800);

    pinMode(LED_BUILTIN, OUTPUT);//LED闪烁 

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
    Serial.print(*ligGD);
    //Serial.print("\t");
    Serial.println();

//   Gray_all();

  if(*ligGD==0)
  {
    start_temp();
  }
}

int start_temp()
{
  
    //单轮初始化
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


//灰度传感器一起测定
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
    graynum2 = quickSort(gray_void_num2, 0, 200) + 4;
    graynum3 = quickSort(gray_void_num3, 0, 200) + 35;
    graynum4 = quickSort(gray_void_num4, 0, 200) +2;

    level1 = &graynum1;
    level2 = &graynum2;
    level3 = &graynum3;
    level4 = &graynum4;

}

//回归中心函数
int return_center()
{
  Gray_all();
    GA();
    GB();
    GC();
    GD();


    if ((*level1 > *level3) && (*level2 > *level4) && (*ligGA == 0))
    {
        Serial.print("2");
        Serial.println();
        do
        {
            forward();
            Gray_all();
        } while ((*level1 > attack_gray_edge) && (*level2 > attack_gray_edge));
        back();
        delay(100);
    }
 

    //车子左侧靠中心
    else  if ((*level1 > *level2) && (*level3 > *level4))
    { 
        Serial.print("4");
        Serial.println();
        rotate_counterclockwise();
        delay(640);
        do
        {
            forward();
            Gray_all();
        } while ((*level1 > *level3) && (*level2 > *level4));
        forward();
        delay(5);
    }

    //车子右侧靠中心
    else if ((*level1 < *level2) && (*level3 < *level4))
    {
        Serial.print("5");
        Serial.println();
        rotate_clockwise();
        delay(640);
        do
        {
            forward();
            Gray_all();
        } while ((*level1 > *level3) && (*level2 > *level4));
        forward();
        delay(5);
    }

    //车子面向中心
    else if ((*level1 > *level3) && (*level2 > *level4))
    {
        Serial.print("1");
        Serial.println();
        do
        {
            forward();
            delay(5);
            Gray_all();
        } while ((*level1 > *level3) && (*level2 > *level4));
        forward();
        delay(5 );
    }



    ////车子左上靠里
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
    ////车子右上靠里
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
    ////车子左下靠里
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
    ////车子右下靠里
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
























//数学函数

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
        return s[100];
    }

    // 划分，返回基准点位置
    int i = quickSortPartition(s, l, r);

    // 递归处理左右两部分，i处为分界点，不用管i了
    quickSort(s, l, i - 1);
    quickSort(s, i + 1, r);

    return s[100];
}
































//调整灰度函数
int gray_retest()
{
    Gray_all();

    //求数组内中位数
    int median1 = *level1;
    int median2 = *level2;
    int median3 = *level3;
    int median4 = *level4;


    // 串口输出函数
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


//返回擂台
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

    if (*ligGD == 0)//车面向擂台
    {
        forward();
        delay(1000);
    }
    else if (*ligGA == 0)//车背向擂台
    {
        back();
        delay(1000);
    }
    else if (*ligGB == 0)//车右边靠擂台
    {
        rotate_clockwise();
        delay(620);
        forward();
        delay(1000);
    }
    else if (*ligGC == 0)//车左边靠擂台
    {
        rotate_counterclockwise();
        delay(620);
        forward();
        delay(1000);
    }
}

//判断是否在擂台
void judge_stage()
{
    Gray_all();

    //求数组内中位数
    int median1 = *level1;
    int median2 = *level2;
    int median3 = *level3;
    int median4 = *level4;

    //// 串口输出函数
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

     //循环比较
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

//攻击小车函数
int attack_car()
{
    //舵机展开
    change_servo_angle();

    //进攻对方小车
    do
    {
        //锁定对方小车方向
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

    //舵机回收
    back_servo_angle();
}

//int fully_attack()
//{
//    //舵机展开
//    change_servo_angle();
//     
//    Gray_all();
//    if (on_stage == false);
//    {
//        goto gg;
//    }
//
//    //重新攻击
//    restart:
//    //车子面向中心
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
//    //车子背离中心
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
//    //车子左侧靠中心
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
//    //车子右侧靠中心
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
//    //车子左上靠里
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
//    //车子右上靠里
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
//    //车子左下靠里
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
//    //车子右下靠里
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
//    //进攻对方小车
//    do
//    {
//        //锁定对方小车方向
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
//    //舵机回收
//    back_servo_angle();
//
//    //紧急跳转  
//gg:
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(100);
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(100);
//
//}



////用法
//int main()
//{
//    int a[21] = {};
//    quickSort(a, 0, 20);//注意最后一个参数是n-1
//}






//需调试小车移动函数

//前进函数
int forward()
{
    digitalWrite(posLF, HIGH);//左前向前
    digitalWrite(negLF, LOW);
    digitalWrite(posRF, LOW);//右前向前
    digitalWrite(negRF, HIGH);
    digitalWrite(posLB, LOW);//左后向前
    digitalWrite(negLB, HIGH);
    digitalWrite(posRB, HIGH);//右后向前
    digitalWrite(negRB, LOW);
}

//后退函数
int back()
{
    digitalWrite(posLF, LOW);//左前向前
    digitalWrite(negLF, HIGH);
    digitalWrite(posRF, HIGH);//右前向前
    digitalWrite(negRF, LOW);
    digitalWrite(posLB, HIGH);//左后向前
    digitalWrite(negLB, LOW);
    digitalWrite(posRB, LOW);//右后向前
    digitalWrite(negRB, HIGH);
}

//停止函数
int brake()
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

//顺时针旋转（600ms）

//顺时针旋转
int rotate_clockwise()
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
int rotate_counterclockwise()
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

//左转
int left()
{
    digitalWrite(posLF, LOW);//左前向
    digitalWrite(negLF, LOW);
    digitalWrite(posRF, LOW);//右前向
    digitalWrite(negRF, HIGH);
    digitalWrite(posLB, LOW);//左后向
    digitalWrite(negLB, LOW);
    digitalWrite(posRB, HIGH);//右后向
    digitalWrite(negRB, LOW);
}

//右转
int right()
{
    digitalWrite(posLF, HIGH);//左前向
    digitalWrite(negLF, LOW);
    digitalWrite(posRF, LOW);//右前向
    digitalWrite(negRF, LOW);
    digitalWrite(posLB, LOW);//左后向
    digitalWrite(negLB, HIGH);
    digitalWrite(posRB, LOW);//右后向
    digitalWrite(negRB, LOW);
}


//改动接口时注意改动函数中analogRead();



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

////光电传感器GE
//int GE()
//{
//    lightnumGE = digitalRead(lightGE);
//    ligGE = &lightnumGE;
//}

//超声波检测CA
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

//超声波检测CB
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

//红外传感器
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

//舵机旋转展开函数
int change_servo_angle()
{
    for (int i = 0; i < 180; i++)
    {
        myservo_left.write(180 - i);
        myservo_right.write(i);
        delay(10);
    }
}

//舵机旋转收回函数
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
//    case true://台上进攻
//        do
//        {
//            fully_attack();
//        } while (on_stage == true);
//        break;
//
//    case false://台下返回
//        do
//        {
//            back_stage();
//        } while(on_stage == false);
//        break;
//    }
//}
