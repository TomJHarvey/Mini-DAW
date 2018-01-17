/*
 ==============================================================================
 
 Audio.h
 Created: 13 Nov 2014 8:14:40am
 Author:  Tom Mitchell
 
 ==============================================================================
 */

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

/**
 Class containing all audio processes
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "SinOscillator.h"
#include "Oscillator.h"
#include "SquareOscillator.h"
#include "SawOscillator.h"

class Audio :
public MidiInputCallback,
public AudioIODeviceCallback

{
public:
    /** Constructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** Returns the audio device manager, don't keep a copy of it! */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager;}
    
    
    /** Receives an incoming message.
     */
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    
    /** Processes a block of incoming and outgoing audio data.
     */
    
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
    
    /** Called to indicate that the device is about to start calling back.
     */
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    
    /** Processes a block of incoming and outgoing audio data. */
    void audioDeviceStopped() override;
    
    
    /** Calls the audio thread with oscillator and track information.
     
     @param noteNumber_  the midi note number based on its regions position on the y axis
     @param noteSize_  the midi note size based on its regions size
     @param trackNumber_ the track number ascoiated with the piano roll in use
     
     */
    void setNoteProperties(int noteNumber_,int noteSize_, int trackNumber_);
    
    /** Stops oscillators that have played the length of their related note region */
    void stopNote();
    
    
    /** Sets all oscillators with the selected track number to the same wave type.
     
     @param trackNumber_    the number of the track where its comboBox has been edited
     @param waveType_       the type of wave that has been selected on the changed track
     
     */
    void changeOscillator(int trackNumber_, int waveType_);
    
    /** Adds a new trackNumber that an oscillator can be when a track is created.*/
    
    void addTrackOscillator();
    
    /** Updates the gain of all the oscillators that share the selected track when the gain slider is moved.
     
     @param trackNumber_    the number of the track effected used to change oscillators with the same number
     @param gain_           the amount of gain applied to the selected oscillators
     
     */
    
    void adjustTrackGain(int trackNumber_, float gain_);
    
    /** Adds a new trackNumber that an oscillator can be when a track is created.
     @param buttonType_ resets the sequence completely if stop button and partially if the pause button
     
     */
    
    void resetSequence(int buttonType_);
    
private:
    
    AudioDeviceManager audioDeviceManager;
    MidiMessage midi;
    OwnedArray <Oscillator> oscillatorPointers;
    
    Array<bool> oscillatorState;
    Array<int> noteSize;
    Array<int> noteSizeCounter;
    Array<int> trackNumbers; // which numbers have which oscillators
    Array<int> trackOscillators;
    Array<float> oscillatorGain;
    
    float frequency = 440;
    float sampleRate = 44000;
    int numOfOscillatorsInUse = 0;
    
};



#endif  // AUDIO_H_INCLUDED
