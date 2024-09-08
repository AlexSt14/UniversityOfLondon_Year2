/*
  ==============================================================================

    DeckGUI.cpp
    Created: 29 Jul 2024 9:34:33am
    Author:  alex_

  ==============================================================================
*/

#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                AudioFormatManager& formatManagerToUse,
                AudioThumbnailCache& cacheToUse,
                TrackInfoComponent& trackInfoToUse,
                AudioProcessorValueTreeState& vTreeStateToUse)
    : player(_player), waveform(formatManagerToUse, cacheToUse), trackInfo(trackInfoToUse), vTreeState(vTreeStateToUse)
{
    //Buttons and sliders
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(waveform);
    addAndMakeVisible(highSlider);
    addAndMakeVisible(midSlider);
    addAndMakeVisible(lowSlider);
    addAndMakeVisible(wetDrySlider);
    addAndMakeVisible(roomSizeSlider);
    addAndMakeVisible(dampingSlider);
    addAndMakeVisible(widthSlider);

    //Labels
    addAndMakeVisible(highLabel);
    highLabel.setText("HI", dontSendNotification);
    highLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(midLabel);
    midLabel.setText("MID", dontSendNotification);
    midLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(lowLabel);
    lowLabel.setText("LOW", dontSendNotification);
    lowLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(volLabel);
    volLabel.setText("VOL", dontSendNotification);
    volLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(speedLabel);
    speedLabel.setText("SPEED", dontSendNotification);
    speedLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(positionLabel);
    positionLabel.setText("POS", dontSendNotification);
    positionLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(wetDryLabel);
    wetDryLabel.setText("WET/DRY", dontSendNotification);
    wetDryLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(roomSizeLabel);
    roomSizeLabel.setText("Room Size", dontSendNotification);
    roomSizeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(dampingLabel);
    dampingLabel.setText("Damping", dontSendNotification);
    dampingLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(widthSliderLabel);
    widthSliderLabel.setText("Width", dontSendNotification);
    widthSliderLabel.setJustificationType(Justification::centred);

    //Sliders styles
    volSlider.setSliderStyle(Slider::LinearVertical);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    speedSlider.setSliderStyle(Slider::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    positionSlider.setSliderStyle(Slider::LinearVertical);
    positionSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    highSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    highSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    midSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    midSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    lowSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    lowSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    wetDrySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    wetDrySlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    roomSizeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    dampingSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dampingSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    widthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    //Slider attachments
    highSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "high", highSlider);
    midSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "mid", midSlider);
    lowSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "low", lowSlider);
    wetDrySliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "wetDry", wetDrySlider);
    roomSizeSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "roomSize", roomSizeSlider);
    dampingSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "damping", dampingSlider);
    widthSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "width", widthSlider);

    //Listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    positionSlider.addListener(this);
    highSlider.addListener(this);
    wetDrySlider.addListener(this);

    //Sliders ranges
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 5.0);
    positionSlider.setRange(0.0, 1.0);
    highSlider.setRange(0.0, 1.0);
    midSlider.setRange(0.0, 1.0);
    lowSlider.setRange(0.0, 1.0);
    wetDrySlider.setRange(0.0, 1.0);
    roomSizeSlider.setRange(0.0, 1.0);
    dampingSlider.setRange(0.0, 1.0);
    widthSlider.setRange(0.0, 1.0);
    //Timer callback every 500ms
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}
/*Inherited from Component class, paints over the component body*/
void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1); 
}
/*Inherited from Component class, resizes the components inside the deck*/
void DeckGUI::resized()
{
    double rowHeight = getHeight() / 11;
    double rowWidth = getWidth();
    //Equalizer dimensions
    double eqHeight = rowHeight * 3;
    double eqWidth = rowWidth / 3;
    double eqX = 0;
    double eqY = rowHeight * 7;
    //Buttons and sliders
    double btnWidth = rowWidth / 3;
    double btnHeight = rowHeight;
    //Sliders
    double sliderWidth = rowWidth / 6;
    double sliderHeight = rowHeight * 5 - 20;
    //Reverb thumbs
    double thumbWidth = (rowWidth / 3) / 2;
    double thumbHeight = rowHeight * 3;

    waveform.setBounds(0, 0, rowWidth, rowHeight * 2);
    //Sliders and buttons
    volSlider.setBounds(0, rowHeight * 2, sliderWidth, sliderHeight);
    speedSlider.setBounds(sliderWidth, rowHeight * 2, sliderWidth, sliderHeight);
    positionSlider.setBounds(sliderWidth * 2, rowHeight * 2, sliderWidth, sliderHeight);
    highSlider.setBounds(eqX, eqY, eqWidth, eqHeight - 20);
    midSlider.setBounds(eqX + eqWidth, eqY, eqWidth, eqHeight - 20);
    lowSlider.setBounds(eqX + eqWidth * 2, eqY, eqWidth, eqHeight - 20);
    playButton.setBounds(0, rowHeight * 10, btnWidth, btnHeight);
    stopButton.setBounds(btnWidth, rowHeight * 10, btnWidth, btnHeight);
    loadButton.setBounds(btnWidth*2, rowHeight * 10, btnWidth, rowHeight);
    wetDrySlider.setBounds(sliderWidth * 3 + 10, rowHeight * 2, thumbWidth, thumbHeight - 20);
    roomSizeSlider.setBounds(sliderWidth * 3 + thumbWidth+40, rowHeight * 2, thumbWidth, thumbHeight - 20);
    dampingSlider.setBounds(sliderWidth * 3 + 10, rowHeight * 2 + thumbHeight - 20, thumbWidth, thumbHeight - 20);
    widthSlider.setBounds(sliderWidth * 3 + thumbWidth+40, rowHeight * 2 + thumbHeight - 20, thumbWidth, thumbHeight - 20);
    //Labels
    highLabel.setBounds(eqX, eqY +eqHeight - 20, eqWidth, 20);
    midLabel.setBounds(eqX + eqWidth, eqY + eqHeight - 20, eqWidth, 20);
    lowLabel.setBounds(eqX + eqWidth * 2, eqY + eqHeight - 20, eqWidth, 20);
    volLabel.setBounds(0, rowHeight * 7-20, sliderWidth, 20);
    speedLabel.setBounds(sliderWidth, rowHeight * 7-20, sliderWidth, 20);
    positionLabel.setBounds(sliderWidth * 2, rowHeight * 7-20, sliderWidth, 20);
    wetDryLabel.setBounds(sliderWidth * 3 + 10, rowHeight * 2 + thumbHeight - 40, thumbWidth, 20);
    roomSizeLabel.setBounds(sliderWidth * 3 + thumbWidth+40, rowHeight * 2 + thumbHeight - 40, thumbWidth, 20);
    dampingLabel.setBounds(sliderWidth * 3 + 10, rowHeight * 2 + thumbHeight * 2 - 50, thumbWidth, 20);
    widthSliderLabel.setBounds(sliderWidth * 3 + thumbWidth+40, rowHeight * 2 + thumbHeight * 2 - 50, thumbWidth, 20);
}
/*Implement button listener*/
void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        player->start();
    }
    else if (button == &stopButton)
    {
        player->stop();
    }
    else if (button == &loadButton)     //Loading files through the file browser
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            File chosenfile = chooser.getResult();
            player->loadURL(URL{chosenfile});
            waveform.loadURL(URL{chosenfile});
            setSlidersPosition();
            trackInfo.addTrack(chosenfile);
            DBG("DeckGUI::trackLength - " + juce::String(trackInfo.getNumTracks()));
        });
    }
}
/*Implement slider listener*/
void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    else if (slider == &positionSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}
/*Callback to check whether the target accepts/interested in files*/
bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    DBG("DeckGUI::isInterestedInFileDrag - Checking if the target is interested in the files");
    return true;
}
/*Callback to handle the files dropped on the target*/
void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
    DBG("DeckGUI::filesDropped - File has been dropped on the target");
    DBG(files[0]);
    if (files.size() == 1) {
        player->loadURL(URL{ File{files[0]} });
        waveform.loadURL(URL{ File{files[0]} });
        trackInfo.addTrack(File{files[0]});
        setSlidersPosition();
    }
}
/*Setting up sliders position once files are loaded, this will also reset the sliders at their default position if sliders have been touched before*/
void DeckGUI::setSlidersPosition()
{
    volSlider.setValue(1.0);
    speedSlider.setValue(1.0);
    positionSlider.setValue(0.0);
    highSlider.setValue(1.0);
    midSlider.setValue(1.0);
    lowSlider.setValue(1.0);
}
/*Implement timer callback*/
void DeckGUI::timerCallback()
{
    waveform.setPosition(player->getPositionRelative(), player->getTrackPosition());
    positionSlider.setValue(player->getPositionRelative());
}
/*Plays a track on a deck, called from MainComponent, that's where it is decided which deck will be played on*/
void DeckGUI::playTrack(const juce::URL& trackURL)
{
    player->loadURL(trackURL);
    waveform.loadURL(trackURL);
    setSlidersPosition();
}