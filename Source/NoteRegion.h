/*
 ==============================================================================
 
 noteRegion.h
 Created: 3 Dec 2016 10:42:22am
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef NOTEREGION_H_INCLUDED
#define NOTEREGION_H_INCLUDED
#include "Region.h"
#include "../JuceLibraryCode/JuceHeader.h"


/**
 Class for a note region
 */

class NoteRegion:
public Region

{
public:
    
    /**
     NoteRegion constructor
     */
    NoteRegion();
    
    /**
     NoteRegion deconstructor
     */
    
    ~NoteRegion();
    
    /** Colours the NoteRegion background
     */
    
    void paint (Graphics&) override;
};



#endif  // NOTEREGION_H_INCLUDED
