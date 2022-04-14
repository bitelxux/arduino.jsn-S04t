// jsn-S04T-v3 test
// Arduino Nano

#include <HCSR04.h>

#define TRIG_PIN 6
#define ECHO_PIN 5

void readSensor();
HCSR04 hc(TRIG_PIN, ECHO_PIN);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  // some people say it goes better with a pullup
  // I haven't needed it
  // pinMode(ECHO_PIN, INPUT_PULLUP);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(115200);
}


// Thanks for this, StackOverflow
int get_most_common(int vet[], size_t dim)
{
    size_t i, j, count;
    size_t most = 0;
    int temp, elem;

    for(i = 0; i < dim; i++) {
        temp = vet[i];
        count = 1;
        for(j = i + 1; j < dim; j++) {
            if(vet[j] == temp) {
                count++;
            }
        }
        if (most < count) {
            most = count;
            elem = vet[i];
        }
    }
    return elem;
}


void readSensor(){
  // to -try- to get rid of the wrong readings
  // (the sensor is not very stable), we read a few
  // times and keep the value that was most repeated
  int valuesToRead = 5;

  int values[valuesToRead];
  for (int i=0; i<valuesToRead; i++){
   values[i] = hc.dist();
   // it seems a good idea to give the little thing
   // some time to settle
   delay(50);
  }

  // that +3 is to correct the (looks like) constant error
  // that my specific module is producing
  int distance = get_most_common(values, valuesToRead) + 3;

  Serial.println(distance);    
}


void loop() {  
  readSensor();
  delay(50);
}
