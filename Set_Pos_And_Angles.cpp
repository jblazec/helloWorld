#include "Set_Pos_And_Angles.h"
#include "Dp_Fun.h"

void Set_Pos_And_Angles::ZeroSetpoints() {
  float Bottom_Set_Angle = 0;
  float Top_Set_Angle = 0;
  float Cart_Set_X = 0;
}

void Set_Pos_And_Angles::BM_Setpoint_At_t() {
Bottom_Set_Angle = 0;
}

void Set_Pos_And_Angles::TM_Setpoint_At_t() {
Top_Set_Angle = 0;
//Top_Set_Angle = 25*sin(2*3.14159*.2*t);
}

void Set_Pos_And_Angles::Cart_Setpoint_At_t() {
//Cart_Set_X = .5*sin(2*3.14159*.01*t); // A*sin(2*pi*f*t)
Cart_Set_X = 0;
}
