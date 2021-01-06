// Main code using functions for tremor vector and setting motor speed

#include <MPU9250_asukiaaa.h>
#include <Servo.h>

MPU9250_asukiaaa mySensor; // create sensor object for accelerometer
Servo motor;              // create servo object to control the ESC


float abs_tremor_vector, val, tremor1, tremor2;
int motor_speed;


void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginAccel();

  motor.attach(9, 1000, 2000); // Attach the motor on pin 9 (pin, min pulse width, max pulse width in microseconds)

  tremor1 = 0;
  tremor2 = 0;
  val = 0;
  motor_speed = 0;
}


void loop() {
  tremor1 = getTremorVector(); // Call function for calculating current accelerometer data and turning it into a 3D vector
  delay(400);
  tremor2 = getTremorVector();

  abs_tremor_vector = abs(tremor1 - tremor2); // Calculating difference between two tremors, essentially the derivative

  val = 0.90 * val + abs_tremor_vector; // Adding difference to 90% of old difference values, essentially integrating the derivative
  Serial.print("tremor value is: ");
  Serial.println(val);

  motor_speed = SetMotorSpeed(val); // Calling the function for setting the speed of the motor using the value calculated above
  motor.write(motor_speed);

  Serial.print("motor speed is ");
  Serial.println(motor_speed);
}

// Function for calculating tremor, making a 3D vector from accelerometer values in x,y and z- directions using Pythagorean theorem
float getTremorVector(){
  mySensor.accelUpdate(); // Updating sensor with current values
  
  float aX, aY, aZ, aX2, aY2, aZ2, tremor;

  // Getting accelerometer values in each direction
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  aZ = mySensor.accelZ();

  // Taking the square of each value
  aX2 = pow(aX, 2);
  aY2 = pow(aY, 2);
  aZ2 = pow(aZ, 2);

  tremor = sqrt(aX2 + aY2 + aZ2) - 1.07;  // Calculating a 3D vector for the tremor acceleration using the Pythagoran theorem and a centralizing constant
  return tremor;
}

//Function for setting the speed of the motor, using different intervals of tremor values
int SetMotorSpeed (float val) {
  if (val < 4) {
    int s = 0;
    return s;
  }
  if (val >= 4 && val < 5) {
    int s = 60;
    return s;
  }
  if (val >= 5 && val < 6) {
    int s = 80;
    return s;
  }
  if (val >= 6 && val < 7) {
    int s = 100;
    return s;
  }
  if (val >= 6 && val < 7) {
    int s = 120;
    return s;
  }
  if (val >= 7 && val < 8) {
    int s = 140;
    return s;
  }
  if (val >= 8 && val < 9) {
    int s = 160;
    return s;
  }
  if (val >= 9) {
    int s = 180;
    return s;
  }
}
