/*
  ==============================================================================

    MyAudioProcessor.h
    Created: 2 Sep 2024 9:43:16am
    Author:  alex_

  ==============================================================================
*/

/*So that I am able to implement the high, mid and low frequency filter it was needed for me to create this class, and implement all these virtual functions,
however, not many of these functions are used, due to the EQ effect being applied inside the DJAudioPlayer. I decided to make this as a separate class and not
inherit AudioProcessor in another class such as DJAudioPlayer due to AudioProcessor having a lot of pure virtual methods, it is cleaner this way*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/
class MyAudioProcessor  : public AudioProcessor
{
public:
    MyAudioProcessor();
    ~MyAudioProcessor() override;
    /*Pure virtual methods required to be implemented, however, as I explained, not many are being used for my purpose,
    some or them are being implemented as empty methods. A MINIMUM Implementation was given so that I can use the class alongside the vTreeState*/
    /*Inherited from AudioSource class, prepares the player to play audio*/
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    /*Inherited from AudioSource class, releases the resources used by the player*/
    void releaseResources() override;
    /*Renders the next block*/
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    /*Creating an editor for the EQ effect*/
    AudioProcessorEditor* createEditor() override;
    /*Checking for editor*/
    bool hasEditor() const override;
    /*Returning the name of the processor*/
    const String getName() const override;
    /*Returns the length of the processor's tail, in seconds*/
    double getTailLengthSeconds() const override;
    /*Returns true if the processor wants MIDI messages*/
    bool acceptsMidi() const override;
    /*Returns true if the processor produces MIDI messages*/
    bool producesMidi() const override;
    /*Returns true if this is a MIDI effect plug-in and does no audio processing*/
    bool isMidiEffect() const override;
    /*Returns the number of preset programs the processor supports*/
    int getNumPrograms() override;
    /*Returns the number of the currently active program*/
    int getCurrentProgram() override;
    /*Called by the host to change the current program*/
    void setCurrentProgram (int index) override;
    /*Must return the name of a given program*/
    const String getProgramName (int index) override;
    /*Called by the host to rename a program*/
    void changeProgramName (int index, const String& newName) override;
    /*The host will call this method when it wants to save the processor's internal state*/
    void getStateInformation (MemoryBlock& destData) override;
    /*This must restore the processor's state from a block of data previously created using getStateInformation()*/
    void setStateInformation (const void* data, int sizeInBytes) override;
    /*This method is used to get the parameters of the EQ effects, so that they can be used in the DJAudioPlayer class*/
    AudioProcessorValueTreeState& getParameters();

private:
    //This is the AudioProcessorValueTreeState object that will hold the parameters of the EQ effects
    AudioProcessorValueTreeState parameters;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyAudioProcessor)
};
