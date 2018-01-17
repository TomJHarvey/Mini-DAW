/*
 ==============================================================================
 
 ArrangeWindow.cpp
 Created: 3 Jan 2017 12:06:57pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "ArrangeWindow.h"
#include "../JuceLibraryCode/JuceHeader.h"

ArrangeWindow::ArrangeWindow()
{
    
    // initalises variables inherited from window
    
    regionSize = 80;
    mininumXposition = 160;
    mininumYposition = 0;
    regionType = 0;
    currentRegionSize = 80;
    
    trackLabels.add(new TrackLabelGui);
    trackLabels[createTrackCounter] -> setTrackNumber(createTrackCounter);
    trackLabels[createTrackCounter] -> setBounds(0, createTrackHeight[createTrackCounter], 160, 80);
    trackLabels[createTrackCounter] -> setListener(this);
    addAndMakeVisible(trackLabels[createTrackCounter]);
    createTrackCounter ++;
    
    sequenceRegions.add(new SequenceRegion);                                            // an empty region
    sequenceRegions[createRegionCounter] -> setRegionNumber(createRegionCounter);
    regionData.add(new RegionData);
    
    createRegionCounter ++;
    
    addKeyListener(this);
    addMouseListener(this, true);
    
}
ArrangeWindow::~ArrangeWindow()
{
    
}

void ArrangeWindow::paint(Graphics& g)
{
    g.setColour (Colours::darkblue);       // Side bar
    g.drawRect(0, 0, 160, getHeight());
    g.fillRect(0, 0, 160, getHeight());
    
    g.setColour(Colours:: lightslategrey);
    g.drawRect(160, 0, getWidth(), getHeight());
    g.fillRect(160, 0, getWidth(), getHeight());
    
}

void ArrangeWindow::createTrackLabel()
{
    
    // creates a maxinum of four tracks
    
    if(createTrackCounter < 4)
    {
        trackLabels.add(new TrackLabelGui);
        trackLabels[createTrackCounter] -> setTrackNumber(createTrackCounter);
        trackLabels[createTrackCounter] -> setBounds(0, createTrackHeight[createTrackCounter], 160, 80);
        trackLabels[createTrackCounter] -> setListener(this);
        addAndMakeVisible(trackLabels[createTrackCounter]);
        trackLabelHeight = trackLabels[createTrackCounter] -> getHeight();
        trackLabelY = trackLabels[createTrackCounter] -> getY();
        createTrackCounter ++;
    }
    
}


bool ArrangeWindow::keyPressed(const KeyPress &key, Component* originatingComponent )
{
    // deletes currently selected region
    
    if (key.getTextCharacter() == 100)  // d
    {
        deleteRegion();
        listener -> deletePianoRoll(currentRegionNumber);
    }
    
    // creates a new region and related region data
    
    else if (key.getTextCharacter() == 114) // n
    {
        if (sequenceRegions.add(addRegions()) !=nullptr);
        
        if (regionCreated == true)
        {
            addAndMakeVisible(sequenceRegions[createRegionCounter]);
            regionData.add(new RegionData);
            addRegionData();
            listener -> resizeViewPorts(regionData[createRegionCounter] -> yPosition);
            listener -> setPianoRollSize(createRegionCounter, sequenceRegions[createRegionCounter] -> getWidth()); // do this like how i am with sequenceRPositons
            setPianoRollBoundary(((regionData[createRegionCounter] -> xSize / 80) *224 ) + 14 , createRegionCounter);
            
            for (int count = 0; count < createRegionCounter; count ++)
            {
                sequenceRegions[count] ->setRegionNumber(count);
            }
            createRegionCounter ++;
            regionCreated = false;
        }
    }
    
    // changes size of a sequence region
    
    else if (key.getTextCharacter() == 49 || key.getTextCharacter() == 50)  // 1 and 2
    {
        regionSizeChanged(key.getTextCharacter());
    }
    
    // opens piano roll
    
    else if (key.getTextCharacter() == 111) // o
    {
        listener -> openPianoRoll(currentRegionNumber);
    }
}


void ArrangeWindow::setListener (Listener* newListener)
{
    listener = newListener;
}


void ArrangeWindow::setSizeOfPianoRoll()
{
    listener -> setPianoRollSize(currentRegionNumber, sequenceRegions[currentRegionNumber] -> getWidth());
}

void ArrangeWindow::setPianoRollBoundary(int sequenceRegionBoundary_,  int regionNumber_)
{
    std::cout << "Reg boundary " << sequenceRegionBoundary_ << std::endl;
    listener -> setPianoRollX(sequenceRegionBoundary_ + 56, regionNumber_);
}

void ArrangeWindow::changeOscillator(int trackNumber_, int waveType_)
{
    // sets the wave type for the selected track
    std::cout << "Arrange window track number = " << trackNumber_ << std::endl;
    listener -> selectOscillator(trackNumber_, waveType_);
}

void  ArrangeWindow::changeTrackNumber(int trackNumber_ ,int regionNumber_)
{
    // changes the track number if the region has been moved
    listener -> changeTrackHeight(regionNumber_, trackNumber_);
}

void ArrangeWindow::adjustTrackGain(int trackNumber_, float gain_)
{
    listener -> changeTrackGain(trackNumber_, gain_);
}



