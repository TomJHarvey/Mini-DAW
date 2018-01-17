/*
 ==============================================================================
 
 TrackLabelGui.h
 Created: 27 Nov 2016 8:30:06am
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef TRACKLABELGUI_H_INCLUDED
#define TRACKLABELGUI_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"

/**
 Class for a trackLabel Gui elements
 */


class TrackLabelGui:
public Component,
public Slider::Listener,
public ComboBox::Listener

{
public:
    
    /**
     TrackLabelGui constructor.
     */
    TrackLabelGui();
    
    /**
     TrackLabelGui destructor.
     */
    ~TrackLabelGui();
    
    /** Colours the trackLabel background.
     */
    void paint (Graphics&) override;
    
    /** Sets the bounds of the trackLabels components.
     */
    void resized() override;
    
    /** Is called when a slider is moved.
     */
    void sliderValueChanged (Slider* slider) override;
    
    /** Is called when a comboBox is edited.
     */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    /** Sets the track number.
     */
    void setTrackNumber(int trackNumber_);
    
    /** A class used by other classes to listen to trackLabelGui objects.
     */
    
    class Listener
    {
    public:
        
        /**
         Listener destructor
         */
        virtual ~Listener() {}
        
        /** Sets the wave type of all oscillators on the current track
         
         @param trackNumber  the number of the track being changed
         @param waveType_   the wave type to change the selcted tracks to
         
         */
        virtual void changeOscillator(int trackNumber, int waveType_) = 0;
        
        /** Updates the gain of all the oscillators that share the selected track when the gain slider is moved.
         
         @param trackNumber_    the number of the track effected used to change oscillators with the same number
         @param gain_           the amount of gain applied to the selected oscillators
         
         */
        virtual void adjustTrackGain(int trackNumber_, float gain_) = 0;
    };
    
    
    /**
     Sets a listener to this class
     */
    
    void setListener (Listener* newListener);
    
private:
    
    ComboBox oscillatorSelector;
    Label trackLabel;
    Label gainLabel;
    Slider volumeSlider;
    Listener* listener;
    int currentTrackNumber;
    String trackNumbers[4] = { "1","2","3","4"};
    
};



#endif  // TRACKLABELGUI_H_INCLUDED
