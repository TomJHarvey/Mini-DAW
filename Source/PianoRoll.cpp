/*
 ==============================================================================
 
 PianoRoll.cpp
 Created: 2 Dec 2016 2:48:01pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "PianoRoll.h"
#include <stdio.h>

PianoRoll::PianoRoll(Audio& a):
audio(a)
{
    
    // initalises variables inherited from window
    
    regionSize = 14;
    mininumXposition = 70;
    mininumYposition = 14;
    regionType = 1;
    pianoRollBoundary = 294;
    maxinumXPosition = 294;
    
    noteRegions.add(new NoteRegion);
    noteRegions[createRegionCounter] -> setRegionNumber(createRegionCounter);
    noteRegions[createRegionCounter] -> setSize(20, 10);
    noteRegions[createRegionCounter] -> setTopLeftPosition(mousePositionX, mousePositionY);
    
    regionData.add(new RegionData);
    regionData[createRegionCounter] -> xPosition = noteRegions[createRegionCounter] -> getX();
    regionData[createRegionCounter] -> yPosition = noteRegions[createRegionCounter] -> getY();
    regionData[createRegionCounter] -> xSize = noteRegions[createRegionCounter] -> getWidth();
    
    createRegionCounter ++;
    
    addMouseListener(this, true);
    // threadCounter.setListener(this);
    
    // Sets the position and label of each white piano key
    
    int noteLetterCounter = 0;
    int octaveNumberCounter = 0;
    
    for (int count = 0; count < 52; count ++)
    {
        if (noteLetterCounter == 7)
        {
            noteLetterCounter = 0;
            octaveNumberCounter ++;
        }
        
        pianoKeys[count].setLookAndFeel(&pianokeysLookAndFeel);
        pianoKeys[count].setBounds(0,pianoHeight, 70, 24);
        addAndMakeVisible(pianoKeys[count]);
        pianoKeys[count].addListener(this);
        
        noteLetterLabels[count].setText(noteLetters[noteLetterCounter] + octaveNumbers[octaveNumberCounter],sendNotification );
        noteLetterLabels[count].setBounds(40, pianoHeight, 35, 24);
        addAndMakeVisible(noteLetterLabels[count]);
        
        pianoHeight +=24;
        noteLetterCounter ++;
        if(count == 0)
        {
            octaveNumberCounter ++;
        }
    }
    
    int currentKey = -8;
    int keyCounter = 0;
    
    // Set the position and create each black key on the piano roll
    for (int count = 0; count < 36; count ++)
    {
        
        if (keyCounter == 5)
        {
            keyCounter = 0;
        }
        currentKey += blackKeysPosition[keyCounter];
        blackPianoKeys[count].setLookAndFeel(&blackPianoKeysLookAndFeel);
        blackPianoKeys[count].setBounds(0, currentKey, 40, 18);
        addAndMakeVisible(blackPianoKeys[count]);
        blackPianoKeys[count].addListener(this);
        keyCounter ++;
    }
    
    float lineWidth = 0;
    
    // Adds the horizontal lines for the piano roll
    
    for (int count = 0; count < 180; count ++)
    {
        lineWidth =  gridLineWidth + 56;
        pianoGridVerticalLines[count].startNewSubPath(lineWidth, 0);
        pianoGridVerticalLines[count].lineTo(lineWidth, 1248);
        pianoGridVerticalLines[count].closeSubPath();
        gridLineWidth += 56;
    }
    
    for (int count = 0; count < 150; count ++)
    {
        lineWidth =  gridLineHeight;
        pianoGridHorizontalLines[count].startNewSubPath(70, lineWidth);
        pianoGridHorizontalLines[count].lineTo(10000, lineWidth);
        pianoGridHorizontalLines[count].closeSubPath();
        gridLineHeight += 14;
    }
    
    
    addKeyListener(this);
    listener = nullptr;
}
PianoRoll::~PianoRoll()
{
    
}

void PianoRoll::paint(Graphics& g)
{
    
    //PianoRoll background
    
    g.setColour (Colours::yellow);
    g.drawRect(0, 0, 10000, 1248);
    g.fillRect(0, 0, 10000, 1248);
    
    g.setColour(Colours::black);
    g.drawRect(pianoRollBoundary, 0, getWidth(), getHeight());
    g.fillRect(pianoRollBoundary, 0, getWidth(), getHeight());
    
    // Piano keys background
    
    g.setColour (Colours::white);
    g.drawRect (0, 0, 70 , getHeight());
    g.fillRect (0, 0, 70, getHeight());
    
    g.setColour(Colours::grey);
    for (int count = 0; count < 180; count ++)
    {
        g.strokePath(pianoGridVerticalLines[count], PathStrokeType (1.0f));
    }
    g.setColour(Colours::grey);
    for (int count = 0; count < 88; count ++)
    {
        g.strokePath(pianoGridHorizontalLines[count], PathStrokeType (0.5f));
    }
    
}



void PianoRoll::setListener (Listener* newListener)
{
    listener = newListener;
}


bool PianoRoll::keyPressed(const KeyPress &key, Component* originatingComponent )
{
    
    if (key.getTextCharacter() == 100)  // d
    {
        deleteRegion();
        return true;
    }
    
    // adds a note region and region data
    
    else if (key.getTextCharacter() == 110) // n
    {
        if (noteRegions.add(addRegions()) !=nullptr);
        
        if (regionCreated == true)
        {
            addAndMakeVisible(noteRegions[createRegionCounter]);
            regionData.add(new RegionData);
            addRegionData();
            
            for (int count = 0; count < createRegionCounter; count ++)
            {
                noteRegions[count] -> setRegionNumber(count);
            }
            
            createRegionCounter ++;
            regionCreated = false;
            return true;
            
        }
    }
    
    // resizes the region
    
    else if (key.getTextCharacter() == 49 || key.getTextCharacter() == 50) // 1 and 2
    {
        regionSizeChanged(key.getTextCharacter());
    }
    else
    {
        return false;
    }
    
    return true;
}


void PianoRoll::startOscillators(int counterValue_)  // make this a seperateClass / in main so its only called once
{
    
    currentCounterValue = counterValue_;
    
    // if its not at the end of counting through the sequence
    
    if (counterValue_  != 0 && noteDataCounter < regionData.size())
    {
        
        int note = (regionData[noteDataCounter] -> xPosition - 70) / 14;
        int noteNumber = 97 - (regionData[noteDataCounter] -> yPosition / 14);
        int noteSize = regionData[noteDataCounter] -> xSize /14;
        int count = 0;
        
        if (note == currentCounterValue - 1)
        {
            // starts oscillator based on note regions positions
            
            listener -> setNotePropertiesForAudio(noteNumber, noteSize, trackNumber);
            noteDataCounter ++;
            currentSize = noteSize;
            lengthCounter ++;
            
            // if note regions share the same Y position it starts the oscillators based on their position
            
            while (true)
            {
                if (noteDataCounter != regionData.size() )
                {
                    if ((regionData[noteDataCounter] -> xPosition - 70) / 14 == currentCounterValue - 1 )
                    {
                        
                        listener -> setNotePropertiesForAudio(92 - (regionData[noteDataCounter + count] -> yPosition / 14), regionData[noteDataCounter + count] -> xSize /14,trackNumber );
                        noteDataCounter ++;
                    }
                    else
                    {
                        count = 0;
                        break;
                    }
                }
                
                else
                {
                    break;
                }
            }
            
        }
        
        previousCounterValue = currentCounterValue;
        
    }
    
    // if its at the end it resets its counter and tells main to move to the next region
    
    if (counterValue_ == pianoRollSize)
    {
        noteDataCounter = 1;
        listener -> incrementRegionCounter(counterValue_);
    }
}

void PianoRoll::buttonClicked(Button* button)
{
    // Here to make a sound to trigger an oscillator when a key is pressed
}

void PianoRoll::setSizeOfPianoRoll()
{
    // not in use
}

void PianoRoll::setTrackNumber(int trackNumber_)
{
    trackNumber = trackNumber_;
}
void PianoRoll::changeTrackNumber(int trackNumber_, int regionNumber_)
{
    // not in use
}

void PianoRoll::setPianoRollBoundary1(int sequenceRegionBoundary_)
{
    // sets the boundary for placing note regions
    
    std::cout << maxSizeOfpianoRoll << std::endl;
    pianoRollBoundary = sequenceRegionBoundary_;
    maxinumXPosition = pianoRollBoundary;
}

void PianoRoll::setPianoRollBoundary(int sequenceRegionBoundary_, int regionNumber_)
{
    // not in use
}

void PianoRoll::setPianoRollsize(int size_)
{
    pianoRollSize = size_;
}
void PianoRoll::setNoteDataCounter(int counter_)
{
    noteDataCounter = counter_;
}
