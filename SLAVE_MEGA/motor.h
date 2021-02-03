class Motor{
  private:
    uint8_t input_1, pwm_pin, input_2;
  public:
  Motor(){};
    Motor( int pwm_pin,int input_1, int input_2 = 100) {
      this->input_1 = input_1;
      this->input_2 = input_2;
      this->pwm_pin = pwm_pin;
      pinMode(input_1, OUTPUT);
      pinMode(input_2, OUTPUT);
      pinMode(pwm_pin, OUTPUT);
    }
    void clk(uint8_t pwm) {
      digitalWrite(input_1, HIGH);
      digitalWrite(input_2, LOW);
      analogWrite(pwm_pin, pwm);
    }
    void aclk(uint8_t pwm) {
      digitalWrite(input_1, LOW);
      digitalWrite(input_2, HIGH);
      analogWrite(pwm_pin, pwm);
    }
    void brake() {
      digitalWrite(input_1, HIGH);
      digitalWrite(input_2, HIGH);
      analogWrite(pwm_pin, 0);
    }
    void brakeCytron() {
      digitalWrite(input_1, LOW);
      analogWrite(pwm_pin, 0);
    }
};
