int light1=3;//光电传感器
int v_light1;//光电传感器返回数值

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);//LED闪烁 
  Serial.begin(9600);
}

//主循环
void loop()
{
  light_test();
}

//传感器检测
void light_test()
{
  //读取光电传感器数值
  int value=0;
  v_light1=digitalRead(light1);
  value=v_light1;
  Serial.print(value);
  Serial.println();
  //条件判断
  if(value==0)
  {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else
  {
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  }
}
