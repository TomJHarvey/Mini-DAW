/*
 ==============================================================================
 
 SequenceRegion.h
 Created: 3 Dec 2016 10:53:41am
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef SEQUENCEREGION_H_INCLUDED
#define SEQUENCEREGION_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Region.h"



/**
 Class for a sequence region
 */
class SequenceRegion:
public Region

{
public:
    
    
    /**
     SequenceRegion constructor
     */
    SequenceRegion();
    
    /**
     SequenceRegion destructor
     */
    ~SequenceRegion();
    
    /** Colours the SequenceRegion background
     */
    void paint (Graphics&) override;
    
};



#endif  // SEQUENCEREGION_H_INCLUDED
