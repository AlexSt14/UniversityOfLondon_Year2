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

    void paint (Graphics&) override;
    void resized() override;
    void loadURL(URL audioURL);
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
