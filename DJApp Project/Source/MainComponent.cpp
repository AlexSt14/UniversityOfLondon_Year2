#include "MainComponent.h"
#include <JuceHeader.h>

//==============================================================================
MainComponent::MainComponent()
{
    setLookAndFeel(&lookAndFeel);
    playlist.setLookAndFeel(&lookAndFeel);
    DBG("MainComponent constructor called");
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlist);

    // Add change listener to playlist
    playlist.addChangeListener(this);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
/*Inherited from AudioSource class, prepares the player to play audio*/
//Delegating the prepareToPlay method to the audio players and mixer
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioPlayer1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    audioPlayer2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixer.addInputSource(&audioPlayer1, false);
    mixer.addInputSource(&audioPlayer2, false);
}
/*Inherited from AudioSource and is called when the audio is ready for the next block of audio data*/
//Delegating the getNextAudioBlock method to the mixer
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixer.getNextAudioBlock(bufferToFill);
}
/*Inherited from AudioSource class, releases the resources used by the player*/
//Delegating the releaseResources method to the audio players and mixer
void MainComponent::releaseResources()
{
    audioPlayer1.releaseResources();
    audioPlayer2.releaseResources();
    mixer.releaseResources();
}

//==============================================================================
/*Inherited from Component class, paints over the component body*/
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (backgroundColour);

    // You can add your drawing code here!

}
/*Inherited from Component class, resizes the components inside the deck*/
void MainComponent::resized()
{
    int deckGUIWidth = getWidth()/2;
    int deckGUIHeight = getHeight()/5*3;
    int playlistHeight = getHeight()/5*2;
    int playlistWidth = getWidth();
    int playlistY = getHeight()/5*3;
    deckGUI1.setBounds(0,0, deckGUIWidth, deckGUIHeight);
    deckGUI2.setBounds(getWidth()/2,0, deckGUIWidth, deckGUIHeight);
    playlist.setBounds(0, playlistY, playlistWidth, playlistHeight);
}
/*Waiting for a change listener from within the playlist component, which will help decide which deck will thetrack be played on*/
void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &playlist)
    {
        if (playlist.lastPlayedDeck == 1)
        {
            deckGUI1.playTrack(playlist.lastPlayedURL);
        }
        else if (playlist.lastPlayedDeck == 2)
		{
			deckGUI2.playTrack(playlist.lastPlayedURL);
		}
    }
}