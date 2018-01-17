/*
 ==============================================================================
 
 SawOscillator.h
 Created: 19 Jan 2017 6:00:30pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef SAWOSCILLATOR_H_INCLUDED
#define SAWOSCILLATOR_H_INCLUDED

#include "Oscillator.h"



/**
 Class for a Saw oscillator
 */
class SawOscillator:
public Oscillator
{
    
public:
    
    
    /**
     SawOscillator constructor
     */
    SawOscillator();
    
    /**
     SawOscillator destructor
     */
    ~SawOscillator();
    
    virtual float renderWaveShape (const float currentPhase) override;
    
private:
    
};



#endif  // SAWOSCILLATOR_H_INCLUDED
