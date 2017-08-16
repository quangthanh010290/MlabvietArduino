#include"MyServo.h"
void MyServo::init(int ctlPin,int enPin)
{
  this -> ofsX = (float)90;
  this -> minX = (float)-70;
  this -> maxX = (float)70;
  this -> x0 = 0;
  this->x = 0;
  this -> x1 = 0;
  this -> dx = x1-x0;
  this -> v = 0; //  [degree/second]
  this -> stepTime = 30; // mili second
  this -> T =0;
  this->t = 0;
  this -> mServo.attach(ctlPin);
  this -> mServo.write((float)this -> ofsX);
  this -> controlPin= ctlPin;
  this->enablePin = enPin;
  #ifdef ENABLE_EN_PIN
  	pinMode(this->enablePin,OUTPUT);                                                 
  	digitalWrite(this->enablePin,LOW);
  #endif
  
  this->state = FREE_STATE;

}
void MyServo::writeAngle(float angle)
{
	
	if (angle > this-> maxX) angle = this -> maxX;
	if (angle < this -> minX) angle = this -> minX;
	this -> x1 = angle;

	this -> x0 = this -> x;
	this -> dx = this -> x1- this -> x0;
  
 #ifdef ENABLE_CONTROL_BY_STEP
 	// if const speed, than calculate new period time
 	this -> T = abs(this -> dx)*1000/this -> v; // ms;

	
	
 #endif
 #ifdef ENABLE_CONTROL_BY_TIME
 	// If period time const, than calculate new speed
 	this->T = T_PERIOD;
 	this->v = abs(this->dx)*1000/this->T;
 #endif      
}
  
float MyServo::readAngle()
{
  return (float)(this -> x0);
}

float MyServo::tAngle(float t)
{
  float tem = x0 + 3*(x1 - x0)*t*t/(T*T) + 2*(x0 - x1)*t*t*t/(T*T*T);
  return tem;
  
}
void MyServo::turnOnServo()
{
  digitalWrite(this -> controlPin,HIGH);
}
void MyServo::turnOffServo()
{
  digitalWrite(this -> controlPin,LOW);
}

void MyServo::turnServo(){
	
	// ifnot finish turn motor
	if ((t < this -> T)&&(this->x!= this->x1)){
		this->state = BUSY_STATE;
		this->t += this -> stepTime;
		this->x = this -> tAngle(t);
	  	this -> mServo.write(this->x + this -> ofsX);
			
  	}
	else{
		this->state = FREE_STATE;
		this->x = this->x1;
		this->reset();
#ifdef ENABLE_EN_PIN
		this->turnOffServo();
#endif
	}

}
	void MyServo::reset(){
		this->t = 0;

	}






















