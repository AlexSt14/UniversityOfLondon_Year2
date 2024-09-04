/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 21 Jul 2024 2:24:21am
    Author:  alex_

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;


class DJAudioPlayer : public AudioSource
{
public:
    DJAudioPlayer(AudioFormatManager& _formatManager,
                  AudioProcessorValueTreeState& vTreeState);
    ~DJAudioPlayer() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    /*Loading audio from a file*/
    void loadURL(URL audioURL);
    /*Set the gain of the player*/
    void setGain(double gain);
    /*Set the speed of the player*/
    void setSpeed(double ratio);
    /*Set the position of the playhead in seconds*/
    void setPosition(double posInSecs);
    /*Calculates the position in seconds relative to the slider and that position*/
    void setPositionRelative(double pos);
    /*Start playing the song*/
    void start();
    /*Stop playing the song*/
    void stop();
    /*Get the relative position of the playhead*/
    double getPositionRelative();
    /*Get the position of the track in seconds*/
    double getTrackPosition();
    /*Calculating the frequencies cutoff*/
    void updateFilters();
    /*Calculating HI, MID, and LOW effects*/
    void processEQ(const AudioSourceChannelInfo& bufferToFill);
private:
    AudioFormatManager& formatManager;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	AudioTransportSource transportSource;
	ResamplingAudioSource resampleSource{ &transportSource, false };
    double sampleRate = 0.0;

    //Filter parameters, frequencies in Hz
    const double lowCutoff = 200.0;       
    const double midCenter = 1000.0;      
    const double highCutoff = 5000.0;     
    const double midWidth = 1.0;       
    //Filter objects
    IIRFilter lowPassFilterLeft;
    IIRFilter bandPassFilterLeft;
    IIRFilter highPassFilterLeft;
    IIRFilter lowPassFilterRight;
    IIRFilter bandPassFilterRight;
    IIRFilter highPassFilterRight;
    //Parameters from the AudioProcessorValueTreeState
    std::atomic<float>* lowParameter;
    std::atomic<float>* midParameter;
    std::atomic<float>* highParameter;
    std::atomic<float>* wetDryParameter;
    std::atomic<float>* roomSizeParameter;
    std::atomic<float>* dampingParameter;
    std::atomic<float>* widthParameter;
    //Reverb oject
    Reverb reverb;
    Reverb::Parameters reverbParameters;
};