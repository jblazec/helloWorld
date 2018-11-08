#include "Controller.h"

// PD controller
  float PD_BM_Kp = 10;
  float PD_BM_Kd = .1;
  float PD_TM_Kp = 4;
  float PD_TM_Kd = .1;
  
void Controller::PD_Controller() {
BM_PWM = (int) PD_BM_Kp*BM_Error + PD_BM_Kd*BM_dError;
TM_PWM = (int) PD_TM_Kp*TM_Error + PD_TM_Kd*TM_dError;
}

// PID controller
  float PID_BM_Kp = 10;
  float PID_BM_Kd = .1;
  float PID_BM_Ki = .0;
  float PID_TM_Kp = 10;
  float PID_TM_Kd = .1;
  float PID_TM_Ki = .00;
  
void Controller::PID_Controller() {
BM_PWM = (int) PID_BM_Kp*BM_Error + PID_BM_Kd*BM_dError + PID_BM_Ki*BM_integralError;
TM_PWM = (int) PID_TM_Kp*TM_Error + PID_TM_Kd*TM_dError + PID_TM_Ki*TM_integralError;
}

// Cart PID controller
  float PID_Cart_Kp = 30;
  float PID_Cart_Kd = .1;
  float PID_Cart_Ki = .00;
  
void Controller::PID_Cart_Controller() {
Cart_PWM = (int) PID_Cart_Kp*Cart_Error + PID_Cart_Kd*Cart_dError + PID_Cart_Ki*Cart_integralError;
}
