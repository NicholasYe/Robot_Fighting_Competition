/*
 Name:		Example.ino
 Created:	2020/12/4 8:26:40
 Author:	NicholasYe
*/

// 引脚定义
int M_PWM[4] = { 9,10,11,12 };  //电机PWM，依次对应 LF,LB,RB,RF  L-Left R-Right F-Front B-Back
int M_Dir[8] = { 22,23,24,25,26,27,28,29 };   //控制电机正反转，依次对应 LF,LB,RB,RF,(一个电机需要两个，对应IN1,IN2)
int Switch[8] = { 46,47,48,49,50,51,52,53 };    //光电开关 依次为 F,L,B,R  LF,LB,RB,RF
int Gray[4] = { A0,A1,A2,A3 };  // 数组为int,与Arduino底层有关，不是错误 F,L,B,R
// 传感器的值 
int v_gray[4];    //存放对应灰度传感器的获取值 0~1023
int v_switch[8];    //存放对应光电开关传感器的获取值 0~1 0-近 1-远
//int g_compass;    //Compass的初始方向
// PWM的全局变量
int v_pwm[4] = { 120,120,120,120 };
int v_dir[4] = { 1,1,1,1 };
// 台上台下状态值
boolean on_stage = false;

void setup() {
    //  Serial.begin(9600);   //开启串口通信,调试用
    Dir_Init();
    // 非接触式启动
    while (1)
    {
        int a = digitalRead(Switch[1]);
        int b = digitalRead(Switch[3]);
        if (a == 0 && b == 0)
        {
            Go_PWM();
            delay(1000);
            delay(1000);
            break;
        }
    }
}

void loop() {
    Go_PWM();
    Stage();
    //Serial.println(on_stage);
    if (on_stage == true)
    {
        Edge();
        Enemy();
    }
    else {
        Fence();
    }
}

/*
 * 函数作用：控制一路电机的速度和正反转
 * 输入值：ch-电机号（0,1,2,3），dir-正反转（1,0），vel-速度（0~255）
 * 返回值：无
 */
void Change_PWM(int ch, int dir, int vel = -1) {
    digitalWrite(M_Dir[2 * ch], dir);
    digitalWrite(M_Dir[2 * ch + 1], !dir);
    if (vel != -1)  v_pwm[ch] = vel;
}

/*
 * 函数作用：电机正反转初始化
 * 输入值：无（使用全局变量）
 * 返回值：无
 */
void Dir_Init() {
    for (int i = 0; i < 8; i++) {
        pinMode(M_Dir[i], OUTPUT);
    }
    for (int i = 0; i < 4; i++) {
        digitalWrite(M_Dir[2 * i], v_dir[i]);
        digitalWrite(M_Dir[2 * i + 1], !v_dir[i]);
    }
}

/*
 * 函数作用：维持输出四路pwm
 * 输入值：无（使用全局变量）
 * 返回值：无
 */
void Go_PWM() {
    analogWrite(M_PWM[0], v_pwm[0]);
    analogWrite(M_PWM[1], v_pwm[1]);
    analogWrite(M_PWM[2], v_pwm[2]);
    analogWrite(M_PWM[3], v_pwm[3]);
}

/*
 * 函数作用：判断在擂台上还是在擂台下
 * 返回值：无
 */
void Stage()
{
    /*
     * 方案一：用灰度传感器的绝对值判断
    for(int i=0;i<4;i++){
      v_gray[i]=analogRead(Gray[i]);
      if(v_gray[i]>threshold1)
        on_stage=true;
      else if(v_gray[i]<threshold2)
        on_stage=false;
    }
    */
    /*
     * 方案二：用灰度传感器的差值判断
    for(int i=0;i<4;i++){
      v_gray[i]=analogRead(Gray[i]);
    }
    for(int i=0;i<4;i++)
    {
      for(int j=i+1;j<4;j++)
      {
         if( abs(v_gray[j]-v_gray[i])>threshold )
            on_stage=true;
         else  on_stage=false;
      }
    }
    */
    /*
     * 方案三：利用上下台子的反光度不同，利用光电开关判断
     * （与实际场地有关）
     */
    int value = 0;
    for (int i = 4; i < 8; i++) {
        v_switch[i] = digitalRead(Switch[i]);
        value = (value << 1) + v_switch[i];
    }
    //Serial.println(value);
    if (value == 15)
    {
        on_stage = false;
    }
    else if (value == 0)
    {
        on_stage = true;
    }

}

/*
 * 函数作用：在擂台下检测小车的朝向,并作处理
 * 返回值：无
 */
void Fence()
{
    int value = 0;
    for (int i = 0; i < 4; i++) {
        v_switch[i] = digitalRead(Switch[i]);
        value = (value << 1) + v_switch[i];
    }
    //Serial.println(value);
    switch (value) {
    case  0:  // 0 0 0 0  前左右后（可能有一侧有敌人）
        Turn_Right();
        break;
    case  1:  // 0 0 0 1  前左后
        Turn_Right();
        break;
    case  2:  // 0 0 1 0  前左右
        Turn_Left();
        break;
    case  3:  // 0 0 1 1  前左
        Turn_Right();
        break;
    case  4:  // 0 1 0 0  前后右
        Turn_Left();
        break;
    case  5:  // 0 1 0 1  前后
        Turn_Left();
        break;
    case  6:  // 0 1 1 0  前右
        Turn_Left();
        break;
    case  7:  // 0 1 1 1  前
        Attack(0);
        delay(1000);
        delay(1000);
        break;
    case  8:  // 1 0 0 0  后左右
        Turn_Left();
        delay(500);
        Attack(1);
        delay(1000);
        break;
    case  9:  // 1 0 0 1  左后
        Turn_Right();
        break;
    case  10: // 1 0 1 0  左右
        Turn_Left();
        break;
    case  11: // 1 0 1 1  左
        Turn_Right();
        break;
    case  12: // 1 1 0 0  后右
        Turn_Left();
        break;
    case  13: // 1 1 0 1  后
        Attack(1);
        delay(1000);
        delay(1000);
        break;
    case  14: // 1 1 1 0  右
        Turn_Left();
        break;
    case  15: // 1 1 1 1
        Attack(1);
        delay(1000);
        delay(1000);
        break;
    default:
        //Serial.println("Fence函数状态有误！");
        break;
    }
}

/*
 * 函数作用：在擂台上检测小车是否达到边缘
 * 返回值：无
 */
void Edge() {
    int value = 0;
    for (int i = 4; i < 8; i++) {
        v_switch[i] = digitalRead(Switch[i]);
        value = (value << 1) + v_switch[i];
    }
    if (value != 0) {
        //Serial.println("到达边缘!!！左转");
        Back();
        delay(500);
        Turn_Left();
        delay(1000);
    }
    else {
        if (Enemy() == 1)
        {
            return;
        }
        Straight();
        //Serial.println("尚未到达边缘，继续直行!");
    }
}

/*
 * 函数作用：在擂台上检测小车是否检测到敌人
 * 返回值：1-检测到敌人 0-没有检测到敌人
 */
int Enemy() {
    int value = 0;
    for (int i = 0; i < 4; i++) {
        v_switch[i] = digitalRead(Switch[i]);
        value = (value << 1) + v_switch[i];
    }
    if (value != 15) {
        //Serial.println("检测到敌人！"); 
        switch (value) {
        case 7://前
            Attack(1);
            break;
        case 11://左
            Turn_Left();
            delay(1000);
            break;
        case 13:  //后
            Attack(0);
            break;
        case 14: //右
            Turn_Right();
            delay(1000);
            break;
        default:
            //Serial.println("状态错误！");
            break;
        }
        return 1;
    }
    else {
        //Serial.println("未检测到敌人！");
        return 0;
    }

}

/*
 * 函数作用：快速前进
 * 输入值：1-向前走；0-向后走
 * 返回值：无
 */
void Attack(int dir)
{
    Change_PWM(0, dir, 220);
    Change_PWM(1, dir, 220);
    Change_PWM(2, dir, 220);
    Change_PWM(3, dir, 220);
    Go_PWM();
}

/*
 * 函数作用：向左转
 * 返回值：无
 */
void Turn_Left() {
    Change_PWM(0, 0, 120);
    Change_PWM(1, 0, 120);
    Change_PWM(2, 1, 120);
    Change_PWM(3, 1, 120);
    Go_PWM();
}

/*
 * 函数作用：向右转
 * 返回值：无
 */
void Turn_Right() {
    Change_PWM(0, 1, 120);
    Change_PWM(1, 1, 120);
    Change_PWM(2, 0, 120);
    Change_PWM(3, 0, 120);
    Go_PWM();
}

/*
 * 函数作用：向后走
 * 返回值：无
 */
void Back() {
    Change_PWM(0, 0, 120);
    Change_PWM(1, 0, 120);
    Change_PWM(2, 0, 120);
    Change_PWM(3, 0, 120);
    Go_PWM();
}

/*
 * 函数作用：向前走
 * 返回值：无
 */
void Straight() {
    Change_PWM(0, 1, 120);
    Change_PWM(1, 1, 120);
    Change_PWM(2, 1, 120);
    Change_PWM(3, 1, 120);
}
