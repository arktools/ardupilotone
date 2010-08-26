/*
	Example of AP_RC library.
	Code by Jordi MuÒoz and Jose Julio. DIYDrones.com

	Print Input values and send Output to the servos
	(Works with last PPM_encoder firmware)
*/

#include <AP_RC.h> // ArduPilot Mega RC Library
AP_RC rc;

#define CH_ROLL 0
#define CH_PITCH 1
#define CH_THROTTLE 2
#define CH_RUDDER 3

void setup()
{
	Serial.begin(38400);
	Serial.println("ArduPilot RC library test");

	int trims[] = {1500,1500,1100,1500};
	rc.init(trims);

	delay(1000);
}
void loop()
{
	delay(20);
	rc.read_pwm();
	for(int y=0; y<4; y++) { 
		rc.set_ch_pwm(y, rc.input[y]); // send to Servos
	}
	print_pwm();
}


void print_pwm()
{
	Serial.print("ch1 ");
	Serial.print(rc.input[CH_ROLL],DEC);
	Serial.print("\tch2: ");
	Serial.print(rc.input[CH_PITCH],DEC);
	Serial.print("\tch3 :");
	Serial.print(rc.input[CH_THROTTLE],DEC);
	Serial.print("\tch4 :");
	Serial.println(rc.input[CH_RUDDER],DEC);
}