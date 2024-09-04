/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 5 Aug 2024 10:20:29am
    Author:  alex_

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
                                AudioThumbnailCache& cacheToUse) 
                                : thumbnail(1000, formatManagerToUse, cacheToUse),
                                fileLoaded(false),
                                relativePosition(0.0),
                                minutes(0.0),
                                seconds(0.0)
{
    thumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll (backgroundColour);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    if (fileLoaded) {
        //Drawing the waveform
        g.setColour(juce::Colours::deepskyblue);
        thumbnail.drawChannel(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 0, 1.0f);
        //Drawing the playhead
        g.setColour(Colours::aliceblue);
        g.drawRect(relativePosition * getWidth(), 0, getWidth() / 20, getHeight()-20);
        //Drawing the total length of the song
        g.setColour(Colours::white);
        g.setFont(Font(12.0f));
        int textX = 10;
        int textY = getHeight() - 20;
        String formattedLength = String::formatted("Length: %.0f:%.0f", minutes,seconds);
        g.drawText(formattedLength, textX, textY, getWidth() - textX, 20, Justification::left);
    }
    else {
        g.setColour(juce::Colours::deepskyblue);
        g.setFont(juce::FontOptions(20.0f));
        g.drawText("Load a file!", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
}

void WaveformDisplay::loadURL(URL audioURL)
{
    DBG("WaveformDisplay::loadURL");
    thumbnail.clear();
    fileLoaded = thumbnail.setSource(new URLInputSource(audioURL));
    if (fileLoaded) DBG("WaveformDisplay::loadURL - Loaded");
	else DBG("WaveformDisplay::loadURL - Failed to load");
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    DBG("WaveformDisplay::changeListenerCallback CHANGE RECEIVED");
    repaint();
}
/*Set the relative position of the playhead and the timer of the track*/
void WaveformDisplay::setPosition(double relativePos, double posInSecs)
{
    if (relativePos != relativePosition)
    {
        relativePosition = relativePos;
        seconds = fmod(posInSecs, 59.0);
        minutes = floor(posInSecs / 59.0);
        repaint();
        DBG("WaveformDisplay::setPositionRelative - Minutes " + String(minutes) + " pos is: " + String(posInSecs));
    }
}
