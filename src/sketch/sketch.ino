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
char serial_input[5];

boolean toggle1 = 0;

void setup()
{
    
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  // TODO remove
  pinMode (13, OUTPUT);
  
  cli();
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 4000;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  //OCR1A = (16 * 10^6) / (2 * 1024) - 1;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();

  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect){
  stop();
}

void move()
{
  digitalWrite(13, HIGH);
  TCNT1  = 0;
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
  analogWrite(ENB, right_wheel_speed);
}

void stop() 
{
  digitalWrite(13, LOW);
  left_wheel_direction = right_wheel_direction = 'n';
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
}

void loop()
{
  int result = 0;
  if( Serial.available() ) {
    result = Serial.readBytesUntil('e', serial_input, 5);
  }

  if (result != 0) {
    left_wheel_direction = serial_input[0];
    right_wheel_direction = serial_input[2];

    left_wheel_speed = serial_input[1];
    right_wheel_speed = serial_input[3];
    if ((left_wheel_direction == 'f' || left_wheel_direction == 'b') && (right_wheel_direction == 'f' || right_wheel_direction == 'b')) {
      move();
    }
    result = 0;
    serial_input[0] = '\0';
  }
  delay(20);
}
