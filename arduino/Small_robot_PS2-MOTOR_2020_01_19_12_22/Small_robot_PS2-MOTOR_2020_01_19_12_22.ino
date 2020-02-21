#include <PS2X_lib.h>  //for MOEBIUS
#include "FaBoPWM_PCA9685.h"
/** dependancy :
 *  - https://github.com/FaBoPlatform/FaBoPWM-PCA9685-Library.git
 *  - https://github.com/madsci1016/Arduino-PS2X.git
 *  .
 *  
 *  source :
 *  - https://github.com/MoebiusTech/MecanumRobot-Arduino-Uno.git 
 *  .
 *  
*/
//#include "servo.hpp"
//#include <WireUtility.h>
//#include <SoftWire.h>
//SoftWire i2c(A4, A5);//as uno board
FaBoPWM faboPWM/*(&Wire, PCA9685_SLAVE_ADDRESS)*/;
int pos = 0;
int MAX_VALUE = 2000;   // 电机速度限制 motor speed 
int MIN_VALUE = 300;

//PS2手柄引脚；PS2 handle Pin
#define PS2_DAT        13
#define PS2_CMD        11
#define PS2_SEL        10
#define PS2_CLK        12

//MOTOR CONTROL Pin
#define DIRA1 0
#define DIRA2 1
#define DIRB1 2
#define DIRB2 3
#define DIRC1 4
#define DIRC2 5
#define DIRD1 6
#define DIRD2 7

char speed;
// #define pressures   true
#define pressures   false
// #define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

void (* resetFunc) (void) = 0;

//电机控制，前进、后退、停止   motor control advance\back\stop
#define MOTORA_FORWARD(pwm)    do{faboPWM.set_channel_value(DIRA1,pwm);faboPWM.set_channel_value(DIRA2, 0);}while(0)
#define MOTORA_STOP(x)         do{faboPWM.set_channel_value(DIRA1,0);faboPWM.set_channel_value(DIRA2, 0);}while(0)
#define MOTORA_BACKOFF(pwm)    do{faboPWM.set_channel_value(DIRA1,0);faboPWM.set_channel_value(DIRA2, pwm);}while(0)

#define MOTORB_FORWARD(pwm)    do{faboPWM.set_channel_value(DIRB1,pwm);faboPWM.set_channel_value(DIRB2, 0);}while(0)
#define MOTORB_STOP(x)         do{faboPWM.set_channel_value(DIRB1,0);faboPWM.set_channel_value(DIRB2, 0);}while(0)
#define MOTORB_BACKOFF(pwm)    do{faboPWM.set_channel_value(DIRB1,0);faboPWM.set_channel_value(DIRB2, pwm);}while(0)

#define MOTORC_FORWARD(pwm)    do{faboPWM.set_channel_value(DIRC1,pwm);faboPWM.set_channel_value(DIRC2, 0);}while(0)
#define MOTORC_STOP(x)         do{faboPWM.set_channel_value(DIRC1,0);faboPWM.set_channel_value(DIRC2, 0);}while(0)
#define MOTORC_BACKOFF(pwm)    do{faboPWM.set_channel_value(DIRC1,0);faboPWM.set_channel_value(DIRC2, pwm);}while(0)

#define MOTORD_FORWARD(pwm)    do{faboPWM.set_channel_value(DIRD1,pwm);faboPWM.set_channel_value(DIRD2, 0);}while(0)
#define MOTORD_STOP(x)         do{faboPWM.set_channel_value(DIRD1,0);faboPWM.set_channel_value(DIRD2, 0);}while(0)
#define MOTORD_BACKOFF(pwm)    do{faboPWM.set_channel_value(DIRD1,0);faboPWM.set_channel_value(DIRD2, pwm);}while(0)

#define SERIAL  Serial

//#define SERIAL  Serial3

#define LOG_DEBUG

#ifdef LOG_DEBUG
#define M_LOG SERIAL.print
#else
#define M_LOG 
#endif

//PWM参数
#define MAX_PWM   2000
#define MIN_PWM   300

int Motor_PWM = 1900;
 
//控制电机运动    宏定义
//    ↑A-----B↑   
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
void ADVANCE(uint8_t pwm_A,uint8_t pwm_B,uint8_t pwm_C,uint8_t pwm_D)
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);    
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM);    
}

//    ↓A-----B↓ 
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void BACK()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}

//    =A-----B↑   
//     |   ↖ |
//     | ↖   |
//    ↑C-----D=
void LEFT_1()
{
  MOTORA_STOP(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

//    ↓A-----B↑   
//     |  ←  |
//     |  ←  |
//    ↑C-----D↓
void LEFT_2()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↓A-----B=   
//     | ↙   |
//     |   ↙ |
//    =C-----D↓
void LEFT_3()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↑A-----B=   
//     | ↗   |
//     |   ↗ |
//    =C-----D↑
void RIGHT_1()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    ↑A-----B↓   
//     |  →  |
//     |  →  |
//    ↓C-----D↑
void RIGHT_2()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    =A-----B↓   
//     |   ↘ |
//     | ↘   |
//    ↓C-----D=
void RIGHT_3()
{
  MOTORA_STOP(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

//    ↑A-----B↓   
//     | ↗ ↘ |
//     | ↖ ↙ |
//    ↑C-----D↓
void rotate_1()  //tate_1(uint8_t pwm_A,uint8_t pwm_B,uint8_t pwm_C,uint8_t pwm_D) 
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}

//    ↓A-----B↑   
//     | ↙ ↖ |
//     | ↘ ↗ |
//    ↓C-----D↑
void rotate_2()  // rotate_2(uint8_t pwm_A,uint8_t pwm_B,uint8_t pwm_C,uint8_t pwm_D)
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    =A-----B=  
//     |  =  |
//     |  =  |
//    =C-----D=
void STOP()
{
  MOTORA_STOP(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

//串口输入控制
void UART_Control()
{
  char Uart_Date=0;
  if(SERIAL.available())
  {
    Uart_Date = SERIAL.read();
  }
  switch(Uart_Date)
  {
     case 'A':  ADVANCE(500,500,500,500);  M_LOG("Run!\r\n");        break;
     case 'B':  RIGHT_1();  M_LOG("Right up!\r\n");     break;
     case 'C':  rotate_2();                            break;      
     case 'D':  RIGHT_3();  M_LOG("Right down!\r\n");   break;
     case 'E':  BACK();     M_LOG("Run!\r\n");          break;
     case 'F':  LEFT_3();   M_LOG("Left down!\r\n");    break;
     case 'G':  rotate_1();                              break;         
     case 'H':  LEFT_1();   M_LOG("Left up!\r\n");     break;
     case 'Z':  STOP();     M_LOG("Stop!\r\n");        break;
     case 'z':  STOP();     M_LOG("Stop!\r\n");        break;
     case 'd':  LEFT_2();   M_LOG("Left!\r\n");        break;
     case 'b':  RIGHT_2();  M_LOG("Right!\r\n");        break;
     case 'L':  Motor_PWM = 1500;                      break;
     case 'M':  Motor_PWM = 500;                       break;
   }
}

void IO_init()
{
  STOP();
}

void setup()
{
   IO_init(); 
   SERIAL.begin(9600);
   Serial.println("Scanning...PCA9685");
   /*
   i2c.setDelay_us(5);
 i2c.begin();
  
   scan(Serial,i2c);
    while(scanNext(Serial,i2c)!=0);
  */
  if(faboPWM.begin()) 
  {
    Serial.println("Find PCA9685");
    faboPWM.init(300);
  }else
   Serial.println("PCA9685 missing");
  faboPWM.set_hz(50);
  SERIAL.print("Start"); 

   delay(300) ; //added delay to give wireless ps2 module some time to startup, before configuring it
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
  {
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
    resetFunc();
    
  }

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

//  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
  case 0:
    Serial.print("Unknown Controller type found ");
    break;
  case 1:
    Serial.print("DualShock Controller found ");
    break;
  case 2:
    Serial.print("GuitarHero Controller found ");
    break;
  case 3:
    Serial.print("Wireless Sony DualShock Controller found ");
    break;
  }
}



void loop()
{
  
   // UART_Control();//串口接收处理 
    //CAR_Control();//小车控制
      /* You must Read Gamepad to get new values and set vibration values
    ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
    if you don't enable the rumble, use ps2x.read_gamepad(); with no values
    You should call this at least once a second
  */
  if (error == 1) //skip loop if no controller found
    return;

  if (type == 2) { //Guitar Hero Controller
    return;
  }
  else  { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed


//start 开始运行，电机初PWM为120；
    if (ps2x.Button(PSB_START))  {
      Serial.println("Start is being held");
      ADVANCE(500,500,500,500);


    }
// 电机正转；
    if (ps2x.Button(PSB_PAD_UP)) {
      Serial.println("Up held this hard: ");
     ADVANCE(500,500,500,500);
    }

// 电机反转；
    if (ps2x.Button(PSB_PAD_DOWN)) {
      Serial.println("Down held this hard: ");
      BACK();
    }

//左转；
    if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.println("turn left ");
      rotate_2();
    }

//右转；
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.println("turn right");
      rotate_1();
    }
// Stop
    if (ps2x.Button(PSB_SELECT)) {
      Serial.println("stop");
      STOP();
    }
// 左平移
    if (ps2x.Button(PSB_PINK)) {
      Serial.println("motor_pmove_left");
      LEFT_2();
    }
// 右平移
    if (ps2x.Button(PSB_RED)) {
      Serial.println("motor_pmove_right");
      RIGHT_2();
    }
    delay(20);

  }
  Serial.print(".");
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);
}
    int LY = ps2x.Analog(PSS_LY);
    int LX = ps2x.Analog(PSS_LX);
    int RY = ps2x.Analog(PSS_RY);
    int RX = ps2x.Analog(PSS_RX);
signed int speed1=0;
signed int speed2=0;
#define f 35
    if (LY != 127) //前进
    {

      speed1 += f * (127 - LY);
      speed2 += f * (127 - LY);
   
    }

//    //左转
    if (LX != 128)
    {
 
       speed1 += f * (128 - LX);
      speed2 += -f * (128 - LX);
     }
     speed1=max(speed1,-4095);
     speed2=max(speed2,-4095);
     speed1=min(speed1,4095);
     speed2=min(speed2,4095);
     
     /*
//    //如果摇杆居中
    if (LY >= 128 && LY <= 128 && LX >= 128 && LX <= 128)
    {
       STOP();
      delay(20);
    }
    else*/
    {
      
      forward(speed1,speed2);
    Serial.print("speed Values:");
    Serial.print(LX, DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(LY, DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(speed1, DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.println(speed2, DEC);
    delay(20);
    }

  
}


//    ↓A-----B↓ 
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void back(unsigned int pwm)
{
  MOTORA_FORWARD(pwm);MOTORB_BACKOFF(pwm);
  MOTORC_FORWARD(pwm);MOTORD_BACKOFF(pwm);
}
void stop()
{
  MOTORA_FORWARD(0);MOTORB_BACKOFF(0);
  MOTORC_FORWARD(0);MOTORD_BACKOFF(0);
}

//    ↑A-----B↑   
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
void forward(signed int pwm1,signed int pwm2)
{

  if(pwm1==0)
  {
    MOTORA_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);
  }
  else
  if(pwm1>0)
  {
  MOTORA_BACKOFF(pwm1);
  MOTORC_BACKOFF(pwm1);
  }else
  {
  MOTORA_FORWARD(-pwm1);
  MOTORC_FORWARD(-pwm1);
  }

  
  if(pwm2==0)
  {
    MOTORB_STOP(Motor_PWM);
     MOTORD_STOP(Motor_PWM);
  }
  else
  if(pwm2>0)
  {
  MOTORB_FORWARD(pwm2);
  MOTORD_FORWARD(pwm2);
}else
  {
  MOTORC_BACKOFF(-pwm2);
  MOTORD_BACKOFF(-pwm2);
  }
  }
