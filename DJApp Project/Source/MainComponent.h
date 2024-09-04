#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "TrackInfoComponent.h"
#include "MyAudioProcessor.h"
#include "MyLookAndFeel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::ChangeListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    //==============================================================================
    //Background colour
    Colour backgroundColour { 25, 23, 26 };
    AudioFormatManager formatManager;
    //AudioProcessor for each deck
    MyAudioProcessor processorDeck1;
    MyAudioProcessor processorDeck2;
    AudioThumbnailCache thumbnailCache{ 100 };
    TrackInfoComponent trackInfo{ formatManager };
    PlaylistComponent playlist{ trackInfo };
    DJAudioPlayer audioPlayer1{ formatManager, processorDeck1.getParameters() };
    DJAudioPlayer audioPlayer2{ formatManager, processorDeck2.getParameters() };
    
    
    DeckGUI deckGUI1{ &audioPlayer1, formatManager, thumbnailCache, trackInfo, processorDeck1.getParameters() };
    DeckGUI deckGUI2{ &audioPlayer2, formatManager, thumbnailCache, trackInfo, processorDeck2.getParameters() };

    MixerAudioSource mixer;

    MyLookAndFeel lookAndFeel;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
