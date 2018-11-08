#ifndef Controller_h
#define Controller_h
#include "DP_Fun.h"
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif

 
class Controller {
 
 public:
 void PD_Controller();
 void PID_Controller();
 void PID_Cart_Controller();

 private:
 

 
};



#endif
