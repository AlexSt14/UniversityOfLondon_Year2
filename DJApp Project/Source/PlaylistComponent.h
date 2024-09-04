/*
  ==============================================================================

    PlaylistComponent.h
    Created: 19 Aug 2024 2:11:57pm
    Author:  alex_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "TrackInfoComponent.h"

using namespace juce;

//==============================================================================
/*
*/
class PlaylistComponent  : public Component,
                           public TableListBoxModel,
                           public Button::Listener,
                           public ChangeListener,
                           public ChangeBroadcaster
{
public:
    PlaylistComponent(TrackInfoComponent& trackInfoToUse);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    /*Get number of rows of table*/
    int getNumRows() override;
    /*Drawing the background of each row*/
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    /*This will draw a cell*/
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    /*Refresh component per cell*/
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    /*Button listener*/
    void buttonClicked(Button* button) override;
    /*Callback to update table*/
    void updateTable();
    /*Callback to update track info*/
    void changeListenerCallback(ChangeBroadcaster* source) override;
    /*Last deck to play method, will trigger maincomponent to either play deck1 or deck2*/
    void playTrackOnDeck(int deckNumber, int trackIndex);
    //To create this method I did research on the JSON class reference from the documentation and methods such as toString
    // https://docs.juce.com/master/classJSON.html
    //I have also taken a look at this forum post to understand how to write a string to a file
    // https://forum.juce.com/t/parse-json-file-and-create-a-copy-of-it/58403
    //I have also looked into the File class documentation to understand how to use methods such as getSpecialLocation and getParentDirectory, etc
    // https://docs.juce.com/master/classFile.html
    /*Saving the current playlist to a json file*/
    void savePlaylistToJson();
    /*Loading the playlist from a json file*/
    void loadPlaylistFromJson();
    /*Removing a song from the playlist jsong object*/
    void removeSongFromJson(int index);

    /*Variables for maincomponent to communicate between playlist and deck*/
    int lastPlayedDeck = 0;
    juce::URL lastPlayedURL;

private:
    Colour backgroundColour = Colour{ 25, 23, 26 };
    TableListBox tableComponent;
    TrackInfoComponent& trackInfo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
