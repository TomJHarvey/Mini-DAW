/*
 ==============================================================================
 
 noteRegion.cpp
 Created: 3 Dec 2016 10:42:22am
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "noteRegion.h"
#include "PianoRoll.h"


NoteRegion::NoteRegion()
{
    listener = nullptr;
}

NoteRegion::~NoteRegion()
{
    
}

void NoteRegion::paint(Graphics& g)
{
    g.setColour (Colours::green);
    g.drawRect(0, 0, getWidth(), getHeight());
    g.setColour (Colours::pink);
    g.fillRect(1, 1, getWidth()- 2, getHeight() - 2);
}



