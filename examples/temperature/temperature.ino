#include "thermistor.h"

Thermistor *thermistor;

void setup() {
  Serial.begin(9600);

  /*
  * arg 1: pin: Analog pin
  * arg 2: vcc: Input voltage
  * arg 3: analogReference: reference voltage. Typically the same as vcc, but not always (ie ESP8266=1.0)
  * arg 4: adcMax: The maximum analog-to-digital convert value returned by analogRead (1023 or 4095)
  * arg 5: seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
  * arg 6: thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
  * arg 7: temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
  * arg 8: bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
  * arg 9: samples: Number of analog samples to average (for smoothing)
  * arg 10: sampleDelay: Milliseconds between samples (for smoothing)
  */

  // For 5V Arduino
  thermistor = new Thermistor(A0, 5.0, 5.0, 1023, 10000, 10000, 25, 3950, 5, 20);

  // For 3.3V Arduino
  //thermistor = new Thermistor(A0, 3.3, 3.3, 1023, 10000, 10000, 25, 3950, 5, 20);

  // For Particle Photon, Electron, etc
  //thermistor = new Thermistor(A0, 3.3, 3.3, 4095, 10000, 10000, 25, 3950, 5, 20);

  // For ESP8266 (a 10k series resistor is usually too low in this setup)
  //thermistor = new Thermistor(A0, 3.3, 1.0, 1023, 47000, 10000, 25, 3950, 5, 20);

  // For ESP8266 with improved temperature resolution...
  // Use a 1:1 voltage divider for Vcc and 47k + 10k as series resistors
  //thermistor = new Thermistor(A0, 1.65, 1.0, 1023, 57000, 10000, 25, 3950, 5, 20);
}

void loop() {
  double tempF = thermistor->readTempF();
  Serial.println("tempF=" + String(tempF));
  delay(5000);
}
