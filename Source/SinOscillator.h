/*
 *  SinOscillator.h
 *  sdaAudioMidi
 *
 *  Created by tjmitche on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef H_SINOSCILLATOR
#define H_SINOSCILLATOR

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

/**
 Class for a sinewave oscillator
 */

class SinOscillator:
public Oscillator
{
public:
    //==============================================================================
    /**
     SinOscillator constructor
     */
    SinOscillator();
    
    /**
     SinOscillator destructor
     */
    ~SinOscillator();
    
    virtual float renderWaveShape (const float currentPhase) override;
    
private:
    float frequency;
    float amplitude;
    float sampleRate;
    float phase;
    float phaseInc;
};

#endif //H_SINOSCILLATOR
