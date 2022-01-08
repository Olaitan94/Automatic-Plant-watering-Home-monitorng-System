void setup() {
  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
  int pump = 0;
}


void loop() {
  int mode_pin = 5;  //variable for the digital pin which will control the pump operation.
  pinMode(mode_pin, INPUT);
  int pump_control = 8;
  pinMode(pump_control,OUTPUT);
  
  int pump = digitalRead(mode_pin);

  if (pump == HIGH) {
    digitalWrite(pump_control, HIGH); 
    Serial.println("pump on");
  }

  else {
    digitalWrite(pump_control, LOW);
    Serial.println("Off");
  }
  
}
