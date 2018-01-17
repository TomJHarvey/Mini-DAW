/*
 ==============================================================================
 
 TrackLabelGui.cpp
 Created: 27 Nov 2016 8:30:06am
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "TrackLabelGui.h"
#include "MainComponent.h"

TrackLabelGui::TrackLabelGui()// :
// mainContentComponentPointer (m) // assign our pointer to the parent main component
{
    
    
    
    oscillatorSelector.setText("Oscillators");
    oscillatorSelector.addItem("Sine Wave", 01);
    oscillatorSelector.addItem("Square Wave", 02);
    oscillatorSelector.addItem("Saw Wave", 03);
    oscillatorSelector.addListener(this);
    addAndMakeVisible(oscillatorSelector);
    
    gainLabel.setText("Gain", sendNotification);
    addAndMakeVisible(gainLabel);
    
    String importedTrackNumber = " 1 ";
    trackLabel.setText("Track " + importedTrackNumber, sendNotification);
    addAndMakeVisible(trackLabel);
    
    // sets the range of the gain from 0 - 1
    
    volumeSlider.setRange(0.0, 1.0);
    volumeSlider.setSkewFactorFromMidPoint (0.15);
    volumeSlider.setValue(1);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
    
    listener = nullptr;
    
}

TrackLabelGui::~TrackLabelGui()
{
    
}

void TrackLabelGui::paint(Graphics& g)
{
    g.fillAll(Colours::orangered);
    
}

void TrackLabelGui::resized()
{
    trackLabel.setBounds(0, 0, 80, 12);
    oscillatorSelector.setBounds(0,25,80,20);
    volumeSlider.setBounds(0, 40, 150,40 );
    gainLabel.setBounds(85, 25, 40, 20);
}



void TrackLabelGui::sliderValueChanged (Slider* slider)
{
    
    // adjusts the gain of the track
    
    if (slider == &volumeSlider)
    {
        listener -> adjustTrackGain(currentTrackNumber + 1, slider -> getValue());
    }
}

void TrackLabelGui::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    
    // changes the tracks wave form
    
    if (listener != nullptr)
    {
        listener -> changeOscillator(currentTrackNumber ,comboBoxThatHasChanged -> getSelectedItemIndex());
    }
    
}

void TrackLabelGui::setTrackNumber(int trackNumber_)
{
    trackLabel.setText("Track " + trackNumbers[trackNumber_], sendNotification);
    currentTrackNumber = trackNumber_;
}

void TrackLabelGui::setListener (Listener* newListener)
{
    listener = newListener;
}

