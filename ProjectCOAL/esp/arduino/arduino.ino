void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  // Initialize your sensor here if needed
}

void loop() {
  // Read sensor data (replace this with your actual sensor reading code)
  int sensorValue = analogRead(A0); // Assuming sensor is connected to A0
  
  // Send sensor value via serial
  Serial.println(sensorValue); // Sending sensor value over serial
  delay(5000); // Delay for 5 seconds before sending the next reading
}
