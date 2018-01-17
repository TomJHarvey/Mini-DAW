/*
 ==============================================================================
 
 SquareOscillator.cpp
 Created: 19 Jan 2017 6:00:23pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "SquareOscillator.h"



SquareOscillator::SquareOscillator()
{
    
}
SquareOscillator::~SquareOscillator()
{
    
}

float SquareOscillator::renderWaveShape (const float currentPhase)
{
    
    
    if (currentPhase <= M_PI)
        return 0.5;
    else
        return -0.5;
    
}
