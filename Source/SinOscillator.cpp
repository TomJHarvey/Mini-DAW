/*
 *  SinOscillator.cpp
 *  sdaAudioMidi
 *
 *  Created by tjmitche on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SinOscillator.h"
#include <cmath>

SinOscillator::SinOscillator()
{
    reset();
}

SinOscillator::~SinOscillator()
{
    
}


float SinOscillator::renderWaveShape (const float currentPhase)
{
    return sin (currentPhase);
}
