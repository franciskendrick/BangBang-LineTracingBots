/*
  Microcontroller: Arduino UNO R3
  Motor Driver: L298N
  DC Motor: TT Motor
  No. of DC Motors: 2
  IR Sensor: 5 channel array
  Ideal Voltage: 8v
*/

// Initialize right motors
const int PWM_right = 10;
const int motor_RB = 9;
const int motor_RF = 8;

// Initialize left motors
const int PWM_left = 5;
const int motor_LB = 6;
const int motor_LF = 7;

// Initialize variables
String prev_move = "R";

const int normal_Fspeed = 140;  // normal forward
const int slow_Fspeed = 120;    // slow forward
const int normal_Pspeed = 125;  // normal pivot 
const int fast_Pspeed = 145;    // fast pivot
const int normal_Tspeed = 150;  // normal turn

void setup() {
  Serial.begin(9600);

  // Set motor pins as OUTPUT
  pinMode(motor_RF, OUTPUT);
  pinMode(motor_RB, OUTPUT);
  pinMode(motor_LF, OUTPUT);
  pinMode(motor_LB, OUTPUT);
}

void loop() {
  // Read values from IR sensors
  int IR_LL = digitalRead(A0);
  int IR_L = digitalRead(A1);
  int IR_C = digitalRead(A2); 
  int IR_R = digitalRead(A3);
  int IR_RR = digitalRead(A4);

  // Line following logic
  // 1 = White; 0 = Black

  // Center Sensor
  if (IR_C == 0) {
    if (IR_L == 1 && IR_R == 1) {
      forward();
    } else {
      slowforward();
    }
  }
  // Left Sensor
  else if (IR_LL == 0 || IR_L == 0) {
    prev_move = "L";
    if (IR_LL == 0 && IR_L == 1) {
      fastleft_pivot();
    } else if (IR_LL == 1 && IR_L == 0) {
      left_pivot();
    } else {
      left_pivot();
    }
  }
  // Right Sensor
  else if (IR_RR == 0 || IR_R == 0) {
    prev_move = "R";
    if (IR_RR == 0 && IR_R == 1) {
      fastright_pivot();
    } else if (IR_RR == 1 && IR_R == 0) {
      right_pivot();
    } else {
      right_pivot();
    }
  }
  // All white
  if (IR_LL == 1 && IR_L == 1 && IR_C == 1 && IR_R == 1 && IR_RR == 1) {
    if (prev_move == "L") {
      left_normal();
    } else if (prev_move == "R") {
      right_normal();
    }
  }

  // Serial output for debugging
  Serial.print("IR_LL: ");
  Serial.print(IR_LL);
  Serial.print(" IR_L: ");
  Serial.print(IR_L);
  Serial.print(" IR_C: ");
  Serial.print(IR_C);
  Serial.print(" IR_R: "); 
  Serial.print(IR_R);
  Serial.print(" IR_RR: "); 
  Serial.println(IR_RR);
}

void stop() {
  // Stop all motors
  digitalWrite(motor_RF, LOW);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, LOW);
  digitalWrite(motor_LB, LOW);

  // Set PWM values to 0
  analogWrite(PWM_right, 0);
  analogWrite(PWM_left, 0);
}

void forward() {
  // Move forward
  digitalWrite(motor_RF, HIGH);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, HIGH);
  digitalWrite(motor_LB, LOW);

  // Set PWM values for forward motion
  analogWrite(PWM_right, normal_Fspeed);
  analogWrite(PWM_left, normal_Fspeed);
}

void slowforward() {
  // Move forward
  digitalWrite(motor_RF, HIGH);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, HIGH);
  digitalWrite(motor_LB, LOW);

  // Set PWM values for slow forward motion
  analogWrite(PWM_right, slow_Fspeed);
  analogWrite(PWM_left, slow_Fspeed);
}

void left_pivot() {
  // Turn left
  digitalWrite(motor_RF, HIGH);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, LOW);
  digitalWrite(motor_LB, LOW);

  // Set PWM values for left pivot
  analogWrite(PWM_right, normal_Pspeed);
  analogWrite(PWM_left, normal_Pspeed);
}

void fastleft_pivot() {
  // Turn left
  digitalWrite(motor_RF, HIGH);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, LOW);
  digitalWrite(motor_LB, LOW);

  // Set PWM values for fast left pivot
  analogWrite(PWM_right, fast_Pspeed);
  analogWrite(PWM_left, fast_Pspeed);
}

void left_normal() {
  // Turn left
  digitalWrite(motor_RF, HIGH);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, LOW);
  digitalWrite(motor_LB, HIGH);

  // Set PWM values for normal left turn
  analogWrite(PWM_right, normal_Tspeed);
  analogWrite(PWM_left, normal_Tspeed);
}

void right_pivot() {
  // Turn right
  digitalWrite(motor_RF, LOW);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, HIGH);
  digitalWrite(motor_LB, LOW);

  // Set PWM values for right pivot
  analogWrite(PWM_right, normal_Pspeed);
  analogWrite(PWM_left, normal_Pspeed);
}

void fastright_pivot() {
  // Turn right
  digitalWrite(motor_RF, LOW);
  digitalWrite(motor_RB, LOW);
  digitalWrite(motor_LF, HIGH);
  digitalWrite(motor_LB, LOW);

  // Set PWM values for fast right pivot
  analogWrite(PWM_right, fast_Pspeed);
  analogWrite(PWM_left, fast_Pspeed);
}

void right_normal() {
  // Turn right
  digitalWrite(motor_RF, LOW);
  digitalWrite(motor_RB, HIGH);
  digitalWrite(motor_LF, HIGH);
  digitalWrite(motor_LB, LOW);

  // Set PWM values for normal right turn
  analogWrite(PWM_right, normal_Tspeed);
  analogWrite(PWM_left, normal_Tspeed);
}
