#include "Dp_Fun.h"




void Dp_Fun::PendPinInitialize()
{ pinMode(Cart_Step_Pin,OUTPUT);
 pinMode(Cart_Dir_Pin,OUTPUT);
 pinMode(Cart_OutputA,INPUT);
 pinMode(Cart_OutputB,INPUT);
 pinMode(BM_Step_Pin,OUTPUT);
 pinMode(BM_Dir_Pin,OUTPUT);
 pinMode(BM_OutputA,INPUT);
 pinMode(BM_OutputB,INPUT);
 pinMode(BM_GND, OUTPUT);
 digitalWrite(BM_GND, LOW);
 pinMode(TM_Step_Pin,OUTPUT);
 pinMode(TM_Dir_Pin,OUTPUT);
 pinMode(TM_OutputA,INPUT);
 pinMode(TM_OutputB,INPUT);
 pinMode(TM_GND, OUTPUT);
 digitalWrite(TM_GND, LOW);}



  
// Cart interrupt functions
void Dp_Fun::Cart_OutputA_Change() 
{
 if(digitalRead(Cart_OutputA) == HIGH) {
 if(digitalRead(Cart_OutputB) == HIGH) {
 Cart_Counter--;
 } else {
 Cart_Counter++;
 }
 } else {
 if(digitalRead(Cart_OutputB) == HIGH) {
 Cart_Counter++;
 } else {
 Cart_Counter--;
 }
 }
}


void Dp_Fun::Cart_OutputB_Change() 
{
 if(digitalRead(Cart_OutputB) == HIGH) {
 if(digitalRead(Cart_OutputA) == HIGH) {
 Cart_Counter++;
 } else {
 Cart_Counter--;
 }
 } else {
 if(digitalRead(Cart_OutputA) == HIGH) {
 Cart_Counter--;
 } else {
 Cart_Counter++;
 }
 }
}
 // End cart interrupt functions
 // BM interrupt functions
void Dp_Fun::BM_OutputA_Change() 
{
 if(digitalRead(BM_OutputA) == HIGH) {
 if(digitalRead(BM_OutputB) == HIGH) {
 BM_Counter--;
 } else {
 BM_Counter++;
 }
 } else {
 if(digitalRead(BM_OutputB) == HIGH) {
 BM_Counter++;
 } else {
 BM_Counter--;
 }
 }
}
void Dp_Fun::BM_OutputB_Change() 
{
 if(digitalRead(BM_OutputB) == HIGH) {
 if(digitalRead(BM_OutputA) == HIGH) {
 BM_Counter++;
 } else {
 BM_Counter--;
 }
 } else {
 if(digitalRead(BM_OutputA) == HIGH) {
 BM_Counter--;
 } else {
 BM_Counter++;
 }
 }
}
 // End BM interrupt functions
 // TM interrupt functions
 void Dp_Fun::TM_OutputA_Change() 
 {
 if(digitalRead(TM_OutputA) == HIGH) {
 if(digitalRead(TM_OutputB) == HIGH) {
 TM_Counter--;
 } else {
 TM_Counter++;
 }
 } else {
 if(digitalRead(TM_OutputB) == HIGH) {
 TM_Counter++;
 } else {
 TM_Counter--;
 }
 }
}
void Dp_Fun::TM_OutputB_Change() 
{
 if(digitalRead(TM_OutputB) == HIGH) {
 if(digitalRead(TM_OutputA) == HIGH) {
 TM_Counter++;
 } else {
 TM_Counter--;
 }
 } else {
 if(digitalRead(TM_OutputA) == HIGH) {
 TM_Counter--;
 } else {
 TM_Counter++;
 }
 }
}


// End TM interrupt functions

// Pendulum swing up routine (top pendulum needs no setting)
void Dp_Fun::Swing_Up(){
digitalWrite(BM_Dir_Pin, HIGH);
while (BM_Counter < 2625) {
 analogWrite(BM_Step_Pin, 255);
 Serial.println(BM_Counter);
}
analogWrite(BM_Step_Pin, 0);
BM_Counter = 0;
}

//Get states of top and bottom motor
void Dp_Fun::Get_States() {
  BM_Old_Error = BM_Error;
  BM_Angle = BM_Counter/14.611;
  BM_Error = Bottom_Set_Angle - BM_Angle;
  BM_dError = (BM_Error-BM_Old_Error)/dt;
  BM_integralError = BM_integralError + BM_Error;
  TM_Old_Error = TM_Error;
  TM_Angle = TM_Counter/11.378;
  TM_Error = Top_Set_Angle - TM_Angle;
  TM_dError = (TM_Error - TM_Old_Error)/dt;
  TM_integralError = TM_integralError + TM_Error;
  }

//Write PWM signals
void Dp_Fun::Send_PWM() {
  //Clip signals
  if (BM_PWM > 255) {
    BM_PWM = 255;
  }
  if (BM_PWM < -255) {
    BM_PWM = -255;
  }
  if (TM_PWM > 255) {
    TM_PWM = 255;
  }
  if (TM_PWM < -255){
    TM_PWM = -255;
  }
  //Set pin directions based on PWM sign, then make PWM positive
   if (BM_PWM < 0) {
  digitalWrite(BM_Dir_Pin,LOW);
 }
 if (BM_PWM > 0) {
  digitalWrite(BM_Dir_Pin,HIGH);
 }
 if (BM_PWM < 0) {
  BM_PWM = -BM_PWM;
 }
  if (TM_PWM > 0){
 digitalWrite(TM_Dir_Pin,LOW);
 }
 if (TM_PWM < 0){
  digitalWrite(TM_Dir_Pin,HIGH);
 }
 if (TM_PWM < 0) {
  TM_PWM = -TM_PWM;
 }
 analogWrite(BM_Step_Pin,BM_PWM);
 analogWrite(TM_Step_Pin,TM_PWM);
}

// Condition cart position signals
void Dp_Fun::Safety_Check(){
  //Clip signals
  if (Cart_X > 6){ //Cart X is in inches
    Cart_X = 6;
  }
  if (Cart_X < -6){
    Cart_X = -6;
  }
  if (Bottom_Set_Angle > 180){
    Bottom_Set_Angle = 180;  
  }
  if (Bottom_Set_Angle < -180){
    Bottom_Set_Angle = -180;
  }
  if (Top_Set_Angle > 90){
    Top_Set_Angle = 90;
  }  
  if (Top_Set_Angle < -90){
    Top_Set_Angle = -90;
  }
}

// Cart states
void Dp_Fun::Get_Cart_States() {
  Cart_Old_Error = Cart_Error;
  Cart_X = (0.5)*(Cart_Counter/14.611)*(3.14159/180); //inches, where 0.3 is radius, 14.611 is assumed counts per degree
  Cart_Error = Cart_Set_X - Cart_X;
  Cart_dError = (Cart_Error-Cart_Old_Error)/dt;
  Cart_integralError = Cart_integralError + Cart_Error;
  }



// Cart PWM
void Dp_Fun::Send_Cart_PWM() {
  //Clip signals
  if (Cart_PWM > 255) {
    Cart_PWM = 255;
  }
  if (Cart_PWM < -255) {
    Cart_PWM = -255;
  }
  
  //Set pin directions based on PWM sign, then make PWM positive
   if (Cart_PWM > 0) {
  digitalWrite(Cart_Dir_Pin,LOW);
 }
 if (Cart_PWM < 0) {
  digitalWrite(Cart_Dir_Pin,HIGH);
 }
 if (Cart_PWM < 0) {
  Cart_PWM = -Cart_PWM;
 }
 analogWrite(Cart_Step_Pin,Cart_PWM);
 // No delay, since delay occurs elsewhere
}
