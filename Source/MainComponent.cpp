/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent(Audio& a) :
audio(a)

{
    
    setSize (1000, 600);
    
    createTrackButton.setButtonText("CreateTrack");
    createTrackButton.addListener(this);
    addAndMakeVisible(createTrackButton);
    
    playButton.setButtonText("Play");
    playButton.addListener(this);
    addAndMakeVisible(playButton);
    
    stopButton.setButtonText("Stop");
    stopButton.addListener(this);
    addAndMakeVisible(stopButton);
    
    bpmSlider.setRange(10, 300,1);
    bpmSlider.addListener(this);
    bpmSlider.setValue(120);
    addAndMakeVisible(bpmSlider);
    
    beatSlider.setRange(1, 16, 1);
    beatSlider.addListener(this);
    beatSlider.setValue(2);
    addAndMakeVisible(beatSlider);
    
    bpmLabel.setText("Bpm", sendNotification);
    addAndMakeVisible(bpmLabel);
    
    barLabel.setText("Number of bars", sendNotification);
    barLabel.setColour(1, Colours::white);
    addAndMakeVisible(barLabel);
    
    arrangeWindow.setBounds(0, 80, 10000, 720);
    arrangeWindow.setListener(this);
    addAndMakeVisible(arrangeWindow);
    
    addMouseListener(this, true);
    threadCounter.setListener(this);
    
    adjustHeightOfPianoRollSlider.setRange(10.0, 1000 , 5);
    adjustHeightOfPianoRollSlider.setSliderStyle(Slider::IncDecButtons);
    adjustHeightOfPianoRollSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(adjustHeightOfPianoRollSlider);
    adjustHeightOfPianoRollSlider.addListener(this);
    
    pianoRolls.add(new PianoRoll(audio));
    pianoRolls[createNoteRegionCounter] -> setListener(this);
    pianoRolls[createNoteRegionCounter] -> setBounds(800,800,getWidth(),getHeight());
    pianoRolls[createNoteRegionCounter] -> setTrackNumber((0/ 80) + 1);
    
    pianoRollViewPort.add(new Viewport); // invisible one at the beggining
    
    createNoteRegionCounter ++;
    
    pianoRollViewPort.add(new Viewport);
    pianoRollViewPort[createNoteRegionCounter] -> setViewedComponent(pianoRolls[createNoteRegionCounter]);
    pianoRollViewPort[createNoteRegionCounter] -> setScrollBarsShown(true,true);
    addAndMakeVisible(pianoRollViewPort[createNoteRegionCounter]);
    
    int height = getHeight() - arrangeWindow.getY();
    int width = getWidth();
    
    arrangeWindowViewPort.setViewedComponent(&arrangeWindow);
    arrangeWindowViewPort.setScrollBarsShown(true,true);
    arrangeWindowViewPort.setBounds(0, 80, width,height );
    addAndMakeVisible(arrangeWindowViewPort);
    
    addAndMakeVisible(playHead);
    
    threadCounter.setBpm(400); // default bpm will be set here
    regionCounter = 1;
    
    setFramesPerSecond(100); // speed which paint is updated
    
    NewlongpianoRoll = 32;
}

MainContentComponent::~MainContentComponent()
{
    
}

void MainContentComponent::paint (Graphics& g)
{
    // Make background for both horizonal and vertical pannels
    
    g.fillAll (Colours::darkgrey);
    g.setColour (Colours::darkblue);
    
    g.drawRect (0, 0, getWidth(), 80);
    g.fillRect (0, 0, getWidth(), 80);
    
    
    if (createNoteRegionCounter > 1)
    {
        // Horizontal side bar
        g.setColour(Colours::darkgreen);
        g.drawRect(0, getHeight() -18, getWidth() , 18);
        g.fillRect(0, getHeight() -18, getWidth() , 18);
        
        // Vertical side bar
        int y = pianoRollViewPort[createNoteRegionCounter - 1] -> getY();
        int height = pianoRollViewPort[createNoteRegionCounter - 1] -> getHeight();
        g.drawRect(getWidth() - 18, y , 18, height);
        g.fillRect(getWidth() - 18, y , 18, height);
        
        
    }
}

void MainContentComponent::paintOverChildren (Graphics& g)
{
    
    // Play head position is updated by the position of the threadCounters count value
    int count = threadCounter.returnCounter();
    g.setColour(Colours::white);
    g.drawLine((count * 5 + 160 - arrangeWindowViewPort.getViewPositionX()) , 81 , (count * 5 + 160 - arrangeWindowViewPort.getViewPositionX()),horizontalBar.getY() - 20,2);
    
};

void MainContentComponent::resized()
{
    
    createTrackButton.setBounds(0, 0, 160, 80);
    playButton.setBounds(160, 0, 160, 80);
    stopButton.setBounds(320, 0, 160, 80);
    bpmSlider.setBounds(480, 0, 160, 80);
    bpmLabel.setBounds(480, 20, 80, 80);
    beatSlider.setBounds(640, 0, 160, 80);
    barLabel.setBounds(640, 20, 80, 80);
    
    // set all pianoRoll viewports to a default size when resized
    
    if (pianoRolls.size() > 1)
    {
        height = getHeight() - pianoRollViewPort[currentRegionNumber] -> getY();
        horizontalBar.setBounds(0, 300 - 18 , getWidth(), 18);
        adjustHeightOfPianoRollSlider.setBounds(0, 300 - 18, 14, 14);
    }
    
    for (int count = 0; count < pianoRollViewPort.size(); count ++)
    {
        pianoRollViewPort[count] ->setBounds(0,300,getWidth(),height);
    }
    
    
    if(createNoteRegionCounter > 1)
    {
        arrangeWindowViewPort.setBounds(0, 80, getWidth(), 200);
    }
    
    else
    {
        height = getHeight() - 78;
        arrangeWindowViewPort.setBounds(0, 80, getWidth(), height);
    }
}


void MainContentComponent::buttonClicked(Button* button)
{
    
    if (button == &createTrackButton)
    {
        arrangeWindow.createTrackLabel();   // adds a new track label
        audio.addTrackOscillator();         // adds a new track in the audio class
    }
    
    else if (button == &playButton)
    {
        threadCounter.toggleButton();  // starts and pauses the thread
    }
    
    else if (button == &stopButton)
    {
        threadCounter.stopCounter();    // stops the thread
    }
    
}

void MainContentComponent::sliderValueChanged (Slider* slider)
{
    
    // updates the pianoRoll, horizonatal bar, pianoroll slider, pianoroll viewports and arrange window viewports based on the slider position
    
    if (slider == &adjustHeightOfPianoRollSlider )
    {
        
        int sliderValue;
        if(slider -> getValue() < previousPianoRollSliderValue )
        {
            sliderValue = -5;
        }
        
        else
        {
            sliderValue = 5;
        }
        
        
        viewportWidth = getWidth();
        viewportHeight = getHeight() - pianoRolls[currentRegionNumber] -> getY();
        
        if (pianoRollViewPort[currentRegionNumber] -> getY() == 0)
        {
            pianoRollViewPort[currentRegionNumber] -> setBounds(0, 300,viewportWidth , viewportHeight);
        }
        
        
        previousPianoRollSliderValue = slider -> getValue();
        viewportHeight = getHeight() - pianoRollViewPort[currentRegionNumber] -> getY();
        pianoRollheightY = pianoRollViewPort[currentRegionNumber] -> getY() + sliderValue;
        horizontalBar.setBounds(0, pianoRollheightY - 18 , getWidth(), 18);
        adjustHeightOfPianoRollSlider.setBounds(0, pianoRollheightY- 18, 14, 14);
        
        std::cout << "P get y = " << pianoRollViewPort[currentRegionNumber] -> getY() << std::endl;
        //std::cout << "pianoRollHeighty = " << pianoRollheightY << std::endl;
        
        for (int count = 0; count < pianoRolls.size() ; count ++)
        {
            pianoRolls[count] ->setBounds(0, pianoRollheightY, 1248, 1248);
            pianoRollViewPort[count] -> setBounds(0, pianoRollheightY, getWidth(), viewportHeight);
        }
        
        arrangeWindowViewPort.setBounds(0, 80, getWidth(), arrangeWindowViewPort.getHeight() + sliderValue);
        
    }
    
    // updates the bpm based on the slider position
    
    else if (slider == &bpmSlider)
    {
        std::cout << (60/ slider -> getValue()) * 1000 << std::endl;
        threadCounter.setBpm((60/ slider -> getValue()) * 1000);
    }
    
    
    else if (slider == &beatSlider)
    {
        NewlongpianoRoll = slider -> getValue() * 16;
    }
    
}


void MainContentComponent::openPianoRoll(int currentRegionNumber_)
{
    // When a sequence region is opened it brings the selected piano roll and viewport to the front
    
    pianoRolls[currentRegionNumber_] -> toFront(true);
    pianoRollViewPort[currentRegionNumber_] -> toFront(true);
    pianoRollViewPort[currentRegionNumber_] -> setScrollBarsShown(true, true);
    // currentRegionNumber = currentRegionNumber_;
}

void MainContentComponent::resizeViewPorts(int trackNumber_)
{
    
    // adds a new pianoRoll and viewport when a sequence region is created
    
    pianoRolls.add(new PianoRoll(audio));
    pianoRolls[createNoteRegionCounter] -> setListener(this);
    pianoRolls[createNoteRegionCounter] -> setTrackNumber((trackNumber_/ 80) + 1);
    addAndMakeVisible(pianoRolls[createNoteRegionCounter]);
    pianoRolls[createNoteRegionCounter] -> setBounds(0, 300, 10000, 1248);
    
    viewportWidth = getWidth();
    viewportHeight = getHeight() - pianoRolls[createNoteRegionCounter] -> getY();
    
    pianoRollViewPort.add(new Viewport);
    pianoRollViewPort[createNoteRegionCounter] -> setViewedComponent(pianoRolls[createNoteRegionCounter]);
    pianoRollViewPort[createNoteRegionCounter] -> setScrollBarsShown(true,true);
    pianoRollViewPort[createNoteRegionCounter] -> setBounds(0,300,viewportWidth,viewportHeight);
    addAndMakeVisible(pianoRollViewPort[createNoteRegionCounter]);
    
    
    // resets other GUI elements when a sequence region is created
    
    arrangeWindowViewPort.setBounds(0, 80, getWidth(), 200);
    createNoteRegionCounter ++;
    
    int y = pianoRollViewPort[createNoteRegionCounter - 1] -> getY();
    addAndMakeVisible(horizontalBar);
    addAndMakeVisible(adjustHeightOfPianoRollSlider);
    horizontalBar.setBounds(0, y - 18 , getWidth() - 18, 18);
    adjustHeightOfPianoRollSlider.setBounds(0, y- 18, 14, 14);
    adjustHeightOfPianoRollSlider.toFront(true);
    
}

void MainContentComponent::deletePianoRoll(int currentRegionNumber_)
{
    // removes a piano roll and view port when a sequence region is deleted
    
    pianoRolls.remove(currentRegionNumber_);
    pianoRollViewPort.remove(currentRegionNumber_);
    createNoteRegionCounter --;
}

void MainContentComponent::counterChanged (int counterValue_)
{
    std::cout << counterValue_ << std::endl;
    currentCounterValue = counterValue_;
    
    // if the counter is as long as the furthest away piano roll the whole sequence resets
    
    resetCounter();
    
    if (pianoRolls.size() >= 1)
    {
        // if the sequence region at the smallest position the counter starts from the beggining
        
        if (arrangeWindow.regionData[regionCounter] -> xPosition == 160)
        {
            incrementValue = 0;
        }
        
        // sets the increment value based off the Xposition of the sequence region
        
        else
        {
            incrementValue = (((arrangeWindow.regionData[regionCounter] -> xPosition - 160 )) / 80) * 16;
        }
        
        // checks to see which oscillators need turning off
        
        audio.stopNote();
        
        // Looks through the piano roll to see if there are notes at the counters current position
        
        pianoRolls[regionCounter] -> startOscillators(counterValue_ - incrementValue);
        
        // check to see if theres a note the same position
        
        if (regionCounter < arrangeWindow.regionData.size() - 1)
        {
            for (int count = 1; count < arrangeWindow.regionData.size() - regionCounter ; count ++)
            {
                if(arrangeWindow.regionData[regionCounter] -> xPosition == arrangeWindow.regionData[regionCounter +count] -> xPosition)
                {
                    incrementValue = (((arrangeWindow.regionData[regionCounter + count] -> xPosition - 160 )) / 80) * 16;
                    pianoRolls[regionCounter + count] -> startOscillators(counterValue_ - incrementValue);
                }
            }
            
            
            // if the region before it is still playing when it should be triggered
            
            incrementValue = (((arrangeWindow.regionData[regionCounter + 1] -> xPosition - 160 )) / 80) * 16;
            pianoRolls[regionCounter + 1] -> startOscillators(counterValue_ - incrementValue);
            
        }
        
    }
    
}

void MainContentComponent::incrementRegionCounter(int counterValue_) // pass in the counter , if its higher than the highest one
{
    std::cout << "CALLED " << std::endl;
    
    // if its checking the last one it resets the sequence
    
    if(currentCounterValue >= NewlongpianoRoll)
    {
        threadCounter.setCounter(-1);
        regionCounter = 1;
        sameXpositionCounter = 0;
        
        for (int count = 0; count < pianoRolls.size(); count ++)
        {
            pianoRolls[count] -> setNoteDataCounter(1);
        }
        
    }
    
    
    
    else if (regionCounter < pianoRolls.size() - 1)
    {
        
        // if the sequence region doesn't have the same x position as the next it resets the sameXpositionCounter to 0
        
        if (arrangeWindow.regionData[regionCounter ] -> xPosition != arrangeWindow.regionData[regionCounter+1] -> xPosition)
        {
            sameXpositionCounter = 0;
        }
        
        
        if(regionCounter + sameXpositionCounter < pianoRolls.size() - 1)
        {
            
            
            // if it has the same x position it increments the counter
            
            if (arrangeWindow.regionData[regionCounter + sameXpositionCounter] -> xPosition == arrangeWindow.regionData[(regionCounter + sameXpositionCounter) +1] -> xPosition)
            {
                sameXpositionCounter ++;
            }
            
            
            // if it doesn't equal the one infront of it, but the last two were on the same X axis it resets the counter and increments the region Counter by the amount of regions that share the X position
            
            else if (arrangeWindow.regionData[regionCounter + sameXpositionCounter] -> xPosition != arrangeWindow.regionData[(regionCounter + sameXpositionCounter) +1] -> xPosition)
            {
                
                if (sameXpositionCounter != 0)
                {
                    regionCounter +=sameXpositionCounter;
                    regionCounter ++;
                    sameXpositionCounter = 0;
                    
                }
                
                // if  there are regions infront of the next one on different x axis's increment the counter
                
                else
                {
                    regionCounter ++;
                    sameXpositionCounter =0;
                }
            }
            
            
        }// end of if sposition + region loop
        
        else
        {
            
            //resetCounter();
        }
    }
    
}

void MainContentComponent::resetCounter()
{
    
    if(currentCounterValue >= NewlongpianoRoll)
    {
        threadCounter.setCounter(-1);
        regionCounter = 1;
        sameXpositionCounter = 0;
        
        for (int count = 0; count < pianoRolls.size(); count ++)
        {
            pianoRolls[count] -> setNoteDataCounter(1);
        }
        
    }
    
}

void  MainContentComponent::setPianoRollSize(int currentRegionNumber_, int pianoRollSize_)
{
    pianoRolls[currentRegionNumber_] -> setPianoRollsize((pianoRollSize_ / 80) * 16);
}

void MainContentComponent::setNotePropertiesForAudio(int noteNumber_, int noteSize_, int trackNumber_)
{
    // triggers the oscillators based on the pianoRoll information
    audio.setNoteProperties(noteNumber_, noteSize_, trackNumber_);
}

void MainContentComponent::resetSequence(int buttonType_)
{
    // resets the sequence when stop is pressed
    
    regionCounter = 1;
    sameXpositionCounter = 0;
    incrementValue = 0;
    audio.resetSequence(buttonType_);
}

void  MainContentComponent::update()
{
    
}

void MainContentComponent::selectOscillator(int trackNumber_, int waveType_)
{
    // sets all oscillators with the same track number to the same wave type
    audio.changeOscillator(trackNumber_ + 1, waveType_);
}

void MainContentComponent::changeTrackHeight(int regionNumber_, int trackNumber_)
{
    pianoRolls[regionNumber_] -> setTrackNumber((trackNumber_/ 80) + 1);
}

void MainContentComponent::changeTrackGain(int trackNumber_, float gain_)
{
    audio.adjustTrackGain(trackNumber_, gain_);
}
void MainContentComponent::setPianoRollX(int sequenceRegionBoundary_, int regionNumber_)
{
    // sets how far note regions can be placed in the pianoRoll
    pianoRolls[regionNumber_] -> setPianoRollBoundary1(sequenceRegionBoundary_);
}













