// jsn-S04T-v3 test
// Arduino Nano

#include <HCSR04.h>

#define TRIG_PIN 6
#define ECHO_PIN 5

void readSensor();
HCSR04 hc(TRIG_PIN, ECHO_PIN);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT_PULLUP);
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
  int valuesToRead = 5;

  int values[valuesToRead];
  for (int i=0; i<valuesToRead; i++){
   values[i] = hc.dist();
   delay(50);
  }

  // that +3 is to correct the (looks like) constant error
  // that this specific module is producing
  int distance = get_most_common(values, valuesToRead) + 3;

  Serial.println(distance);    
}


void loop() {  
  readSensor();
}
