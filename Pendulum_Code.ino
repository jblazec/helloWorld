// 2018_11_1
#include "Dp_Fun.h"
#include "Controller.h"
#include "Set_Pos_And_Angles.h"
// Defining pin numbers **NOTE** Pins 2,3,18,19,20,21 are reserved attachInterrupt

 #include <math.h>

 Dp_Fun dpfun;
 Controller controller;
 Set_Pos_And_Angles setPosAngle;

// Defining pins 
  int Cart_Step_Pin=8;
  int Cart_Dir_Pin=9;
  int Cart_OutputA=20;
  int Cart_OutputB=21;
  int BM_Step_Pin=4;
  int BM_Dir_Pin=5;
  int BM_OutputA=2;
  int BM_OutputB=3;
  int BM_GND=50;
  int TM_Step_Pin=6;
  int TM_Dir_Pin=7;
  int TM_OutputA=18;
  int TM_OutputB=19;
  int TM_GND=52;



/////////////////////////////////////////////////////////////////////////////////////

// Sets timestep, angles reset to zero at current location, states set to zero
  
  int Cart_Counter = 0;
  double Cart_X = 0;
  double Cart_Error = 0;
  double Cart_dError = 0;
  double Cart_Old_Error = 0;
  double Cart_integralError = 0;
  int Cart_PWM = 0;

  int BM_Counter = 0;
  double BM_Angle = 0;
  double BM_Error = 0;
  double BM_dError = 0;
  double BM_Old_Error = 0;
  double BM_integralError = 0;
  int BM_PWM = 0;
  
  int TM_Counter = 0;
  double TM_Angle = 0;
  double TM_Error = 0;
  double TM_dError = 0;
  double TM_Old_Error = 0;
  double TM_integralError = 0;
  int TM_PWM = 0;
  
// Time and Timestep
  double dt = 0.0001; //100 microseconds
  unsigned long t = millis();
// Define initial set angles
  
  float Bottom_Set_Angle = 0;
  float Top_Set_Angle = 0;
  float Cart_Set_X = 0;
// setPosAngle.ZeroSetpoints();


/////////////////////////////////////////////////////////////////////////////////////

void setup() {
Serial.begin(9600);
Serial.println("Everything set to zero");
Serial.println(Cart_Set_X);
 // Setting Pins to proper inputs/outputs
dpfun.PendPinInitialize();
Serial.println("Pend initialize");
// Attach interrupt functions
 attachInterrupt(digitalPinToInterrupt(Cart_OutputA), dpfunCOAC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(Cart_OutputB), dpfunCOBC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(BM_OutputA), dpfunBOAC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(BM_OutputB), dpfunBOBC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(TM_OutputA), dpfunTOAC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(TM_OutputB), dpfunTOBC, CHANGE);
Serial.println("interrupts set");
// Calls swing up routine
dpfun.Swing_Up();
Serial.println("swingup done");
}


// Main loop
void loop()
{
//t = millis();  
//setPosAngle.BM_Setpoint_At_t();
//setPosAngle.TM_Setpoint_At_t();
//setPosAngle.Cart_Setpoint_At_t();
//Serial.println("New setpoints");
//Serial.println(Cart_Set_X);
//dpfun.Safety_Check(); // Ensures that set position and angles are not out of bounds and clips if needed
//dpfun.Get_Cart_States(); // Gets cart Error, dError, and integralError
//controller.PID_Cart_Controller(); // Computes cart PWM
//dpfun.Send_Cart_PWM(); // Sends PWM to cart
dpfun.Get_States(); // Gets arm Errors, dErrors, and integralErrors
controller.PD_Controller(); // Computes cart PWM
dpfun.Send_PWM();  // Sends PWM to arm
delayMicroseconds(100); // Delays 100 microseconds, used to be 10, but changed to 100 to match dt
}

// Bring the ISRs into global scale 
void dpfunCOAC(){
dpfun.Cart_OutputA_Change(); 
}

void dpfunCOBC() {
dpfun.Cart_OutputB_Change();
}

void dpfunBOAC() {
 dpfun.BM_OutputA_Change();
}

void dpfunBOBC() {
dpfun.BM_OutputB_Change();
}

void dpfunTOAC() {
dpfun.TM_OutputA_Change();
}

void dpfunTOBC(){
dpfun.TM_OutputB_Change();
}
