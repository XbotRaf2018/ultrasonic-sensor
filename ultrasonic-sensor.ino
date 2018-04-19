#include <SharpIR.h>
#include <Wire.h>

#define LEFT_SENSOR A0
#define RIGHT_SENSOR A1
#define FRONT_SENSOR A2
#define BACK_SENSOR A3

#define TRIG_PIN 2

int sensors[] = {LEFT_SENSOR, RIGHT_SENSOR, FRONT_SENSOR, BACK_SENSOR};

byte results[50];
byte result;

void setup() {
	Serial.begin(115200);
	Wire.begin(9);
	Wire.onRequest(requestEvent);

	pinMode(TRIG_PIN, OUTPUT);

	for(int i = 0; i < sizeof(sensors)/sizeof(*sensors); i++){
		pinMode(sensors[i], INPUT);
	}
}

void loop() {
	for(int i = 0; i < sizeof(sensors)/sizeof(*sensors); i++){
		if(sensors[i] == FRONT_SENSOR){
			SharpIR sharp(sensors[i], 20150);
			results[i] = sharp.distance();
		} else {
			digitalWrite(TRIG_PIN, LOW); 
			delayMicroseconds(2); 

			digitalWrite(TRIG_PIN, HIGH);
			delayMicroseconds(10); 

			digitalWrite(sensors[i], LOW);
			result = pulseIn(sensors[i], HIGH);

			result /= 58.2;

			if(result < 40 && result != 0){
				results[i] = result;
			} else {
				results[i] = 41;
			}
		}

		Serial.print(sensors[i]);
		Serial.print(": ");
		Serial.println(results[i]);

		delay(50);
	}
}

void requestEvent() {
	for(int i = 0; i < sizeof(sensors)/sizeof(*sensors); i++){
		Wire.write(byte);
	}
}

