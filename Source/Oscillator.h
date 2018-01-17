/*
 ==============================================================================
 
 Oscillator.h
 Created: 19 Jan 2017 6:00:13pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

/**
 Class for a generic oscillator
 */


class Oscillator
{
public:
    //==============================================================================
    /**
     SinOscillator constructor
     */
    Oscillator();
    
    /**
     SinOscillator destructor
     */
    virtual ~Oscillator();
    
    /**
     sets the frequency of the oscillator
     */
    void setFrequency (float freq);
    
    /**
     sets frequency using a midi note number
     */
    void setNote (int noteNum);
    
    /**
     sets the amplitude of the oscillator
     */
    void setAmplitude (float amp);
    
    /**
     resets the oscillator
     */
    void reset();
    
    /**
     sets the sample rate
     */
    void setSampleRate (float sr);
    
    /**
     Returns the next sample
     */
    float nextSample();
    
    /**
     function that provides the execution of the waveshape
     */
    virtual float renderWaveShape (const float currentPhase) = 0;
    
private:
    float frequency;
    float amplitude;
    float sampleRate;
    float phase;
    float phaseInc;
};



#endif  // OSCILLATOR_H_INCLUDED
