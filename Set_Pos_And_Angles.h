#ifndef Set_Pos_And_Angles_h
#define Set_Pos_And_Angles_h

#include "Dp_Fun.h"
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif

extern float Bottom_Set_Angle;
extern float Top_Set_Angle;
extern float Cart_Set_X;

class Set_Pos_And_Angles {
 
 public:
 void ZeroSetpoints();
 void BM_Setpoint_At_t();
 void TM_Setpoint_At_t();
 void Cart_Setpoint_At_t();

 private:
 

 
};



#endif
