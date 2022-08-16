// Motor driver type (one must be uncommented only)
#define L293DD
// #define TB6612

// Pins configuration
#ifdef ARDUINO_ARCH_ESP32
// Pins configuration for ESP32
#define IR1 13
#define IR2 12

#if defined(TB6612)
#define MOTOR_L_PWM 4
#define MOTOR_L_IN1 2
#define MOTOR_L_IN2 16

#define MOTOR_R_PWM 5
#define MOTOR_R_IN1 0
#define MOTOR_R_IN2 17

#define MOTORS_ENABLE 32
#else
#error "Selected motor driver not supported on ESP32"
#endif

#define SPEED_MAX 140
#else
// Pins configuration for ESP8266
#define IR1 14 // D5
#define IR2 12 // D6

#if defined(L293DD)
#define MOTOR_L_PWM 5 // D1
#define MOTOR_L_DIR 0 // D3
#define MOTOR_R_PWM 4 // D2
#define MOTOR_R_DIR 2 // D4
#else
#error "Selected motor driver not supported on ESP32"
#endif

#define SPEED_MAX 1023
#endif

#ifdef ARDUINO_ARCH_ESP32
#include <pwmWrite.h>
Pwm pwm = Pwm();
#endif

class MotorL293DD {
  public:
    MotorL293DD(uint8_t, uint8_t);
    MotorL293DD(uint8_t, uint8_t, bool);
    void forward(uint16_t);
    void reverse(uint16_t);
    void stop();
  protected:
    void set_speed(uint16_t);
    uint8_t pwm_pin, dir_pin;
    bool inv;
};

MotorL293DD::MotorL293DD(uint8_t pwm, uint8_t direction) {
  MotorL293DD(pwm, direction, 0);
}

MotorL293DD::MotorL293DD(uint8_t pwm, uint8_t direction, bool inverse) {
  pwm_pin = pwm;
  dir_pin = direction;
  inv = inverse;
  pinMode(pwm_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  this->stop();
}

void MotorL293DD::set_speed(uint16_t speed) {
  analogWrite(pwm_pin, speed > 1023 ? 1023 : speed);
}

void MotorL293DD::forward(uint16_t speed) {
  digitalWrite(dir_pin, inv ? HIGH : LOW);
  this->set_speed(speed);
}

void MotorL293DD::reverse(uint16_t speed) {
  digitalWrite(dir_pin, inv ? LOW : HIGH);
  this->set_speed(speed);
}

void MotorL293DD::stop() {
  this->set_speed(0);
}

class MotorTB6612 {
  public:
    MotorTB6612(uint8_t, uint8_t, uint8_t);
    MotorTB6612(uint8_t, uint8_t, uint8_t, bool);
    void forward(uint16_t);
    void reverse(uint16_t);
    void stop();
  protected:
    void set_speed(uint16_t);
    uint8_t pwm_pin, in1_pin, in2_pin;
    bool inv;
};

MotorTB6612::MotorTB6612(uint8_t in_pwm, uint8_t in1, uint8_t in2) {
  MotorTB6612(in_pwm, in1, in2, 0);
}

MotorTB6612::MotorTB6612(uint8_t in_pwm, uint8_t in1, uint8_t in2, bool inverse) {
  pwm_pin = in_pwm;
  in1_pin = in1;
  in2_pin = in2;
  inv = inverse;
  pinMode(in1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);
  this->stop();
}

void MotorTB6612::set_speed(uint16_t speed) {
#ifdef ARDUINO_ARCH_ESP32
  pwm.write(pwm_pin, speed > 255 ? 255 : speed);
#else
  analogWrite(pwm_pin, speed > 255 ? 255 : speed);
#endif
}

void MotorTB6612::forward(uint16_t speed) {
  digitalWrite(in1_pin, inv ? HIGH : LOW);
  digitalWrite(in2_pin, inv ? LOW : HIGH);
  this->set_speed(speed);
}

void MotorTB6612::reverse(uint16_t speed) {
  digitalWrite(in1_pin, inv ? LOW : HIGH);
  digitalWrite(in2_pin, inv ? HIGH : LOW);
  this->set_speed(speed);
}

void MotorTB6612::stop() {
  this->set_speed(0);
}

#if defined(L293DD)
MotorL293DD left(MOTOR_L_PWM, MOTOR_L_DIR, false);
MotorL293DD right(MOTOR_R_PWM, MOTOR_R_DIR, true);
#elif defined(TB6612)
MotorTB6612 left(MOTOR_L_PWM, MOTOR_L_IN1, MOTOR_L_IN2, true);
MotorTB6612 right(MOTOR_R_PWM, MOTOR_R_IN1, MOTOR_R_IN2, true);
#else
#error "Selected motor driver not supported"
#endif

void setup() {
  Serial.begin(115200);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
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
