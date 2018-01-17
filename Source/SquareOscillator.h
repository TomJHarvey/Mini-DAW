/*
 ==============================================================================
 
 SquareOscillator.h
 Created: 19 Jan 2017 6:00:23pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef SQUAREOSCILLATOR_H_INCLUDED
#define SQUAREOSCILLATOR_H_INCLUDED

#include "Oscillator.h"

/**
 Class for a SquareWave oscillator
 */

class SquareOscillator:
public Oscillator
{
    
public:
    /**
     SquareOscillator constructor
     */
    SquareOscillator();
    
    /**
     SquareOscillator destructor
     */
    ~SquareOscillator();
    
    virtual float renderWaveShape (const float currentPhase) override;
    
private:
    
    
    
};



#endif  // SQUAREOSCILLATOR_H_INCLUDED
