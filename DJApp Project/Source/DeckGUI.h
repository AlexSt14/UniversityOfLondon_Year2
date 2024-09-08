/*
  ==============================================================================

    DeckGUI.h
    Created: 29 Jul 2024 9:34:33am
    Author:  alex_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "TrackInfoComponent.h"
using namespace juce;

//==============================================================================
/*
*/
class DeckGUI  : public Component,
    		     public Button::Listener,
				 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer

{
public:
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager& formatManagerToUse,
            AudioThumbnailCache& cacheToUse,            
            TrackInfoComponent& trackInfoToUse,
            AudioProcessorValueTreeState& vTreeStateToUse);
    ~DeckGUI() override;
    /*Inherited from Component class, paints over the component body*/
    void paint (Graphics&) override;
    /*Inherited from Component class, resizes the components inside the deck*/
    void resized() override;
    /*Implement button listener*/
    void buttonClicked(Button*) override;
    /*Implement slider listener*/
    void sliderValueChanged(Slider* slider) override;
    /*Callback to check whether the target accepts/interested in files*/
    bool isInterestedInFileDrag(const StringArray& files) override;
    /*Callback to handle the files dropped on the target*/
    void filesDropped(const StringArray& files, int x, int y) override;
    /*Setting up sliders position once files are loaded*/
    void setSlidersPosition();
    /*Implement timer callback*/
    void timerCallback() override;
    /*Plays a track on a deck, called from MainComponent, that's where it is decided which deck will be played on*/
    void playTrack(const URL& trackURL);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
    //Background colour
    Colour backgroundColour{ 25, 23, 26 };
    //File chooser for browsing audio files
    FileChooser fChooser{ "Select an audio file" };
    //Buttons for play, stop, and load
    TextButton playButton{ "Play" };
    TextButton stopButton{ "Stop" };
    TextButton loadButton{ "Browse" };
    //Sliders for volume, speed, position, and effects
    Slider volSlider;
    Slider speedSlider;
    Slider positionSlider;
    Slider highSlider;
    Slider midSlider;
    Slider lowSlider;
    Slider wetDrySlider;
    Slider roomSizeSlider;
    Slider dampingSlider;
    Slider widthSlider;
    //Track info component
    TrackInfoComponent& trackInfo;
    //Slider Attachments for linking with ValueTreeState parameters
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wetDrySliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
    //DJAudioPlayer, waveform and vTreeState instances
    DJAudioPlayer* player;
    WaveformDisplay waveform;
    AudioProcessorValueTreeState& vTreeState;
    
    //Labels for my buttons and sliders
    Label highLabel, midLabel, lowLabel, volLabel, speedLabel, positionLabel, wetDryLabel, roomSizeLabel, dampingLabel, widthSliderLabel;
};
