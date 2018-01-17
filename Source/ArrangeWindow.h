/*
 ==============================================================================
 
 ArrangeWindow.h
 Created: 3 Jan 2017 12:06:57pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef ARRANGEWINDOW_H_INCLUDED
#define ARRANGEWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackLabelGui.h"
#include "Region.h"
#include "SequenceRegion.h"
#include "Audio.h"
#include "Window.h"


/**
 Class for an arrange window
 */

class ArrangeWindow:
public KeyListener,
public Window,
TrackLabelGui::Listener
{
    
public:
    
    
    /**
     ArrangeWidnow constructor.
     */
    
    ArrangeWindow();
    
    /**
     ArrangeWidnow destructor.
     */
    ~ArrangeWindow();
    
    /**
     Creates a trackLabelGui object.
     */
    void createTrackLabel();
    
    /** Colours the arrange window background.
     */
    
    void paint(Graphics&) override;
    
    /** Is called when a key is pressed
     */
    
    bool keyPressed(const KeyPress &key, Component* originatingComponent) override;
    
    
    // In herited from Window
    
    /** Sets the size of the piano based off its related sequence region position
     */
    
    void setSizeOfPianoRoll() override;
    
    /** Sets the maxinum space note regions can be placed in the piano roll
     
     @param sequenceRegionBoundary_  the x position + size of its related seuqnce region
     @param regionNumber_  the pianoRoll being effected
     
     */
    
    void setPianoRollBoundary(int sequenceRegionBoundary_,int regionNumber_)  override;
    
    /** Sets a piano rolls height if a sequence region has changed Y position
     
     @param trackNumber_  the height that the sequence region is placed on
     @param regionNumber_  the pianoRoll being effected
     
     */
    
    void changeTrackNumber(int trackNumber_, int regionNumber_) override;
    
    
    // Inherited from TrackLabelGui
    
    
    /** Sets the wave type of all oscillators on the current track
     
     @param trackNumber  the number of the track being changed
     @param waveType_   the wave type to change the selcted tracks to
     
     */
    
    void changeOscillator(int trackNumber_, int waveType_) override;
    
    
    /** Updates the gain of all the oscillators that share the selected track when the gain slider is moved.
     
     @param trackNumber_    the number of the track effected used to change oscillators with the same number
     @param gain_           the amount of gain applied to the selected oscillators
     
     */
    
    void adjustTrackGain(int trackNumber_, float gain_) override;
    
    /** A class used by other classes to listen to ArrangeWindow objects.
     */
    
    
    class Listener
    {
    public:
        virtual ~Listener() {}
        
        /** Creates a new piano roll and viewport and resisizes all the existing piano rolls and viewports
         
         @param trackNumber_   sets the track number based on the Y position of its related sequence region.
         
         */
        virtual void resizeViewPorts(int trackNumber_) = 0;
        
        /** Removes a piano roll and view port when a sequence region is deleted.
         
         @param currentRegionNumber_    the number of the region that has been deleted
         
         */
        virtual void deletePianoRoll(int currentRegionNumber_) = 0;
        
        /** Sends the selected piano roll to the front.
         
         @param currentRegionNumber_    the number of the region that was opened
         
         */
        
        
        virtual void openPianoRoll(int currentRegionNumber_) = 0;
        
        /** Sets the maxinum boundary for the pianoRoll's size.
         
         @param currentRegionNumber_    the number of the region that has been edited
         @param pianoRollSize_          the position of its related sequence region scaled down
         
         */
        
        
        virtual void setPianoRollSize(int currentRegionNumber_, int pianoRollSize_) = 0;
        
        /** Sets all oscillators with the selected track number to the same wave type.
         
         @param trackNumber_    the number of the track where its comboBox has been edited
         @param waveType_       the type of wave that has been selected on the changed track
         
         */
        
        virtual void selectOscillator(int trackNumber_, int waveType_) = 0;
        
        /** Changes the trackNumber of the pianoRoll based on its related sequence regions y position.
         
         @param regionNumber_  the pianoRoll that is effected
         @param trackNumber_   the track number to change the piano roll too
         
         */
        
        virtual void changeTrackHeight(int regionNumber_, int trackNumber_) = 0;
        
        /** Updates the gain of all the oscillators that share the selected track when the gain slider is moved.
         
         @param trackNumber_    the number of the track effected used to change oscillators with the same number
         @param gain_           the amount of gain applied to the selected oscillators
         
         */
        
        
        virtual void changeTrackGain(int trackNumber_, float gain_) = 0;
        
        /** Sets the maxinum space in the piano roll for placing note note regions.
         
         @param sequenceRegionBoundary_ the maxinum X position where note regions can be placed based off its related sequence regions size and position
         @param regionNumber_           the piano roll to be effected
         
         */
        
        
        virtual void setPianoRollX(int sequenceRegionBoundary_,int regionNumber_) = 0;
    };
    
    
    /**
     sets the listener
     */
    void setListener (Listener* newListener);
    
private:
    
    int createTrackCounter = 0;
    int createTrackHeight[8] = {0,80,160,240,320,400,480,560};
    Listener* listener;
    OwnedArray <TrackLabelGui> trackLabels;
    
};



#endif  // ARRANGEWINDOW_H_INCLUDED
