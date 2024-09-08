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
 /*Inherited from AudioSource class, prepares the player to play audio*/
void MyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}
/*Inherited from AudioSource class, releases the resources used by the player*/
void MyAudioProcessor::releaseResources()
{
}
/*Pure virtual methods required to be implemented, however, as I explained, not many are being used for my purpose,
some or them are being implemented as empty methods. A MINIMUM Implementation was given so that I can use the class alongside the vTreeState*/
/*Renders the next block*/
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
/*Returns the length of the processor's tail, in seconds*/
double MyAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
/*Returns true if the processor wants MIDI messages*/
bool MyAudioProcessor::acceptsMidi() const
{
    return false;
}
/*Returns true if the processor produces MIDI messages*/
bool MyAudioProcessor::producesMidi() const
{
    return false;
}
/*Returns true if this is a MIDI effect plug-in and does no audio processing*/
bool MyAudioProcessor::isMidiEffect() const
{
    return false;
}
/*Returns the number of preset programs the processor supports*/
int MyAudioProcessor::getNumPrograms()
{
    return 1;
}
/*Returns the number of the currently active program*/
int MyAudioProcessor::getCurrentProgram()
{
    return 0;
}
/*Called by the host to change the current program*/
void MyAudioProcessor::setCurrentProgram(int index)
{
}
/*Must return the name of a given program*/
const String MyAudioProcessor::getProgramName(int index)
{
    return {};
}
/*Called by the host to rename a program*/
void MyAudioProcessor::changeProgramName(int index, const String& newName)
{
}
/*The host will call this method when it wants to save the processor's internal state*/
void MyAudioProcessor::getStateInformation(MemoryBlock& destData)
{
}
/*This must restore the processor's state from a block of data previously created using getStateInformation()*/
void MyAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}
/*This method is used to get the parameters of the EQ effects, so that they can be used in the DJAudioPlayer class*/
AudioProcessorValueTreeState& MyAudioProcessor::getParameters()
{
	return parameters;
}