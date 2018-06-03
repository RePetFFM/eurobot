#include <AccelStepper.h>
// #include <MultiStepper.h>
// 
#define STEPPER1_DIR_PIN 6
#define STEPPER1_STEP_PIN 2
// 
#define STEPPER2_DIR_PIN 7
#define STEPPER2_STEP_PIN 3
// 
#define STEPPER3_DIR_PIN 8
#define STEPPER3_STEP_PIN 4
// 
#define STEPPER4_DIR_PIN 9
#define STEPPER4_STEP_PIN 5
// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, STEPPER3_STEP_PIN, STEPPER3_DIR_PIN);
AccelStepper stepper4(AccelStepper::DRIVER, STEPPER4_STEP_PIN, STEPPER4_DIR_PIN);

long lf = 0;

long rf = 0;

long lr = 0;

long rr = 0;

long x = 0;
long y = 0;
long rotate = 0;

long maxRotSpeed = 2000;

long maxMoveSpeed = 5000;

long moveSpeed = 2000;

void setup()
{  
		pinMode(10, OUTPUT); // enable pin LOW = on
		pinMode(11, OUTPUT);
		pinMode(12, OUTPUT);
		pinMode(13, OUTPUT);  

		digitalWrite(10, HIGH); // enable pin LOW = on
		digitalWrite(11, LOW);
		digitalWrite(12, HIGH);
		digitalWrite(13, LOW);

		stepper1.setMaxSpeed(maxMoveSpeed);
    stepper1.setAcceleration(100.0);

    stepper2.setMaxSpeed(maxMoveSpeed);
    stepper2.setAcceleration(100.0);

    stepper3.setMaxSpeed(maxMoveSpeed);
    stepper3.setAcceleration(100.0);

    stepper4.setMaxSpeed(maxMoveSpeed);
    stepper4.setAcceleration(100.0);
    
    Serial.begin(38400);
}

void loop() {
	serialParser();
	stepper1.runSpeed();
	stepper2.runSpeed();
	stepper3.runSpeed();
	stepper4.runSpeed();
}




void calcWheels() {
	// get desired translation and rotation, scaled to [-127..128] (0 neutral)

	// calculate wheel throttles

	lf = x + y + rotate;

	rf = x - y + rotate;

	lr = -x + y + rotate;

	rr = -x - y + rotate;


	// normalize wheel throttles

	/*
	float maximum = max(max(abs(lf), abs(rf)), max(abs(lr), abs(rr)));

	if (maximum >1000) {

	lf = (lf / maximum) * 1000;

	rf = (rf / maximum) * 1000;

	lr = (lr / maximum) * 1000;

	rr = (rr / maximum) * 1000;
	*/
}

void serialParser() {
	static uint8_t buf[32];
  static uint8_t bufcnt = 0;
  uint8_t c;

  boolean controlUpdate = false;

	while(Serial.available()) {
		//digitalWrite(LEDGN1, !digitalRead(LEDGN1));
		
		c = Serial.read();
		buf[bufcnt++] = c;


		if(((c == 0x0a) || (bufcnt > 30)) || ((bufcnt==1 ) && ((c=='q') || (c=='w') ||(c=='e') ||(c=='a') ||(c=='s') || (c=='d') || (c==' ')))) { // (c == 0x0d) ||
			buf[bufcnt] = 0;
			controlUpdate = false;
			switch(buf[0]) {
				case 'q': 
					clearMotorSpeedValues();
					rotate = -maxRotSpeed;
					controlUpdate = true;
				break;
				case 'e': 
					clearMotorSpeedValues();
					rotate = maxRotSpeed;
					controlUpdate = true;
				break;
				case 'w': 
					clearMotorSpeedValues();
					y = moveSpeed;
					controlUpdate = true;
				break;
				case 's': 
					clearMotorSpeedValues();
					y = -moveSpeed;
					controlUpdate = true;
				break;
				case 'a': 
					clearMotorSpeedValues();
					x = -moveSpeed;
					controlUpdate = true;
				break;
				case 'd': 
					clearMotorSpeedValues();
					x = moveSpeed;
					controlUpdate = true;
				break;
				case 'g': // goto
					{
						int xx,yy,rr;
						if(sscanf((const char*)&buf[1],"%d %d %d",&xx,&yy,&rr)==3) {
							x = xx;
							y = yy;
							rotate = rr;
							Serial.print(x);
							Serial.print(',');
							Serial.print(y);
							Serial.print(',');
							Serial.println(rotate);
							controlUpdate = true;
						}
					}
	      // do something
	      break;
	    	case ' ': // stop
	      // do something
	      digitalWrite(10, HIGH); // enable pin LOW = on
	      stepper1.setSpeed(0);
				stepper2.setSpeed(0);
				stepper3.setSpeed(0);
				stepper4.setSpeed(0);
				rotate = 0;
				x = 0;
				y = 0;
	      break;
			}

			if(controlUpdate) {
				calcWheels();
				stepper1.setSpeed(-rf);
				stepper2.setSpeed(-lf);
				stepper3.setSpeed(lr);
				stepper4.setSpeed(rr);
				digitalWrite(10, LOW); // enable pin LOW = on
			}

			/*
			if(bufcnt >= 4) { 
				uint16_t var_temp;
				var_temp = (get2Hex((char*)buf))*256U+get2Hex((char*)(buf+2));
				speed2DistPerSec = (var_temp<0x7fffU) ? var_temp : 0x7fffU;
			}
			*/
			bufcnt = 0;
		}
	}
}

void clearMotorSpeedValues() {
	rotate = 0;
	x = 0;
	y = 0;
}