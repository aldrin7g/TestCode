const int trig=5;
const int echo=16;
const int led=14;
const int dist_limit=20;
void setup()
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
}
void loop()
{
  float dist,duration;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  duration=pulseIn(echo,HIGH);
  dist=0.017*duration;
 
  if(dist<=dist_limit)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  Serial.print("distance: ");
  Serial.print(dist);
  Serial.println("cm");
  delay(2000);
  
}
