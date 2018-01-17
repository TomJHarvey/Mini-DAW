/*
 ==============================================================================
 
 Audio.cpp
 Created: 13 Nov 2014 8:14:40am
 Author:  Tom Mitchell
 
 ==============================================================================
 */

#include "Audio.h"

Audio::Audio()
{
    
    noteSize.add(0);
    noteSizeCounter.add(2);
    
    audioDeviceManager.initialiseWithDefaultDevices (2, 2); //2 inputs, 2 outputs
    audioDeviceManager.addMidiInputCallback (String::empty, this);
    audioDeviceManager.addAudioCallback (this);
    
    oscillatorPointers.add(new SinOscillator);
    oscillatorPointers[0] -> setSampleRate(sampleRate);
    
    trackOscillators.add(10); // add a default one at the beggening
    oscillatorGain.add(1.0);
    
}

Audio::~Audio()
{
    audioDeviceManager.removeAudioCallback (this);
    audioDeviceManager.removeMidiInputCallback (String::empty, this);
}


void Audio::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    //All MIDI inputs arrive here
}

void Audio::audioDeviceIOCallback (const float** inputChannelData,
                                   int numInputChannels,
                                   float** outputChannelData,
                                   int numOutputChannels,
                                   int numSamples)
{
    //All audio processing is done here
    const float *inL = inputChannelData[0];
    const float *inR = inputChannelData[1];
    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
    
    
    
    while(numSamples--)
    {
        float masterOscillator = 0;
        for (int count = 0; count < oscillatorPointers.size(); count ++)
        {
            masterOscillator += oscillatorPointers[count] ->nextSample() * oscillatorGain[count];
        }
        
        *outL = masterOscillator;
        *outR = masterOscillator;
        
        inL++;
        inR++;
        outL++;
        outR++;
    }
}


void Audio::audioDeviceAboutToStart (AudioIODevice* device)
{
    sampleRate = device->getCurrentSampleRate();
}

void Audio::audioDeviceStopped()
{
    
}

void Audio::stopNote()
{
    
    
    for (int count = 0; count < oscillatorPointers.size(); count ++)
    {
        
        if (noteSizeCounter[count] == noteSize[count] && noteSize[count] != 0)
        {
            oscillatorPointers[count] ->setAmplitude(0);
            noteSizeCounter.set(count, 0);
            noteSize.set(count, 0);
            oscillatorState.set(count, false);    // make oscillator available
            numOfOscillatorsInUse --;
        }
        
        else if (noteSizeCounter[count] < noteSize[count] )   // if the note should still be playing, increment it
        {
            std::cout << "Increment " << std::endl;
            int increment = noteSizeCounter[count] + 1;
            noteSizeCounter.set(count, increment);
        }
    }
    
}

void Audio::setNoteProperties(int noteNumber_, int noteSize_, int trackNumber_)
{
    
    
    if (numOfOscillatorsInUse == oscillatorPointers.size()) // if all the oscillators are in use it adds a new one
    {
        oscillatorPointers.add(new SinOscillator);
        oscillatorPointers[oscillatorPointers.size() -1] -> setSampleRate(sampleRate);
        noteSizeCounter.add(0);
        noteSize.add(0);
        trackNumbers.add(trackNumber_);
        oscillatorGain.add(1.0);
        // trackOscillators.add(0); // each one is defualt to a sine wave so track 0 = wave type 0
        
    }
    
    for (int count = 0; count < oscillatorPointers.size(); count ++)
    {
        std::cout << "Atttempt " << count << std::endl;
        std::cout << "Oscillators size" << std::endl;
        
        if (oscillatorState[count] == false) // if the oscillator isn't in use
        {
            frequency = midi.getMidiNoteInHertz(noteNumber_);
            //            oscillators[count] ->setFrequency(frequency);       // sets the frequency of the oscillator
            //            oscillators[count] ->setAmplitude(1.0 / oscillators.size());    // if its a chord makes each amplitude add up to 1
            
            // std::cout << "C NUMBER = " << trackOscillators[trackNumber_] << std::endl;
            
            if (trackOscillators[trackNumber_]== 0)
            {
                oscillatorPointers.set(count, new SinOscillator);
            }
            
            else if (trackOscillators[trackNumber_]== 1)
            {
                oscillatorPointers.set(count, new SquareOscillator);
            }
            
            else if (trackOscillators[trackNumber_]== 2)
            {
                oscillatorPointers.set(count, new SawOscillator);
            }
            
            oscillatorPointers[count] -> setFrequency(frequency);
            oscillatorPointers[count] -> setAmplitude(1.0 / oscillatorPointers.size());
            trackNumbers.set(count, trackNumber_);
            noteSize.set(count, noteSize_);   // sets the length of the note
            // std::cout << count << " inside note size = " << noteSize[count] << std::endl;
            noteSizeCounter.set(count, 1);    // increments the length to 1 (for 1 16th note already)
            oscillatorState.set(count, true);
            numOfOscillatorsInUse ++;                          // sets oscillator to being in use
            break;
        }
        
    }
    
    
}


void Audio::changeOscillator(int trackNumber_, int waveType_)
{
    
    // DBG("CHANGED");
    
    // std::cout << "track number = " << trackNumber_ << std::endl;
    
    if (waveType_ == 0)
    {
        for (int count = 0; count <  oscillatorPointers.size(); count ++)
        {
            if (trackNumbers[count] == trackNumber_)
            {
                oscillatorPointers.set(count, new SinOscillator);
            }
        }
    }
    
    else if ( waveType_ == 1)
    {
        for (int count = 0; count <  oscillatorPointers.size(); count ++)
        {
            
            if (trackNumbers[count] == trackNumber_)
            {
                oscillatorPointers.set(count, new SquareOscillator);
            }
        }
    }
    
    
    else if (waveType_ == 2)
    {
        for (int count = 0; count <  oscillatorPointers.size(); count ++)
        {
            
            if (trackNumbers[count] == trackNumber_)
            {
                oscillatorPointers.set(count, new SawOscillator);
            }
        }
    }
    
    std::cout << "Oscillators size  = " <<  trackOscillators.size() << std::endl;
    trackOscillators.set(trackNumber_, waveType_);
}

void Audio::addTrackOscillator()
{
    trackOscillators.add(0); // add a sine wave as a default
}

void Audio::adjustTrackGain(int trackNumber_, float gain_)
{
    
    for (int count = 0; count < oscillatorPointers.size(); count ++)
    {
        if (trackNumbers[count] == trackNumber_)
        {
            oscillatorGain.set(count, gain_);
        }
        
    }
    
}

void Audio::resetSequence(int buttonType_)
{
    for (int count = 0; count < oscillatorPointers.size(); count ++)
    {
        oscillatorPointers[count] ->setAmplitude(0);
        if (buttonType_ == 1)
        {
            oscillatorState.set(count, false);
            noteSizeCounter.set(count, 0);
            noteSize.set(count, 0);
            numOfOscillatorsInUse = 0;
        }
    }
    
}

