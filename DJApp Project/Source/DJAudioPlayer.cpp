/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 21 Jul 2024 2:24:21am
    Author:  alex_

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager,
                             AudioProcessorValueTreeState& vTreeState) 
    : formatManager(_formatManager), 
      lowParameter(vTreeState.getRawParameterValue("low")), 
      midParameter(vTreeState.getRawParameterValue("mid")), 
      highParameter(vTreeState.getRawParameterValue("high")),
      wetDryParameter(vTreeState.getRawParameterValue("wetDry")),
      roomSizeParameter(vTreeState.getRawParameterValue("roomSize")),
      dampingParameter(vTreeState.getRawParameterValue("damping")),
      widthParameter(vTreeState.getRawParameterValue("width"))
{
    updateFilters();
    reverbParameters.freezeMode = false;
    reverb.setParameters(reverbParameters);
}
DJAudioPlayer::~DJAudioPlayer()
{

}
//==============================================================================
/*Inherited from AudioSource class, prepares the player to play audio*/
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    this->sampleRate = sampleRate;
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    updateFilters();
}
/*Inherited from AudioSource and is called when the audio is ready for the next block of audio data*/
void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);

    //Processing the HI, MID, and LOW effects
    processEQ(bufferToFill);

    //Processing the reverb effect
    reverbParameters.wetLevel = wetDryParameter->load();
    reverbParameters.dryLevel = 1.0f - wetDryParameter->load();
    reverbParameters.roomSize = roomSizeParameter->load();
    reverbParameters.damping = dampingParameter->load();
    reverbParameters.width = widthParameter->load();
    reverb.setParameters(reverbParameters);
    reverb.processStereo(bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample),
        						 bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample),
        						 bufferToFill.numSamples);
}
/*Inherited from AudioSource class, releases the resources used by the player*/
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}
/*Loading audio from a file*/
void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}
/*Set the gain of the player*/
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0.0 || gain > 1.0) {
        DBG("DJAudioPlayer::setGain - Gain out of range. Should be between 0 and 1.");
    }
    else transportSource.setGain(gain);
}
/*Set the speed of the player*/
void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0.0 || ratio > 100.0) {
		DBG("DJAudioPlayer::setSpeed - Speed out of range. Should be between 0 and 100.");
	}
	else resampleSource.setResamplingRatio(ratio);
}
/*Sets the position*/
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}
/*Calculates the position in seconds relative to the slider and that position*/
void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0.0 || pos > 1.0) {
        DBG("DJAudioPlayer::setPositionRelative - Pos out of range. Should be between 0 and 1.");
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}
/*Start playing*/
void DJAudioPlayer::start()
{
    std::cout << "Play button clicked" << std::endl;
    DBG("Play button clicked");
    transportSource.start();
}
/*Stop playing*/
void DJAudioPlayer::stop()
{
    std::cout << "Stop button clicked" << std::endl;
    DBG("Stop button clicked");
    transportSource.stop();
}
/*Get the relative position of the playhead, checking for division by zero*/
double DJAudioPlayer::getPositionRelative()
{
    if (transportSource.getLengthInSeconds() == 0) return 0;
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
/*Get the length of the audio file in seconds*/
double DJAudioPlayer::getTrackPosition()
{
    return transportSource.getCurrentPosition();
}
/*Calculating the cutoff frequencies*/
void DJAudioPlayer::updateFilters()
{
    //Terminating the function if the sample rate is not set
    if (sampleRate <= 0)
        return;
    IIRCoefficients lowPassCoeffs = IIRCoefficients::makeLowPass(sampleRate, lowCutoff);
    IIRCoefficients bandPassCoeffs = IIRCoefficients::makeBandPass(sampleRate, midCenter, midWidth);
    IIRCoefficients highPassCoeffs = IIRCoefficients::makeHighPass(sampleRate, highCutoff);

    lowPassFilterLeft.setCoefficients(lowPassCoeffs);
    lowPassFilterRight.setCoefficients(lowPassCoeffs);
    bandPassFilterLeft.setCoefficients(bandPassCoeffs);
    bandPassFilterRight.setCoefficients(bandPassCoeffs);
    highPassFilterLeft.setCoefficients(highPassCoeffs);
    highPassFilterRight.setCoefficients(highPassCoeffs);

}
/*Calculating HI, MID, and LOW effects*/
void DJAudioPlayer::processEQ(const AudioSourceChannelInfo& bufferToFill)
{
    //Calculating the high, mid and low frequencies for project extension
    if (sampleRate <= 0)
        return;

    //Getting pointers to the buffer's channels
    auto* leftChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightChannel = bufferToFill.buffer->getNumChannels() > 1 ?    //Checking if there is a right channel
        bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample) : nullptr;
    //Processing the audio samples
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float leftSample = leftChannel[sample];
        float lowLeft = lowPassFilterLeft.processSingleSampleRaw(leftSample) * *lowParameter;
        float midLeft = bandPassFilterLeft.processSingleSampleRaw(leftSample) * *midParameter;
        float highLeft = highPassFilterLeft.processSingleSampleRaw(leftSample) * *highParameter;
        leftChannel[sample] = lowLeft + midLeft + highLeft;

        //Processing right channel if available
        if (rightChannel != nullptr)
        {
            float rightSample = rightChannel[sample];
            float lowRight = lowPassFilterRight.processSingleSampleRaw(rightSample) * *lowParameter;
            float midRight = bandPassFilterRight.processSingleSampleRaw(rightSample) * *midParameter;
            float highRight = highPassFilterRight.processSingleSampleRaw(rightSample) * *highParameter;
            rightChannel[sample] = lowRight + midRight + highRight;
        }
    }
}