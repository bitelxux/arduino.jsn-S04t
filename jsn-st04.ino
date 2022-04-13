// jsn-S04T-v3 test
// Arduino Nano

#include <HCSR04.h>

#define TRIG_PIN 6
#define ECHO_PIN 5

void readSensor();

char buffer[100];
HCSR04 hc(TRIG_PIN, ECHO_PIN);

struct
{
    boolean enabled;
    unsigned long timer;
    unsigned long lastRun;
    void (*function)();
    char* functionName;
} TIMERS[] = {
  { true, 1*200, 0, &readSensor, "readSensor" },  
};


void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT_PULLUP);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(115200);
}


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

  int distance = get_most_common(values, valuesToRead) + 3;
      
  sprintf(buffer, "the distance is %d", distance);
  log(buffer);
}


void attendTimers(){    
  byte NUM_TIMERS = (sizeof(TIMERS) / sizeof(TIMERS[0]));
  for (int i=0; i<NUM_TIMERS; i++){
    if (TIMERS[i].enabled && millis() - TIMERS[i].lastRun >= TIMERS[i].timer) {
      TIMERS[i].function();
      TIMERS[i].lastRun = millis();
    }
  }
}


void log(char* msg){
  char *ID = "ard";
  char buffer[100];
  sprintf(buffer, "[%s] %s", ID, msg);
  Serial.println(buffer);
}


void loop() {  
  attendTimers();
}
