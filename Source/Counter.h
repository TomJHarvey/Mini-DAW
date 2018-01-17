/*
 ==============================================================================
 
 Counter.h
 Created: 5 Jan 2017 12:43:28pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"


/**
 Class for time thread
 */

class Counter :
public Thread
{
    
public:
    
    /** Constructor */
    Counter();
    
    /** Deconstructor */
    ~Counter();
    
    /** Called when a thread is running */
    void run() override;
    
    /** Called when the play/pause button is pressed */
    void toggleButton();
    
    /** Called when the stop button is pressed */
    void stopCounter();
    
    /** Returns the counters current value */
    int returnCounter();
    
    /** Sets the counters value */
    void setCounter(int counterValue_);
    
    /** Sets the counters Bpm */
    void setBpm(int bpm_);
    
    
    /** A class used by other classes to listen to counter objects.
     */
    
    class Listener
    {
        
    public:
        
        /** Listener destructor*/
        virtual ~Listener() {}
        
        /** called when the counter value changes.
         
         @parm counterValue_ gives the listener its current counter position
         
         */
        virtual void counterChanged (int counterValue_) = 0;
        
        /** resets the sequence when the stop button is pressed or it reaches the end of the sequence
         
         @parm buttonType_
         
         */
        virtual void resetSequence(int buttonType_) = 0;
        
    };
    
    
    /** sets the listener */
    void setListener (Listener* newListener);
    
private:
    
    Atomic <int> counterBpm;
    Atomic <int> count;
    bool pause = false;
    
    Listener* listener;
};




#endif  // COUNTER_H_INCLUDED
