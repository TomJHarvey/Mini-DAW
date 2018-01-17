/*
 ==============================================================================
 
 Region.h
 Created: 27 Nov 2016 3:02:55pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef REGION_H_INCLUDED
#define REGION_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


/**
 Class for a generic region
 */


class Region:
public Component
{
public:
    //==============================================================================
    /**
     Region constructor.
     */
    Region();
    
    /**
     Region destructor.
     */
    virtual ~Region();
    
    /**
     sets the region number when the mouse enters the region.
     */
    void mouseMove(const MouseEvent &event) override;
    
    /**
     sets the region number to 0 when the mouse exits the region.
     */
    void mouseExit (const MouseEvent &event) override;
    
    
    /**
     sets the regionNumber when creating a region.
     */
    
    void setRegionNumber(int regionNumber_);
    
    /** A class used by other classes to listen to Region objects.
     */
    
    class Listener
    {
    public:
        
        /**
         Listener destructor
         */
        virtual ~Listener() {}
        
        /** Sets the region number of the currently selected region
         
         @param regionNumber_  the region number of the currently selected region
         
         */
        
        virtual void setRegionNumberWhenMouseEntersRegion(int regionNumber) = 0;
        
        /** Sets the region number to 0 when no region is selcted
         */
        virtual void resetRegionNumberWhenMouseExitsRegion() =0 ;
    };
    
    /**
     Sets the listener
     */
    
    void setListener (Listener* newListener);
    
    Listener* listener;
    
private:
    
    int regionNumber = 0;
    int changeSizeOfregionValue = 80;
    
    Slider moveRegionSlider;
    Slider changeSizeOfRegionSlider;
    
    TextButton openPianoRoll;
    
};



#endif  // REGION_H_INCLUDED
