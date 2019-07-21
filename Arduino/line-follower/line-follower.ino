#define IR1 14 // D5
#define IR2 12 // D6
// 13 // D7
// 15 // D8

#define MOTOR_L_PWM 5 // D1
#define MOTOR_L_DIR 0 // D3
#define MOTOR_R_PWM 4 // D2
#define MOTOR_R_DIR 2 // D4

#define SPEED_MAX 1023

int ir1, ir2;

class Motor {
  public:
    Motor(uint8_t, uint8_t);
    Motor(uint8_t, uint8_t, bool);
    void forward(uint16_t);
    void reverse(uint16_t);
    void stop();
  protected:
    void set_speed(uint16_t);
    uint8_t pwm_pin, dir_pin;
    bool inverse;
};

Motor::Motor(uint8_t pwm, uint8_t direction) {
  Motor(pwm, direction, 0);
}

Motor::Motor(uint8_t pwm, uint8_t direction, bool inverse) {
  pwm_pin = pwm;
  dir_pin = direction;
  inverse = inverse;
  pinMode(pwm_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  this->stop();
}

void Motor::set_speed(uint16_t speed) {
  analogWrite(pwm_pin, speed > 1023 ? 1023 : speed);
}

void Motor::forward(uint16_t speed) {
  digitalWrite(dir_pin, inverse ? HIGH : LOW);
  this->set_speed(speed);
}

void Motor::reverse(uint16_t speed) {
  digitalWrite(dir_pin, inverse ? LOW : HIGH);
  this->set_speed(speed);
}

void Motor::stop() {
  this->set_speed(0);
}

Motor left(MOTOR_L_PWM, MOTOR_L_DIR, 0);
Motor right(MOTOR_L_PWM, MOTOR_L_DIR, 1);

void setup() {
  Serial.begin(115200);
  
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
}

void loop() {
  ir1 = analogRead(IR1);
  ir2 = analogRead(IR2);

  Serial.print("IR1: ");
  Serial.print(ir1);
  Serial.print(", IR2: ");
  Serial.println(ir2);

  if ((ir1 < 500) && (ir2 < 500)) {
    left.forward(1023);
    right.forward(1023);
  } else {
    left.stop();
    right.stop();
  }

  delay(100);
}
