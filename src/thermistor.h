/*
  thermistor.cpp - Universal Thermistor Library

  Copyright (c) 2018 Paul Cowan <paul@monospacesoftware.com>
  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef UNIVERSAL_THERMISTOR_H
#define UNIVERSAL_THERMISTOR_H

#include <math.h>

#ifdef PARTICLE
  #include "application.h"
#else
  #include <arduino.h>
#endif

class Thermistor {
  protected:
    const int _pin;
    const double _vcc;
    const double _analogReference;
    const double _adcMax;
    const double _seriesResistor;
    const double _thermistorNominal;
    const double _temperatureNominal;
    const double _bCoef;
    const int _samples;
    const int _sampleDelay;
    const bool _thermistorFirst;
  public:

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
    Thermistor(int pin, double vcc, double analogReference, int adcMax, int seriesResistor, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay);
    
    /*
    * arg 11: boolean indicating that the thermistor is first in series
    */
    Thermistor(int pin, double vcc, double analogReference, int adcMax, int seriesResistor, int thermistorNominal, int temperatureNominal, int bCoef, int samples, int sampleDelay, bool thermistorFirst);

    // Smoothed ADC value
    double readADC() const;

    // Temperature in Kelvin
    double readTempK() const;

    // Temperature in Celsius
    double readTempC() const;

    // Temperature in Fahrenheit
    double readTempF() const;

    // convert ADC value to Kelvin
    double adcToK(double adc) const;

    // convert Kelvin to Celsius
    double kToC(double k) const;

    // convert Celsius to Fahrenheit
    double cToF(double c) const;

    // Resistance of the thermistor
    double getResistance() const;

    // Convert ADC value to resistance
    double adcToR(double adc) const;

    // Voltage between the voltage divider
    double getVoltage() const;

    // Convert ADC value to voltage
    double adcToV(double adc) const;
};

#endif
