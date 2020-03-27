#include <SoftwareSerial.h>
SoftwareSerial HC12(10,11);
int d = 0;
void setup() {
  Serial.begin(9600);
  HC12.begin(9600); 
}

void loop() {
  while (HC12.available()) {        
    Serial.write(HC12.read());      
  }
  while (Serial.available()) {
    HC12.write(Serial.read());
    d = 1;     
  }
  if(!Serial.available()){
    if(d>0 && d < 200){
      d++;
      delay(5);
    }
    if(d==200){
      HC12.write('~');
      delay(100);
      d++;
    }
  }

}
