/*
 ==============================================================================
 
 Counter.cpp
 Created: 5 Jan 2017 12:43:28pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "Counter.h"

Counter::Counter(): Thread ("CounterThread")
{
    
    listener = nullptr;
}


Counter::~Counter()
{
    stopThread(500);
    count.set(0);
    
}

void Counter::run()
{
    
    DBG("Run");
    
    
    while (!threadShouldExit())
    {
        
        // std::cout << "Counter:" << count << "\n";
        uint32 time = Time::getMillisecondCounter();
        
        // calls main component with the updated counter position
        
        if (listener != nullptr)
        {
            listener->counterChanged (count.get());
        }
        
        isThreadRunning();
        
        // increments the counter based on the bpm
        
        if (count.get() == 0)
        {
            Time::waitForMillisecondCounter (time + 0);
        }
        
        else
        {
            Time::waitForMillisecondCounter (time + counterBpm.get()/4);
        }
        count.set(count.get() + 1);
        //playHeadCount = count;
    }
}



void Counter::toggleButton()
{
    // toggles between pausing and starting the thread
    
    if (isThreadRunning() == false)
    {
        startThread();
    }
    
    else
    {
        stopThread(250);
        listener -> resetSequence(0);
    }
}

void Counter::stopCounter()
{
    
    // stops and resets the thread
    
    stopThread(250);
    count.set(0);
    listener -> resetSequence(1);
    
}

int Counter::returnCounter()
{
    return  count.get();
}

void Counter::setCounter(int counterValue_)
{
    count.set(counterValue_);
}

void Counter::setBpm(int bpm_)
{
    counterBpm.set(bpm_);
}

void Counter::setListener (Listener* newListener)
{
    listener = newListener;
}


