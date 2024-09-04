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
    some or them are being implemented as empty methods*/
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    /*Creating an editor for the EQ effect*/
    AudioProcessorEditor* createEditor() override;
    /*Checking for editor*/
    bool hasEditor() const override;
    /*Returning the name of the processor*/
    const String getName() const override;

    double getTailLengthSeconds() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    /*This method is used to get the parameters of the EQ effect, so that they can be used in the DJAudioPlayer class*/
    AudioProcessorValueTreeState& getParameters();

private:
    //This is the AudioProcessorValueTreeState object that will hold the parameters of the EQ effect
    AudioProcessorValueTreeState parameters;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyAudioProcessor)
};
