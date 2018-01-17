/*
 ==============================================================================
 
 Oscillator.cpp
 Created: 19 Jan 2017 6:00:13pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "Oscillator.h"

#include <cmath>

Oscillator::Oscillator()
{
    reset();
}

Oscillator::~Oscillator()
{
    
}

void Oscillator::setFrequency (float freq)
{
    frequency = freq;
    phaseInc = (2 * M_PI * frequency ) / sampleRate ;
}

void Oscillator::setNote (int noteNum)
{
    setFrequency (440.f * pow (2, (noteNum - 69) / 12.0));
}

void Oscillator::setAmplitude (float amp)
{
    amplitude = amp;
}

void Oscillator::reset()
{
    phase = 0.f;
    sampleRate = 44100;
    setFrequency (440.f);
    setAmplitude (0.f);
}

void Oscillator::setSampleRate (float sr)
{
    sampleRate = sr;
    setFrequency (frequency );
}

float Oscillator::nextSample()
{
    float out = renderWaveShape (phase ) * amplitude ;
    phase = phase + phaseInc ;
    if(phase  > (2.f * M_PI))
        phase -= (2.f * M_PI);
    
    return out;
}
