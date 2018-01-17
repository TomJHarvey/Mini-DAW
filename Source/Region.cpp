/*
 ==============================================================================
 
 Region.cpp
 Created: 27 Nov 2016 3:02:55pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "Region.h"


Region::Region()
{
    
    listener = nullptr;
}

Region::~Region()
{
    
}

void Region::setListener (Listener* newListener)
{
    listener = newListener;
}

void Region::mouseMove(const MouseEvent &event)
{
    
    listener -> setRegionNumberWhenMouseEntersRegion(regionNumber);
}

void Region::setRegionNumber(int regionNumber_)
{
    regionNumber = regionNumber_;
}

void Region::mouseExit (const MouseEvent &event)
{
    listener -> resetRegionNumberWhenMouseExitsRegion();
}




