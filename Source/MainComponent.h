/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackLabelGui.h"
#include "SequenceRegion.h"
#include "PianoRoll.h"
#include "Audio.h"
#include "ArrangeWindow.h"
#include "Counter.h"


//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainContentComponent:
public AnimatedAppComponent,
public Button::Listener ,
public PianoRoll::Listener,
public Slider::Listener,
public ArrangeWindow::Listener,
public Counter::Listener
{
public:
    //==============================================================================
    
    /** MainContentComponent constructor */
    MainContentComponent(Audio &a);
    
    /** MainContentComponent destructor */
    ~MainContentComponent();
    
    /** Draws the GUI elements in the main window.*/
    void paint (Graphics& g) override;
    
    /** Draws the GUI elements in the main window.*/
    void paintOverChildren (Graphics&) override;
    
    /** Is called when the window is resized. */
    void resized() override;
    
    /** Is called when a button is clicked.*/
    void buttonClicked(Button* button) override;
    
    /** Is called when a slider is moved.*/
    void sliderValueChanged (Slider* slider) override;
    
    /** Resets and starts the sequence from the start when the counter reaches the length of the sequence.*/
    void resetCounter();
    
    /** Updates the sequence based on the main thread counter position.*/
    void counterChanged (int counterValue_) override;
    
    /** Resets the sequence when the stop button is pressed.*/
    void resetSequence(int buttonType_) override;
    
    /** Inherited from animated app component.*/
    void update() override;
    
    // In herited from piano roll
    
    /** Calls the audio thread with oscillator and track information.
     
     @param noteNumber_  the midi note number based on its regions position on the y axis
     @param noteSize_  the midi note size based on its regions size
     @param trackNumber_ the track number ascoiated with the piano roll in use
     
     */
    
    void setNotePropertiesForAudio(int noteNumber_, int noteSize_, int trackNumber_) override;
    
    
    /** Called when a counter reaches the end of a region and updates a counter so it can check the next region.
     
     @param counterValue_   the position of the counter when the region has finished
     
     */
    
    void incrementRegionCounter(int counterValue_) override;
    
    // inherited from arrangeWindow
    
    
    /** Creates a new piano roll and viewport and resisizes all the existing piano rolls and viewports
     
     @param trackNumber_   sets the track number based on the Y position of its related sequence region.
     
     */
    
    void resizeViewPorts(int trackNumber_) override;
    
    
    /** Removes a piano roll and view port when a sequence region is deleted.
     
     @param currentRegionNumber_    the number of the region that has been deleted
     
     */
    
    void deletePianoRoll(int currentRegionNumber_) override;
    
    /** Sends the selected piano roll to the front.
     
     @param currentRegionNumber_    the number of the region that was opened
     
     */
    
    void openPianoRoll(int currentRegionNumber_) override;
    
    /** Sets the maxinum boundary for the pianoRoll's size.
     
     @param currentRegionNumber_    the number of the region that has been edited
     @param pianoRollSize_          the position of its related sequence region scaled down
     
     */
    
    void setPianoRollSize(int currentRegionNumber_, int pianoRollSize_) override;
    
    /** Sets all oscillators with the selected track number to the same wave type.
     
     @param trackNumber_    the number of the track where its comboBox has been edited
     @param waveType_       the type of wave that has been selected on the changed track
     
     */
    
    void selectOscillator(int trackNumber_, int waveType_) override;
    
    /** Changes the trackNumber of the pianoRoll based on its related sequence regions y position.
     
     @param regionNumber_  the pianoRoll that is effected
     @param trackNumber_   the track number to change the piano roll too
     
     */
    
    void changeTrackHeight(int regionNumber_, int trackNumber_) override;
    
    
    /** Updates the gain of all the oscillators that share the selected track when the gain slider is moved.
     
     @param trackNumber_    the number of the track effected used to change oscillators with the same number
     @param gain_           the amount of gain applied to the selected oscillators
     
     */
    
    void changeTrackGain(int trackNumber_, float gain_) override;
    
    /** Sets the maxinum space in the piano roll for placing note note regions.
     
     @param sequenceRegionBoundary_ the maxinum X position where note regions can be placed based off its related sequence regions size and position
     @param regionNumber_           the piano roll to be effected
     
     */
    
    void setPianoRollX(int sequenceRegionBoundary_, int regionNumber_) override;
    
    
    /** A class used for drawing a rectangle
     */
    
    class HorizontalBar: public Component
    {
        
    public:
        
        HorizontalBar(){}
        ~HorizontalBar(){}
        
        void paint(Graphics& g)
        {
            g.fillAll(Colours::lightgrey);
        }
    };
    
    
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
    
    TextButton createTrackButton;   // creates new tracks
    TextButton playButton;          // starts the thread and plays
    TextButton stopButton;          // pauses the thread until play is pressed? and resets everything
    Slider bpmSlider;               // adjusts the Bpm
    Slider adjustHeightOfPianoRollSlider;   // adjusts the height of the piano roll
    Slider beatSlider;                      // changes the amount of bars looped in the sequence
    Label bpmLabel;
    Label barLabel;
    
    OwnedArray<PianoRoll> pianoRolls;
    OwnedArray<Viewport> pianoRollViewPort;
    ArrangeWindow arrangeWindow;
    Viewport arrangeWindowViewPort;
    
    Audio& audio;
    Audio a;
    
    HorizontalBar horizontalBar;    // used as the bar above the piano roll
    HorizontalBar playHead;         // the play head
    
    Counter threadCounter;
    
    int createNoteRegionCounter = 0;
    int pianoRollheightY = 300;
    int height = 0;
    int regionCounter = 1;
    int incrementValue = 0;
    int sameXpositionCounter = 0;
    int longestPianoRoll = 0;
    int currentCounterValue = 0;
    int previousPianoRollSliderValue = 0;
    int currentRegionNumber = 0;
    int viewportWidth = 0;
    int viewportHeight = 0;
    
    int NewlongpianoRoll = 0;
};


#endif  // MAINCOMPONENT_H_INCLUDED
