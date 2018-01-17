/*
 ==============================================================================
 
 SequenceRegion.cpp
 Created: 3 Dec 2016 10:53:41am
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "SequenceRegion.h"
#include "MainComponent.h"


SequenceRegion::SequenceRegion()
{
    
}

SequenceRegion::~SequenceRegion()
{
    
}

void SequenceRegion::paint(Graphics& g)
{
    g.setColour (Colours::green);
    g.drawRect(0, 0, getWidth(), getHeight());
    g.setColour (Colours::orange);
    g.fillRect(2, 2, getWidth()-3, getHeight()-3);
}




