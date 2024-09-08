/*
  ==============================================================================

    WaveformDisplay.h
    Created: 5 Aug 2024 10:20:29am
    Author:  alex_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/
class WaveformDisplay  : public Component,
						 private ChangeListener

{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;
    /*Inherited from Component class, paints over the component body*/
    void paint (Graphics&) override;
    /*Inherited from Component class, resizes the components inside the deck*/
    void resized() override;
    /*Load the audio file to be displayed on the waveform*/
    void loadURL(URL audioURL);
    /*Inherited from ChangeListener class, listens for changes in the audio thumbnail*/
    void changeListenerCallback(ChangeBroadcaster* source) override;
    /*Set the relative position of the playhead and the timer of the track*/
    void setPosition(double relativePos, double posInSecs);

private:
    Colour backgroundColour = Colour{ 25, 23, 26 };
    AudioThumbnail thumbnail;
    bool fileLoaded;
    double relativePosition;
    double minutes;
    double seconds;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
