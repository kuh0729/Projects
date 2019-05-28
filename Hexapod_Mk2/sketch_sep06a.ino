#include <Servo.h>
#include <SoftwareSerial.h>
#include <PID_v1.h>
#include <math.h>

Servo myservo[18];
  int b1,b2,b3,b4,b5,b6=0;
  int b51,b52,b53,b54,b55,b56=0;
  int b61,b62,b63,b64,b65,b66=0;
  double pid;
  int l1,l2,l3,l4,l5,l6=0;
  int f1,f2,f3,f4,f5,f6=0;
  int w,s,q,e,r,a,d,j,l,h=0;
  int action_speed =0;

//Specify the links and initial tuning parameters
double Kp, Ki, Kd;
double error;
double error_previous;

double desired_value;
double current_value, current_value_x, current_value_y, current_value_z;
float val, val_mapped;

double P_control, I_control, D_control;
//double PID_control, PID_control2, PID_control3;
double Time = 0.5;  
  
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high


// uncomment "OUTPUT_READABLE_QUATERNION" if you want to see the actual
// quaternion components in a [w, x, y, z] format (not best for parsing
// on a remote host such as Processing or something though)
//#define OUTPUT_READABLE_QUATERNION

// uncomment "OUTPUT_READABLE_EULER" if you want to see Euler angles
// (in degrees) calculated from the quaternions coming from the FIFO.
// Note that Euler angles suffer from gimbal lock (for more info, see
// http://en.wikipedia.org/wiki/Gimbal_lock)
//#define OUTPUT_READABLE_EULER

// uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
// pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.
// Also note that yaw/pitch/roll angles suffer from gimbal lock (for
// more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
#define OUTPUT_READABLE_YAWPITCHROLL

// uncomment "OUTPUT_READABLE_REALACCEL" if you want to see acceleration
// components with gravity removed. This acceleration reference frame is
// not compensated for orientation, so +X is always +X according to the
// sensor, just without the effects of gravity. If you want acceleration
// compensated for orientation, us OUTPUT_READABLE_WORLDACCEL instead.
//#define OUTPUT_READABLE_REALACCEL

// uncomment "OUTPUT_READABLE_WORLDACCEL" if you want to see acceleration
// components with gravity removed and adjusted for the world frame of
// reference (yaw is relative to initial orientation, since no magnetometer
// is present in this case). Could be quite handy in some cases.
//#define OUTPUT_READABLE_WORLDACCEL

// uncomment "OUTPUT_TEAPOT" if you want output that matches the
// format used for the InvenSense teapot demo
//#define OUTPUT_TEAPOT



//#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
//bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion qa;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}



void setup()
{

  Serial.begin(115200);
//  Serial2.begin(9600);
  Serial.print("start");

 ypr_setup();
 
  myservo[0].attach(5);   // body1 5
  myservo[1].attach(28);   // leg1 28
  myservo[2].attach(46);   //  foot1 46

  myservo[3].attach(61);   // body2 61
  myservo[4].attach(45);   // leg2 45
  myservo[5].attach(41);   //  foot2 41

  myservo[6].attach(12);   // body3 12
  myservo[7].attach(13);   // leg3 13
  myservo[8].attach(62);   // foot3 62

  myservo[9].attach(55);    // body4 55
  myservo[10].attach(31);   // leg4 47
  myservo[11].attach(3);   //  foot4  6
  
  myservo[12].attach(30);   // body5 //30
  myservo[13].attach(7);   // leg5 7
  myservo[14].attach(54);   //  foot5 54

  myservo[15].attach(44);    // body6 44
  myservo[16].attach(8);   // leg6 8
  myservo[17].attach(11);   //  foot6  11

  val_setup();
  standing();
  stand();



}
/*
 int action_speed = 110;
  
  myservo[0].write(b1+0);   // body1    90
  myservo[1].write(l1+0);   // leg1   130
  myservo[2].write(f1+(0*-1));   //  foot1  170
  
  myservo[9].write(b4+(0*-1));    // body4  140
  myservo[10].write(l4+(0*-1));   // leg4   50
  myservo[11].write(f4+0);   //  foot4  10  
  
  myservo[12].write(b5+0);   // body5  90
  myservo[13].write(l5+0);   // leg5  130
  myservo[14].write(f5+(0*-1));   //  foot5 130 
  
  myservo[3].write(b2+(0*-1));   // body2   90
  myservo[4].write(l2+(0*-1));   // leg2    40
  myservo[5].write(f2+0);   //  foot2    0
  
  myservo[6].write(b3+0);   // body3    30
  myservo[7].write(l3+0);   // leg3   135
  myservo[8].write(f3+(0*-1));   // foot3   135
  
  myservo[15].write(b6+(0*-1));    // body6  90
  myservo[16].write(l6+(0*-1));   // leg6   40
  myservo[17].write(f6+0);   //  foot6  40
 delay(action_speed);//1
 */
 

