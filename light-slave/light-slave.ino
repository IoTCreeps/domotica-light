int AC_LOAD = 3;    // Output to Opto Triac pin
int dimming = 20;  // Dimming level (0-128)  0 = ON, 128 = OFF

void setup() {
  Serial.begin(9600);
  pinMode(AC_LOAD, OUTPUT);
  attachInterrupt(0, zero_crosss_int, RISING);
}

void loop() {
   if (Serial.available()) {  
      String data = Serial.readStringUntil('\n');
      setDimmingFromData(data);
   }
}

void setDimmingFromData(String data) {
  int dimmingFromBluetooth = data.toInt();
  if(dimmingFromBluetooth > 0 && dimmingFromBluetooth < 128){
    dimming = dimmingFromBluetooth;
  }
}

void zero_crosss_int() {
  int dimtime = (65*dimming);    // For 60Hz =>65    
  delayMicroseconds(dimtime);    // Wait till firing the TRIAC    
  digitalWrite(AC_LOAD, HIGH);   // Fire the TRIAC
  delayMicroseconds(8.33);         // triac On propogation delay 
  digitalWrite(AC_LOAD, LOW);    // No longer trigger the TRIAC (the next zero crossing will swith it off) TRIAC
}

