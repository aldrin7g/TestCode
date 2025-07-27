// this sample code provided by www.programmingboss.com
#define RXp2 16
#define TXp2 17
int c = 0,cal;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.begin(9600, SERIAL_8N1, (SerialMode)0, TXp2);

}
void loop() {
    //Serial.println("Message Received: ");
    //Serial.println(Serial.readString());
    //Serial.println(Serial.parseInt());
    c = Serial.parseInt();
    delay(1000);
    //Serial.println((Serial.readString());
    //c = c + Serial.parseInt();
    //cal = cal + c;
    Serial.println(c);
    //cal++;
}
