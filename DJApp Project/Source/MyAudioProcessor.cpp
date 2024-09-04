/*
  ==============================================================================

    MyAudioProcessor.cpp
    Created: 2 Sep 2024 9:43:16am
    Author:  alex_

  ==============================================================================
*/

/*So that I am able to implement the high, mid and low frequency filter it was needed for me to create this class, and implement all these virtual functions,
however, not many of these functions are used, due to the EQ effect being applied inside the DJAudioPlayer. I decided to make this as a separate class and not
inherit AudioProcessor in another class such as DJAudioPlayer due to AudioProcessor having a lot of pure virtual methods, it is cleaner this way*/

#include <JuceHeader.h>
#include "MyAudioProcessor.h"

//==============================================================================
/*Setting up the parameters low, mid and high in the AudioProcessorValueTreeState*/
MyAudioProcessor::MyAudioProcessor() : parameters (*this, nullptr, "Parameters", {
                  std::make_unique<AudioParameterFloat>("low", "Low", 0.0f, 1.0f, 1.0f),
                  std::make_unique<AudioParameterFloat>("mid", "Mid", 0.0f, 1.0f, 1.0f),
                  std::make_unique<AudioParameterFloat>("high", "High", 0.0f, 1.0f, 1.0f),
                  std::make_unique<AudioParameterFloat>("wetDry", "WetDry", 0.0f, 1.0f, 0.0f),
                  std::make_unique<AudioParameterFloat>("roomSize", "RoomSize", 0.0f, 1.0f, 0.0f),
                  std::make_unique<AudioParameterFloat>("damping", "Damping", 0.0f, 1.0f, 0.0f),
                  std::make_unique<AudioParameterFloat>("width", "Width", 0.0f, 1.0f, 1.0f)
              })
{
}

MyAudioProcessor::~MyAudioProcessor()
{
}

//==============================================================================
void MyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}
void MyAudioProcessor::releaseResources()
{
}
/*Pure virtual methods required to be implemented, however, as I explained, not many are being used for my purpose,
some or them are being implemented as empty methods*/
void MyAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}
/*Creating an editor for the EQ effect*/
AudioProcessorEditor* MyAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor(*this);
}
/*Checking for editor*/
bool MyAudioProcessor::hasEditor() const
{
    return true;
}
/*Returning the name of the processor*/
const String MyAudioProcessor::getName() const
{
    return "GenericAudioProcessor";
}
double MyAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
bool MyAudioProcessor::acceptsMidi() const
{
    return false;
}
bool MyAudioProcessor::producesMidi() const
{
    return false;
}
bool MyAudioProcessor::isMidiEffect() const
{
    return false;
}

int MyAudioProcessor::getNumPrograms()
{
    return 1;
}
int MyAudioProcessor::getCurrentProgram()
{
    return 0;
}
void MyAudioProcessor::setCurrentProgram(int index)
{
}
const String MyAudioProcessor::getProgramName(int index)
{
    return {};
}
void MyAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void MyAudioProcessor::getStateInformation(MemoryBlock& destData)
{
}
void MyAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}
/*This method is used to get the parameters of the EQ effect, so that they can be used in the DJAudioPlayer class*/
AudioProcessorValueTreeState& MyAudioProcessor::getParameters()
{
	return parameters;
}