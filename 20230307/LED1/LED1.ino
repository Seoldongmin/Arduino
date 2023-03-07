

void setup()
{
  pinMode(3,OUTPUT);//3번 핀을 출력으로 설정
  pinMode(4,INPUT); //4번 핀을 입력으로 설정
}

void loop() 
{
  digitalWrite(3,HIGH); //3번 핀 출력을 HIGH로
  delay(1000);          //1000msec 지연
  digitalWrite(3,LOW);  //3번 핀 출력을 LOW로
  delay(1000);          //1000msec 지연
 
}
