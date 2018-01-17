/*
 ==============================================================================
 
 PianoRoll.h
 Created: 2 Dec 2016 2:48:01pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "noteRegion.h"
#include "Audio.h"
#include "Window.h"

#ifndef PIANOROLL_H_INCLUDED
#define PIANOROLL_H_INCLUDED

/**
 Class for a piano roll
 */

class PianoRoll:
public Button::Listener,
public KeyListener,
public Window

{
    
public:
    
    /**
     PianoRoll constructor
     */
    
    PianoRoll(Audio& a);
    
    /**
     PianoRoll destructor
     */
    
    ~PianoRoll();
    
    /** Colours the piano roll
     */
    
    void paint (Graphics&) override;
    
    
    void buttonClicked(Button* button) override;
    
    /** Is called when a key is pressed
     */
    
    bool keyPressed(const KeyPress &key, Component* originatingComponent ) override;
    
    /** Checks to see if note regions are at the same position as the counter
     
     @param counterValue_   the thread counter value
     */
    
    void startOscillators(int counterValue_);
    
    /** Sets the track number based on its related sequence region y position
     
     @param trackNumber_   sets the track number the piano roll is related to
     */
    
    void setTrackNumber(int trackNumber_);
    
    /** Sets the maxinum space note regions can be placed in the piano roll
     
     @param sequenceRegionBoundary_  the x position + size of its related seuqnce region
     */
    
    void setPianoRollBoundary1(int sequenceRegionBoundary_);
    
    /** Sets the size of the pianoRoll
     
     @param size_  the size of its realted sequence region
     */
    
    void setPianoRollsize(int size_);
    
    
    /** Re sets the note data counter when the length of the piano roll has been played
     
     @param counter_    the size that the counter is reset to
     */
    
    void setNoteDataCounter(int counter_);
    
    
    // Inherited from window
    
    /** sets the size of a piano roll based on its realted sequence regions width */
    void setSizeOfPianoRoll() override;
    
    /** Sets the maxinum space note regions can be placed in the piano roll
     
     @param sequenceRegionBoundary_  the x position + size of its related seuqnce region
     @param regionNumber_ the number of the piano roll being changed
     
     */
    void setPianoRollBoundary(int sequenceRegionBoundary_, int regionNumber_) override;
    
    
    /** Sets a piano rolls height if a sequence region has changed Y position
     
     @param trackNumber_  the height that the sequence region is placed on
     @param regionNumber_  the pianoRoll being effected
     
     */
    
    void changeTrackNumber(int trackNumber_, int regionNumber_) override;
    
    
    /** A class used by other classes to listen to pianoRoll objects.
     */
    
    class Listener
    {
    public:
        
        /** Listener destructor*/
        virtual ~Listener() {}
        
        /** Called when a counter reaches the end of a region and updates a counter so it can check the next region.
         
         @param counterValue_   the position of the counter when the region has finished
         
         */
        virtual void incrementRegionCounter(int counterValue_) = 0;
        
        /** Calls the audio thread with oscillator and track information.
         
         @param noteNumber_  the midi note number based on its regions position on the y axis
         @param noteSize_  the midi note size based on its regions size
         @param trackNumber_ the track number ascoiated with the piano roll in use
         
         */
        virtual void setNotePropertiesForAudio(int noteNumber_, int noteSize_, int trackNumber_) = 0;
        
    };
    
    /**
     sets the listener
     */
    
    void setListener (Listener* newListener);
    
    
    /**
     A class to set the shape and colour of white piano key buttons.
     */
    
    
    class WhitePianoKeysLookAndFeel : public LookAndFeel_V3
    {
    public:
        WhitePianoKeysLookAndFeel()
        {
            
        }
        void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                   bool isMouseOverButton, bool isButtonDown) override
        {
            Rectangle<int> buttonArea = button.getLocalBounds();
            
            g.setColour (Colours::black);
            g.drawRect(buttonArea);
            //g.fillRect (buttonArea);
            
            if (isButtonDown == true)
            {
                g.setColour (Colours::grey);
                g.drawRect(buttonArea);
                g.fillRect (buttonArea);
            }
            
        }
    };
    
    
    /**
     A class to set the shape and colour of black piano key buttons
     */
    
    
    class BlackPianoKeysLookAndFeel : public LookAndFeel_V3
    {
    public:
        BlackPianoKeysLookAndFeel()
        {
            
        }
        
        void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                   bool isMouseOverButton, bool isButtonDown) override
        {
            Rectangle<int> buttonArea = button.getLocalBounds();
            
            g.setColour (Colours::black);
            g.drawRect(buttonArea);
            g.fillRect(buttonArea);
            
            
            if (isButtonDown == true)
            {
                g.setColour (Colours::grey);
                g.drawRect(buttonArea);
                g.fillRect (buttonArea);
            }
        }
    };
    
    
    
private:
    
    String noteLetters[7] = {"C","B","A","G","F","E","D"};
    String octaveNumbers[9] = {"8","7","6","5","4","3","2","1","0"};
    Label noteLetterLabels[52];
    
    TextButton pianoKeys[127];
    TextButton blackPianoKeys[127];
    WhitePianoKeysLookAndFeel pianokeysLookAndFeel;
    BlackPianoKeysLookAndFeel blackPianoKeysLookAndFeel;
    Path pianoGridVerticalLines[180];
    Path pianoGridHorizontalLines[150];
    Path blackKeysBackground[180];
    
    float gridLineWidth = 70;
    float gridLineHeight = 14;
    int blackKeysPosition[5] = {48,24,24,48,24};
    
    Listener* listener;
    OwnedArray<NoteRegion> noteregions;
    Audio& audio;
    
    int lengthCounter = 0;
    int currentSize = 10;
    int previousCounterValue = 0;
    int trackNumber = 0;
    int pianoHeight = 0;
    int pianoRollSize = 0;
    int noteDataCounter = 1;
    int currentCounterValue = 0;
    int pianoRollBoundary = 0;
    int maxSizeOfpianoRoll = 0;
    
};


#endif  // PIANOROLL_H_INCLUDED
