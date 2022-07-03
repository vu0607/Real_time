#include <Wire.h>
#include <mpu6050.h>
MPU6050 mpu6050;

#define TRIG_PIN 3
#define ECHO_PIN 2
#define TIME_OUT 3000
#define MOTOR_A_IN1  4
#define MOTOR_A_IN2  5
#define MOTOR_B_IN2  6
#define MOTOR_B_IN1  8

#define PID_K_p 1
#define PID_K_i  0.02
#define PID_K_d  0.02

float i_input;
float d_last;
float target_dir;
//khoi tao DC
void motor_begin() {
  analogWrite(MOTOR_A_IN2, 0);
  analogWrite(MOTOR_B_IN2, 0);

  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);


  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);


  Serial.println("Motors : ok");
}

//Set toc do cho DC A
void motor_A_set( int speed ) {
  if ( speed == 0 ) {
    digitalWrite( MOTOR_A_IN1, HIGH );
    digitalWrite( MOTOR_A_IN2, HIGH );
  } else if ( speed > 0 ) {
    digitalWrite( MOTOR_A_IN1, HIGH );
    analogWrite( MOTOR_A_IN2, speed );

  } else {
    digitalWrite( MOTOR_A_IN1, LOW );
    analogWrite( MOTOR_A_IN2, 255 - speed );
  }
}
//Set toc do cho DC B
void motor_B_set( int speed ) {
  if ( speed == 0 ) {
    digitalWrite( MOTOR_B_IN1, HIGH );
    digitalWrite( MOTOR_B_IN2, HIGH );
  } else if ( speed > 0 ) {
    digitalWrite( MOTOR_B_IN1, HIGH );
    analogWrite( MOTOR_B_IN2, speed);
  } else {
    digitalWrite( MOTOR_B_IN1, LOW );
    analogWrite( MOTOR_B_IN2, 255 - speed  );
  }
}
// Set chay thang
void motor_forward(int delta)
{
  if (delta > 0)
  {
    motor_A_set(171);
    motor_B_set(175);
    delay(2);
  }
  else
  {
    motor_A_set(169);
    motor_B_set(176);
    delay(3);
  }
}
// khoi tao mpu6050
void mpu6050_begin()  {
  Wire.begin();
  Serial.print("MPU6050: Starting calibration; leave device flat and still ... ");
  int error = mpu6050.begin();
  Serial.println(mpu6050.error_str(error));
}
//doc gia tri truc dz
float mpu6050_yaw() {
  MPU6050_t data = mpu6050.get();
  while ( data.dir.error != 0 ) {
    // I suffer from a lot of I2C problems
    Serial.println(mpu6050.error_str(data.dir.error));
    // Reset I2C
    TWCR = 0; Wire.begin();
    // Reread
    data = mpu6050.get();
  }
  return data.dir.yaw;
}
// khoi tao PID
void pid_begin() {
  i_input = 0;
  d_last = 0;
  Serial.println("PID    : ok");
}
//tinh toan PID
int pid(float error) {
  float p_input;
  float d_input;

  p_input = error;
  i_input = constrain(i_input + error, -50, +50);
  d_input = error - d_last; d_last = error;

  return p_input * PID_K_p + i_input * PID_K_i + d_input * PID_K_d;
}
// DO KHOANG CACH
float GetDistance()
{
  long duration, distanceCm;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);

  // convert to distance
  distanceCm = duration / 29.1 / 2;
  
    return distanceCm;
  }
uint8_t i = 0;
// DOC ZONE
void zone()
{
  int giatri = analogRead(A0);
  //Serial.println(giatri);
  if (analogRead(A0) > 500)
  {
    i++;
    while (analogRead(A0) > 500){GetDistance(); Serial.print("//");}
    if (i > 5) i = 0;
  }
  Serial.println(i);
}


  void setup() {
    Serial.begin(115200);
    Serial.println("\n\nWelcome at PID robot");
    motor_begin();
    pid_begin();
    mpu6050_begin();
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
  }
  void loop()
  {
    float current_dir;
    int steer;
    current_dir = mpu6050_yaw();
    //  Serial.print(" dir="); Serial.print(current_dir, 2);
    //  Serial.print(" tgt="); Serial.print(target_dir, 2);
    steer = pid( target_dir - current_dir );
      Serial.print(" steer="); Serial.println(steer);
    motor_forward(steer);
    long distance = GetDistance();

    if (distance <= 0)
    {
      Serial.println("Echo time out !!");
    }
    else
    {
      Serial.print("Distance to nearest obstacle (cm): ");
      Serial.println(distance);
    }
    zone();
  }
