// Motors driver ports
int ENA = 11;
int IN1 = 10;
int IN2 = 9;

int ENB = 3;
int IN3 = 5;
int IN4 = 4;

// global control params
char left_wheel_direction, right_wheel_direction;
int left_wheel_speed, right_wheel_speed;
char serial_input[10];

void setup()
{
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  Serial.begin(9600);
}

void move()
{
  if (left_wheel_direction == 'f') {
    digitalWrite (IN1, HIGH);
    digitalWrite (IN2, LOW);
  } else if (left_wheel_direction == 'b') {
    digitalWrite (IN1, LOW);
    digitalWrite (IN2, HIGH);
  } else {
    digitalWrite (IN1, LOW);
    digitalWrite (IN2, LOW);
  }

  if (right_wheel_direction == 'f') {
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW);
  } else if (right_wheel_direction == 'b') {
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, HIGH);
  } else {
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, LOW);
  }

  analogWrite(ENA, left_wheel_speed);
  analogWrite(ENB, left_wheel_speed);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
}

void loop()
{
  int result;
  if( Serial.available() ) {
    result = Serial.readBytesUntil('\n', serial_input, 5);
  }

  if (result != 0) {
    Serial.write(serial_input);
    left_wheel_direction = serial_input[0];
    right_wheel_direction = serial_input[2];

    left_wheel_speed = serial_input[1];
    right_wheel_speed = serial_input[3];

    move();
    delay(500);
    stop();
  }
}
