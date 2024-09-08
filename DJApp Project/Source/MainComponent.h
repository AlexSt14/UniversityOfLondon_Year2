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
    /*Inherited from AudioSource class, prepares the player to play audio*/
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    /*Inherited from AudioSource and is called when the audio is ready for the next block of audio data*/
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    /*Inherited from AudioSource class, releases the resources used by the player*/
    void releaseResources() override;

    //==============================================================================
    /*Inherited from Component class, paints over the component body*/
    void paint (juce::Graphics& g) override;
    /*Inherited from Component class, resizes the components inside the deck*/
    void resized() override;
    /*Waiting for a change listener from within the playlist component, which will help decide which deck will thetrack be played on*/
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
