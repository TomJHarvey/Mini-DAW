/*
 ==============================================================================
 
 Window.h
 Created: 14 Jan 2017 6:58:42pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Region.h"
#include "SequenceRegion.h"
#include "NoteRegion.h"


#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

/**
 A class for arrange window and piano roll to inherit from
 */

class Window:
public Component,
public Region::Listener
{
public:
    
    
    /** Constructor */
    Window();
    
    /** Destructor */
    virtual~Window();
    
    /** updates the regions x and y positions when it is moved */
    void moveRegionWhenClickedAndDragged(int x, int y);
    
    /** returns a pointer to a region
     
     @return returns apointer to either a sequence region or a note region
     
     */
    Region* addRegions();
    
    /** Deletes a region and region data*/
    void deleteRegion();
    
    /** Adds region Data */
    void addRegionData();
    
    /** updates the size of a region when a regions size is increased */
    void regionSizeChanged(int changeOfsize);
    
    /** sets the size of a piano roll based on its realted sequence regions width */
    virtual void setSizeOfPianoRoll() = 0;
    
    /** Sets the maxinum space note regions can be placed in the piano roll
     
     @param sequenceRegionBoundary_  the x position + size of its related seuqnce region
     @param regionNumber_ the number of the piano roll being changed
     
     */
    
    virtual void setPianoRollBoundary(int sequenceRegionBoundary_, int regionNumber_) = 0;
    
    
    /** Sets a piano rolls height if a sequence region has changed Y position
     
     @param trackNumber_  the height that the sequence region is placed on
     @param regionNumber_  the pianoRoll being effected
     
     */
    
    virtual void changeTrackNumber(int trackNumber_, int regionNumber_) = 0;
    
    
    // Mouse Listener
    
    /** updates the mouse x and y positions position when a mouse is moved */
    void mouseMove(const MouseEvent &event) override;
    
    /** is called when the mouse is clicked and dragged */
    void mouseUp(const MouseEvent &event) override;
    
    
    // Inherited from NoteRegion
    
    
    /** Sets the region number of the currently selected region
     
     @param regionNumber_  the region number of the currently selected region
     
     */
    void setRegionNumberWhenMouseEntersRegion(int regionNumber) override;
    
    /** Sets the region number to 0 when no region is selcted
     */
    
    void resetRegionNumberWhenMouseExitsRegion() override;
    
    /** A structure for containing note x and y position and note size
     */
    
    struct RegionData
    {
        int xPosition;  // Where the notes starts
        int yPosition;  // What note it is
        int xSize;      // How long the note is
    };
    
    
    
    // Variables are public so they can be used by its children
    // Variables for moving and changing the size of regions
    
    int currentRegionNumber = 0;
    int mousePositionX = 0;
    int mousePositionY = 0;
    int mousePositionDraggedX = 0;
    int mousePositionDraggedY = 0;
    int remainderX = 0;
    int remainderY = 0;
    
    int maxinumXPosition = 0;
    
    // Region dimensions and boundaries
    int currentRegionSize = 0;
    int regionType = 0;
    int regionSize = 0; // initalise to 80, or to 14
    int createRegionCounter = 0;
    int mininumXposition = 0;
    int mininumYposition = 0;
    int previousXsize = 0;
    
    
    // Specific to sequence region
    int trackLabelHeight = 0;
    int trackLabelY = 0;
    
    OwnedArray <Region> sequenceRegions;
    OwnedArray <Region> noteRegions;
    OwnedArray <RegionData> regionData;
    
    bool regionCreated = false;
    
private:
    
    
};


#endif  // WINDOW_H_INCLUDED
