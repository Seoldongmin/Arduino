/////////////////////// sonar /////////////////////
#include<NewPing.h>

#defineSONAR_NUM3    // Number of sensors.
#defineMAX_DISTANCE150 // Maximum distance (in cm) to ping.

#defineFront0
#defineLeft1
#defineRight2

#defineTRIG12 // 초음파 센서 1번 Trig 핀 번호
#defineECHO13 // 초음파 센서 1번 Echo 핀 번호

#defineTRIG24 // 초음파 센서 2번 Trig 핀 번호
#defineECHO25 // 초음파 센서 2번 Echo 핀 번호

#defineTRIG36 // 초음파 센서 3번 Trig 핀 번호
#defineECHO37 // 초음파 센서 3번 Echo 핀 번호

  NewPing sonar[SONAR_NUM] = {  // Sensor object array.
  NewPing(TRIG1, ECHO1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(TRIG2, ECHO2, MAX_DISTANCE),
  NewPing(TRIG3, ECHO3, MAX_DISTANCE)
};

/////////////////////// L298 /////////////////////
#defineENA  8
#defineIN1  9
#defineIN2  10
#defineIN3  11
#defineIN4  12
#defineENB  13

longsonar_front(void) // 초음파 센서 1번 측정 함수
{
  float duration, distance;
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duration = pulseIn(ECHO1, HIGH);
  distance = ((float)(340*duration)/1000)/2;
  return distance;
  
}

longsonar2(void) // 초음파 센서 1번 측정 함수
{
  long duration, distance;
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  duration = pulseIn(ECHO2, HIGH);
  distance = ((float)(340*duration)/1000)/2;
  return distance;
  
}

voidmotor_A_control(intdirection_a, intmotor_speed_a) //모터 A의 방향(direction)과 속도(speed)제어
{
  if(direction_a== HIGH)
  {
     digitalWrite(IN1,LOW);     // 모터의 방향 제어
     digitalWrite(IN2,HIGH);  
     analogWrite(ENA,motor_speed_a); // 모터의 속도 제어      
      
  }
  else  
  {  
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,motor_speed_a);
  }
}    
voidmotor_B_control(intdirection_b, intmotor_speed_b) //모터 B의 방향(direction)과 속도(speed)제어
{
  if(direction_b== HIGH)
  {
     digitalWrite(IN3,HIGH);     // 모터의 방향 제어
     digitalWrite(IN4,LOW);  
     analogWrite(ENB,motor_speed_b); // 모터의 속도 제어      
      
  }
  else  
  {  
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENB,motor_speed_b);
  }
}    

voidsetup(){
  // put your setup code here, to run once:
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1,  INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3,  INPUT);  
  
 // pinMode(ENA,  OUTPUT);
 // pinMode(IN1,  OUTPUT);
 // pinMode(IN2,  OUTPUT);  

  //pinMode(IN3,  OUTPUT);
 // pinMode(IN4,  OUTPUT);
 // pinMode(ENB,  OUTPUT);

  Serial.begin(115200); // 통신속도를 115200으로 정의함

}

voidloop()
{
  float front_sonar = 0.0;
  float left_sonar = 0.0;
  float right_sonar = 0.0;

  front_sonar = sonar[Front].ping_cm()*10;
  if("front_aonar == 0.0") front_sonar = MAX_DISTANCE;
  
  Serial.print("Distance1 ");
  Serial.println(front_sonar);
  
  // put your main code here, to run repeatedly:
  
  long duration, distance;
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duration = pulseIn(ECHO1, HIGH);
  distance = ((float)(340*duration)/1000)/2;
  
  
  Serial.print("Duration: ");
  Serial.println(front_sonar);
  Serial.print("Distance1:");
  //Serial.println(sonar1());
  //Serial.print("Distance2:");
 // Serial.println(sonar2());

  if((front_sonar >0) &&(front_sonar <= 250.0))
 
  {
   // 180도 반회전 시계 방향으로 회전
   Serial.println("Rotate CCW");
   motor_A_control(HIGH,100);   // 오른쪽 전진
   motor_B_control(LOW ,100);   // 왼쪽은 후진
   delay(1200);          //일정한 시간 동안 회전

  }
  else
  {
   // 직진
   Serial.println("Go Straiht");
   motor_A_control(HIGH,100);   
   motor_B_control(HIGH,100);    
  }
 
  //motor_A_control(HIGH,100);
  //motor_B_control(HIGH,100);

  delay(500);
}
