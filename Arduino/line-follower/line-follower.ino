#define IR1 13 // D7
#define IR2 12 // D6
// 12 // D6
// 13 // D7
// 14 // D5
// 15 // D8

#define MOTOR_L_PWM 4
#define MOTOR_L_IN1 2
#define MOTOR_L_IN2 16

#define MOTOR_R_PWM 5
#define MOTOR_R_IN1 0
#define MOTOR_R_IN2 17

#define MOTORS_ENABLE 32

#define SPEED_MAX 140

#ifdef ARDUINO_ARCH_ESP32
#include <pwmWrite.h>
#endif

Pwm pwm = Pwm();

class Motor {
  public:
    Motor(uint8_t, uint8_t, uint8_t);
    Motor(uint8_t, uint8_t, uint8_t, bool);
    void forward(uint16_t);
    void reverse(uint16_t);
    void stop();
  protected:
    void set_speed(uint16_t);
    uint8_t pwm_pin, in1_pin, in2_pin;
    bool inv;
};

Motor::Motor(uint8_t in_pwm, uint8_t in1, uint8_t in2) {
  Motor(in_pwm, in1, in2, 0);
}

Motor::Motor(uint8_t in_pwm, uint8_t in1, uint8_t in2, bool inverse) {
  pwm_pin = in_pwm;
  in1_pin = in1;
  in2_pin = in2;
  inv = inverse;
  pinMode(in1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);
  this->stop();
}

void Motor::set_speed(uint16_t speed) {
#ifdef ARDUINO_ARCH_ESP32
  pwm.write(pwm_pin, speed > 255 ? 255 : speed);
#else
  analogWrite(pwm_pin, speed > 255 ? 255 : speed);
#endif
}

void Motor::forward(uint16_t speed) {
  digitalWrite(in1_pin, inv ? HIGH : LOW);
  digitalWrite(in2_pin, inv ? LOW : HIGH);
  this->set_speed(speed);
}

void Motor::reverse(uint16_t speed) {
  digitalWrite(in1_pin, inv ? LOW : HIGH);
  digitalWrite(in2_pin, inv ? HIGH : LOW);
  this->set_speed(speed);
}

void Motor::stop() {
  this->set_speed(0);
}

Motor left(MOTOR_L_PWM, MOTOR_L_IN1, MOTOR_L_IN2, true);
Motor right(MOTOR_R_PWM, MOTOR_R_IN1, MOTOR_R_IN2, true);

void setup() {
  Serial.begin(115200);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  delay(1000);
  
  pinMode(MOTORS_ENABLE, OUTPUT);
  digitalWrite(MOTORS_ENABLE, HIGH);
}

void loop() {
  uint16_t ir1 = analogRead(IR1);
  uint16_t ir2 = analogRead(IR2);

  if ((ir1 < 500) && (ir2 < 500)) {
    // both sensors are on white
    left.forward(SPEED_MAX);
    right.forward(SPEED_MAX);
    
  } else if (ir1 < 500) {
    // left sensor is on white, right is on the line
    left.forward(SPEED_MAX);
    right.reverse(SPEED_MAX/1.3);
    
  } else if (ir2 < 500) {
    // right sensor is on white, left is on the line
    left.reverse(SPEED_MAX/1.3);
    right.forward(SPEED_MAX);
    
  } else {
    // both sensors are on black, stop
    left.stop();
    right.stop();
  }
}
