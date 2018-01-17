/*
 ==============================================================================
 
 Window.cpp
 Created: 14 Jan 2017 6:58:42pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "Window.h"



Window::Window()
{
    
    
}

Window::~Window()
{
    
    
    
}
void Window::mouseMove(const MouseEvent &event)
{
    
    // sets the mouse position when the mouse is moved
    
    MouseEvent currentEvent = event.getEventRelativeTo(this);
    mousePositionX = currentEvent.x;
    mousePositionY = currentEvent.y;
    
    if (mousePositionX  % regionSize !=0)
    {
        remainderX =  mousePositionX  % regionSize;
        mousePositionX  =  mousePositionX  - remainderX;
    }
    
    if (mousePositionY % regionSize !=0)
    {
        remainderY = mousePositionY % regionSize;
        mousePositionY = mousePositionY - remainderY;
    }
}

void Window::mouseUp(const MouseEvent &event)
{
    
    event.getEventRelativeTo(this);
    MouseEvent currentEvent = event.getEventRelativeTo(this);
    const int EventX = currentEvent.getDistanceFromDragStartX();
    const int EventY  = currentEvent.getDistanceFromDragStartY();
    
    
    // moves a region and is snapped to a multiple of its region size (this is either a note or sequence region)
    
    if (EventX % regionSize == 0)
    {
        mousePositionDraggedX = EventX;
    }
    
    else if (EventX % regionSize !=0)
    {
        remainderX = EventX % regionSize;
        mousePositionDraggedX = EventX - remainderX;
    }
    
    if (EventY % regionSize ==0)
    {
        mousePositionDraggedY = EventY;
    }
    
    else if (EventY % regionSize !=0)
    {
        remainderY = EventY % regionSize;
        mousePositionDraggedY = EventY - remainderY;
    }
    
    
    
    // updates regiondata and region infromation
    
    moveRegionWhenClickedAndDragged(mousePositionDraggedX, mousePositionDraggedY);
    
    if (mousePositionDraggedX < 0)
    {
        mousePositionDraggedX *= -1;
    }
    
    if (mousePositionDraggedY < 0)
    {
        mousePositionDraggedY *= -1;
    }
    
    // changes the track number and the length of the entire sequence
    
    if (mousePositionDraggedX >= 80 || mousePositionDraggedY >= 80)
    {
        std::cout << regionData[currentRegionNumber] -> xSize << " + " << regionData[currentRegionNumber] -> xPosition << std::endl;
        
        changeTrackNumber(regionData[currentRegionNumber] -> yPosition, currentRegionNumber);
        
    }
    
    
    
}


Region* Window::addRegions()
{
    Region* regionPointer = nullptr;
    
    
    // creates a region and is snapped to a multiple of its region size (this is either a note or sequence region)
    
    if (mousePositionX %regionSize != 0)
    {
        remainderX = mousePositionX % 80;
        mousePositionX= mousePositionX - remainderX;
    }
    
    if (mousePositionY %regionSize != 0)
    {
        remainderY = mousePositionY % regionSize;
        mousePositionY= mousePositionY - remainderY;
    };
    
    // if its a sequence region it is snapped to the lowest place it can go
    
    if (mousePositionY > trackLabelHeight + trackLabelY && regionType == 0)
    {
        mousePositionY = trackLabelY;
    }
    
    if (regionType == 1 && mousePositionX > maxinumXPosition)
    {
        
        mousePositionX = maxinumXPosition - 14;
    }
    
    // makes sure its within the right space of the window
    
    if (mousePositionX >= mininumXposition )
    {
        
        // makes a new Pointer to a region and sets and returns its attibutes and adds it to an array
        
        if (regionType == 0 )
        {
            regionPointer = new SequenceRegion;
        }
        else if (regionType == 1)
        {
            regionPointer =  new NoteRegion;
        }
        
        regionPointer -> setRegionNumber(createRegionCounter);
        regionPointer->setSize (regionSize, regionSize);    //  current regionSize
        regionPointer->setTopLeftPosition (mousePositionX, mousePositionY);
        regionPointer -> setListener(this);
        addAndMakeVisible(regionPointer);
        regionCreated = true;
    }
    
    else
    {
        regionCreated = false;
        regionPointer = nullptr;
    }
    
    
    
    return regionPointer;
}

void Window::addRegionData()
{
    
    // creates region data for each newly added region
    
    if (createRegionCounter < regionData.size())
    {
        
        if (regionType == 0 )
        {
            regionData[createRegionCounter]-> xPosition = sequenceRegions[createRegionCounter] -> getX();
            regionData[createRegionCounter] -> yPosition = sequenceRegions[createRegionCounter] -> getY();
            regionData[createRegionCounter] -> xSize = sequenceRegions[createRegionCounter] -> getWidth();
        }
        else if (regionType == 1)
        {
            regionData[createRegionCounter]-> xPosition = noteRegions[createRegionCounter] -> getX();
            regionData[createRegionCounter] -> yPosition = noteRegions[createRegionCounter] -> getY();
            regionData[createRegionCounter] -> xSize = noteRegions[createRegionCounter] -> getWidth();
        }
        
        // re orders them in order of x position
        
        for (int count = 0; count < regionData.size() - 1; count ++)
        {
            if (regionData[createRegionCounter] -> xPosition < regionData[count] -> xPosition)
            {
                regionData.move(createRegionCounter, count);
                
                if (regionType == 0)
                {
                    noteRegions.move(createRegionCounter, count);
                }
                
                else if (regionType == 1)
                {
                    sequenceRegions.move(createRegionCounter, count);
                }
                break;
            }
            
        }
        
        // sets the furthest note regions can be placed based on its sequence region
        
        if(regionType == 0)
        {
            setSizeOfPianoRoll();
        }
        
    }
}

void Window::deleteRegion()
{
    
    // removes a region and its region data
    
    if (currentRegionNumber != 0)
    {
        if (regionType == 0)
        {
            sequenceRegions.remove(currentRegionNumber);
        }
        else if (regionType == 1)
        {
            noteRegions.remove(currentRegionNumber);
        }
        
        regionData.remove(currentRegionNumber);
        
        for (int count = 0;count < sequenceRegions.size(); count ++)
        {
            if (regionType == 0)
            {
                sequenceRegions[count] -> setRegionNumber(count);
            }
            
            else if (regionType == 1)
            {
                noteRegions[count] -> setRegionNumber(count);
            }
        }
        
        currentRegionNumber = 0;
        createRegionCounter --;
    }
    
}
void Window::setRegionNumberWhenMouseEntersRegion(int regionNumber)
{
    currentRegionNumber = regionNumber;
}
void Window::resetRegionNumberWhenMouseExitsRegion()
{
    currentRegionNumber = 0;    // add boundries for piano roll
}

void Window::moveRegionWhenClickedAndDragged(int x, int y)
{
    
    
    // re orders regino and region data to ensure the smallest x position is first in chronological order
    
    if (currentRegionNumber != 0)
    {
        int X = 0;
        int Y = 0;
        
        if (regionType == 0)
        {
            X = sequenceRegions[currentRegionNumber]->getX() + x;
            Y = sequenceRegions[currentRegionNumber] -> getY() + y;
        }
        
        else  if (regionType == 1)
        {
            X = noteRegions[currentRegionNumber]->getX() + x;
            Y = noteRegions[currentRegionNumber] -> getY() + y;
        }
        
        // if the region is out of its boundaries it is snapped to its closest position
        
        if (X  < mininumXposition)
        {
            X  = mininumXposition;
        }
        
        if (Y < mininumYposition)
        {
            Y = mininumYposition;
        }
        
        if( Y >= trackLabelHeight + trackLabelY  && regionType == 0)
        {
            Y = trackLabelY;
        }
        
        if (regionType == 1 &&  X > maxinumXPosition)
        {
            
            X = maxinumXPosition - 14;
        }
        
        if (regionType == 0)
        {
            sequenceRegions[currentRegionNumber]->setTopLeftPosition(X, Y);
        }
        else  if (regionType == 1)
        {
            noteRegions[currentRegionNumber]->setTopLeftPosition(X, Y);
        }
        
        
        regionData[currentRegionNumber] -> xPosition = X;
        regionData[currentRegionNumber] -> yPosition = Y;
        
        // this re orders the regions so they're in consecutive order
        
        for (int count = 1; count < regionData.size() ; count ++)
        {
            // If its not the last in the array
            if (currentRegionNumber != regionData.size() - 1)
            {
                // If it hasn't changed position in the array
                if (regionData[currentRegionNumber] -> xPosition > regionData[currentRegionNumber - 1] -> xPosition &&
                    regionData[currentRegionNumber] -> xPosition < regionData[currentRegionNumber + 1] -> xPosition)
                {
                    break;
                }
            }
            
            // If the changed value is bigger than the last value, or that itself
            
            if (regionData[currentRegionNumber] -> xPosition > regionData[regionData.size() - 1] -> xPosition)
            {
                regionData.move(currentRegionNumber, regionData.size() - 1);
                
                if (regionType == 0)
                {
                    sequenceRegions.move(currentRegionNumber, regionData.size() - 1);
                }
                else if (regionType == 1)
                {
                    noteRegions.move(currentRegionNumber, regionData.size() - 1);
                }
                
                
                break;
            }
            
            // If the changed value is smaller than the first value or that iself
            
            if (regionData[currentRegionNumber] -> xPosition < regionData[1] -> xPosition)
            {
                regionData.move(currentRegionNumber, 1);
                if (regionType == 0)
                {
                    sequenceRegions.move(currentRegionNumber, 1);
                }
                else if (regionType == 1)
                {
                    noteRegions.move(currentRegionNumber, 1);
                }
                
                break;
            }
            
            
            if (regionData[currentRegionNumber] -> xPosition < regionData[count] -> xPosition)
            {
                if (regionData[currentRegionNumber] -> xPosition < regionData[currentRegionNumber - 1] -> xPosition)
                {
                    count = count;
                }
                else
                {
                    count = count -1;
                }
                regionData.move(currentRegionNumber, count);
                
                if (regionType == 0)
                {
                    sequenceRegions.move(currentRegionNumber, count);
                }
                
                else if (regionType == 1)
                {
                    noteRegions.move(currentRegionNumber, count);
                }
                
                break;
            }
            
        }
        
        for (int count = 1; count < sequenceRegions.size() ; count ++)
        {
            sequenceRegions[count] -> setRegionNumber(count);
        }
        
        
        for (int count = 1; count < noteRegions.size() ; count ++)
        {
            noteRegions[count] -> setRegionNumber(count);
        }
        
    }
    
    
}

void Window::regionSizeChanged(int changeOfsize)
{
    
    // changes the size of the region and region data
    
    
    if (changeOfsize == 49)
    {
        changeOfsize = regionSize * -1;
    }
    
    else if (changeOfsize == 50)
    {
        changeOfsize = regionSize * 1;
    }
    
    
    if (previousXsize + changeOfsize != 0)
    {
        
        if (regionType == 0)
        {
            changeOfsize += sequenceRegions[currentRegionNumber] -> getWidth();
            
            if (changeOfsize == 0)
            {
                changeOfsize = regionSize;
            }
            
            
            sequenceRegions[currentRegionNumber] -> setSize(changeOfsize, regionSize);
            regionData[currentRegionNumber] -> xSize = sequenceRegions[currentRegionNumber] -> getWidth();
            currentRegionSize = regionData[currentRegionNumber] -> xSize;
            previousXsize = changeOfsize;
            setSizeOfPianoRoll();
            setPianoRollBoundary(((regionData[currentRegionNumber] -> xSize / 80) *224 ) + 14, currentRegionNumber);
        }
        
        else if (regionType == 1)
        {
            changeOfsize += noteRegions[currentRegionNumber] -> getWidth();
            noteRegions[currentRegionNumber] -> setSize(changeOfsize, regionSize);
            regionData[currentRegionNumber] -> xSize = noteRegions[currentRegionNumber] -> getWidth();
            currentRegionSize = regionData[currentRegionNumber] -> xSize;
            previousXsize = changeOfsize;
        }
        
        
    }
}

