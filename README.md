# universal-thermistor
A fully configurable NTC thermistor library.

Most thermistor libraries make assumptions about input voltage, analog reference voltage, or the max ADC value.
This library allows configuration of all inputs to the Steinhart–Hart equation including Vcc, reference voltage, and max ADC.
This makes it particularly useful for devices that do not fit the typical Arduino profile such as:

* Particle Photon: vcc and analogRef are 3.3 but adcMax is 4095
* ESP8266: vcc is 3.3 but analogRef is usually 1.0

This library is based on [photon-thermistor](https://github.com/kegnet/photon-thermistor) but simplified somewhat to be less Particle-centric.

### Hookup

See https://learn.adafruit.com/thermistor/using-a-thermistor

![Breadboard Hookup](https://raw.githubusercontent.com/kegnet/universal-thermistor/master/breadboard_hookup.png)

### Configuration

Configuration is done via constructor parameters as follows:

```
1. pin: Analog pin
2: vcc: Input voltage (3.3, 5, or something else if you're using a voltage divider)
3: analogReference: reference voltage. Typically the same as vcc, but not always (ie ESP8266=1.0)
4: adcMax: The maximum analog-to-digital convert value returned by analogRead (1023 or 4095)
5: seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
6: thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
7: temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
8: bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
9: samples: Number of analog samples to average (for smoothing)
10: sampleDelay: Milliseconds between samples (for smoothing)

Thermistor(int pin, float vcc, float analogReference, int adcMax, int seriesResistor, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay)
```

### Example
```
#include "thermistor.h"

Thermistor *thermistor;

void setup() {
  Serial.begin(9600);
  thermistor = new Thermistor(A0, 3.3, 3.3, 1023, 10000, 10000, 25, 3950, 5, 20);
}

void loop() {
  double tempF = thermistor->readTempF();
  Serial.println("tempF=" + String(tempF));
  delay(5000);
}
```

### Troubleshooting

* If the temperature reported by the thermistor is a very small negative number, around -140, the circuit is open or thermistor is not connected.
* If the temperature reported by the thermistor is a very high number, such as 650, the thermistor is likely connected without the series resistor.
* Be sure your connection is Vcc -> seriesResistor -> thermistor -> ground, and your A0 pin is connect between seriesResistor and thermistor. It will not work otherwise.


