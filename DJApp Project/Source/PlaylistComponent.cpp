/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 19 Aug 2024 2:11:57pm
    Author:  alex_

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(TrackInfoComponent& trackInfoToUse) : trackInfo(trackInfoToUse)
{
    //Making the table use the same lookandfeel
    setLookAndFeel(&getLookAndFeel());
    tableComponent.setColour(TableListBox::backgroundColourId, backgroundColour);
    tableComponent.getHeader().addColumn("Name", 1, 400);
    tableComponent.getHeader().addColumn("Artist", 2, 200);
    tableComponent.getHeader().addColumn("Length", 3, 200);
    tableComponent.getHeader().addColumn("", 4, 200);
    tableComponent.getHeader().addColumn("", 5, 200);
    tableComponent.getHeader().addColumn("", 6, 200);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);
    trackInfo.addChangeListener(this);  //Add listener to track info
    loadPlaylistFromJson();
}

PlaylistComponent::~PlaylistComponent()
{
    trackInfo.removeChangeListener(this);
    setLookAndFeel(nullptr);
}
/*Inherited from Component class, paints over the component body*/
void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::red);
    g.drawRect (getLocalBounds(), 1);
}
/*Inherited from Component class, resizes the components inside the deck*/
void PlaylistComponent::resized()
{
    int columnWidth = getWidth()/5;
    int buttonWidth = (getWidth()/2)/4;
    tableComponent.setBounds(0,0,getWidth(), getHeight());
    tableComponent.getHeader().setColumnWidth(1,columnWidth);
    tableComponent.getHeader().setColumnWidth(2, columnWidth);
    tableComponent.getHeader().setColumnWidth(3, columnWidth);
    tableComponent.getHeader().setColumnWidth(4, buttonWidth);
    tableComponent.getHeader().setColumnWidth(5, buttonWidth);
    tableComponent.getHeader().setColumnWidth(6, buttonWidth);
}
/*Get number of rows of table*/
int PlaylistComponent::getNumRows()
{
    return trackInfo.getNumTracks();
}
/*Drawing the background of each row*/
void PlaylistComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
		g.fillAll(Colours::lightblue);
	}
    else
    {
		g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	}
}
/*This will draw a cell*/
void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    switch (columnId)
    {
    case 1:
        g.drawText(trackInfo.getTrackName(rowNumber), 2, 0, width - 4, height, Justification::centredLeft, true);
        break;
    case 2:
        g.drawText(trackInfo.getTrackArtist(rowNumber), 2, 0, width - 4, height, Justification::centredLeft, true);
        break;
    case 3:
        g.drawText(trackInfo.getTrackLength(rowNumber), 2, 0, width - 4, height, Justification::centredLeft, true);
		break;
    default:
        break;
    }
}
/*Refresh component per cell, this is where we add the buttons inside the columns*/
Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* playBtn = new TextButton{ "Load Deck 1" };
            String id{std::to_string(rowNumber)};
            playBtn->setComponentID(id);
            playBtn->addListener(this);
            playBtn->setLookAndFeel(&getLookAndFeel());
            existingComponentToUpdate = playBtn;
        }
    }
    else if (columnId == 5)
    {
        if (existingComponentToUpdate == nullptr)
        {
			TextButton* playBtn = new TextButton{ "Load Deck 2" };
			String id{std::to_string(100+rowNumber)};
			playBtn->setComponentID(id);
			playBtn->addListener(this);
            playBtn->setLookAndFeel(&getLookAndFeel());
			existingComponentToUpdate = playBtn;
		}
	}
    else if (columnId == 6)
    {
        if (existingComponentToUpdate == nullptr)
        {
			TextButton* delBtn = new TextButton{ "Remove" };
			String id{std::to_string(200+rowNumber)};
            delBtn->setComponentID(id);
            delBtn->addListener(this);
            delBtn->setLookAndFeel(&getLookAndFeel());
			existingComponentToUpdate = delBtn;
		}
	}
    return existingComponentToUpdate;
}
/*Button listener*/
void PlaylistComponent::buttonClicked(Button* button)
{
    if (button->getComponentID().getIntValue() < 100)
    {
		int id = button->getComponentID().getIntValue();
		DBG("PlaylistComponent::buttonClicked  Play DECK 1, btn id " + String(button->getComponentID()));
        playTrackOnDeck(1, id);
	}
    else if (button->getComponentID().getIntValue() < 200)
    {
		int id = button->getComponentID().getIntValue();
        DBG("PlaylistComponent::buttonClicked  Play DECK 2, btn id " + String(button->getComponentID()));
        playTrackOnDeck(2, id - 100);
	}
    else
    {
		int id = button->getComponentID().getIntValue();
		DBG("PlaylistComponent::buttonClicked  Remove, btn id " + String(button->getComponentID()));
        trackInfo.removeTrack(id - 200);
        removeSongFromJson(id - 200);
	}
}
/*Callback to update table*/
void PlaylistComponent::updateTable()
{
	tableComponent.updateContent();
}
/*Callback to update track info*/
void PlaylistComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    if (source == &trackInfo)
    {
        updateTable();
        if (trackInfo.getCurrentChangeType() == TrackInfoComponent::TrackChangeType::AddTrack)
        {
            savePlaylistToJson();
        }
	}
}
/*Last deck to play method, will trigger maincomponent to either play deck1 or deck2*/
void PlaylistComponent::playTrackOnDeck(int deckNumber, int trackIndex)
{
    if (trackIndex >= 0 && trackIndex < trackInfo.getNumTracks())
    {
        juce::URL trackURL = trackInfo.getTracks()->at(trackIndex).fileURL;
        sendChangeMessage();
        lastPlayedDeck = deckNumber;
        lastPlayedURL = trackURL;
    }
}
//To create this method I did research on the JSON class reference from the documentation and methods such as toString
// https://docs.juce.com/master/classJSON.html
//I have also taken a look at this forum post to understand how to write a string to a file
// https://forum.juce.com/t/parse-json-file-and-create-a-copy-of-it/58403
//I have also looked into the File class documentation to understand how to use methods such as getSpecialLocation and getParentDirectory, etc
// https://docs.juce.com/master/classFile.html
/*Saving the current playlist to a json file*/
void PlaylistComponent::savePlaylistToJson()
{
    File playlistFile = File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile("playlist.json");
    String jsonString;
    //If a file already exists, we will append the next track to the json object
    //Doing so, we are not running a for loop to iterate through all the tracks
    if (playlistFile.existsAsFile()) {
        int nextTrackIndex = trackInfo.getNumTracks();
        String jsonContent = playlistFile.loadFileAsString();
        var jsonObject = JSON::parse(jsonContent);
        if (jsonObject.isArray()) {
            DynamicObject* nextTrackObject = new DynamicObject();
            nextTrackObject->setProperty("name", trackInfo.getTrackName(nextTrackIndex-1));
            nextTrackObject->setProperty("artist", trackInfo.getTrackArtist(nextTrackIndex-1));
            nextTrackObject->setProperty("album", trackInfo.getTrackAlbum(nextTrackIndex-1));
            nextTrackObject->setProperty("length", trackInfo.getTrackLength(nextTrackIndex-1));
            nextTrackObject->setProperty("url", trackInfo.getTracks()->at(nextTrackIndex-1).fileURL.toString(false));

            jsonObject.append(nextTrackObject);
        }
        jsonString = JSON::toString(jsonObject);
	}
    //Creating a json object if the file doesn't exist
    //Iterating through the tracks and adding them to the json object
    else {
        var playlistArray = var(Array<var>());
        for (int i = 0; i < trackInfo.getNumTracks(); ++i)
        {
			DynamicObject* trackObject = new DynamicObject();
			trackObject->setProperty("name", trackInfo.getTrackName(i));
			trackObject->setProperty("artist", trackInfo.getTrackArtist(i));
			trackObject->setProperty("album", trackInfo.getTrackAlbum(i));
			trackObject->setProperty("length", trackInfo.getTrackLength(i));
			trackObject->setProperty("url", trackInfo.getTracks()->at(i).fileURL.toString(false));

			playlistArray.append(trackObject);
		}
		jsonString = JSON::toString(playlistArray);
	}
    if (playlistFile.hasWriteAccess()) {
        playlistFile.replaceWithText(jsonString);
        DBG("PlaylistComponent::savePlaylistToJson - Playlist saved to json file");
    }
    else {
		DBG("PlaylistComponent::savePlaylistToJson - No write access to the directory");   //No write access to the directory
	}
}
/*Loading the playlist from a json file*/
void PlaylistComponent::loadPlaylistFromJson()
{
    //Reading the json file
    File playlistFile = File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile("playlist.json");
    if (playlistFile.existsAsFile()) {
        String jsonContent = playlistFile.loadFileAsString();
        var parsedJson = JSON::parse(jsonContent);
        //Retrieving the tracks from the json
        trackInfo.retrieveTracksFromJson(parsedJson);
    }
}
//To avoid iterating through a for loop each time and rewriting the entire track list to the json object, after we remove a track
//I'm using the row index which matches the index of the track in the json object and directly removing the correct track, giving us O(1) complexity for this operation
/*Removing a song from the playlist jsong object*/
void PlaylistComponent::removeSongFromJson(int index)
{
    File playlistFile = File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile("playlist.json");
    if (playlistFile.existsAsFile())
    {
        String jsonString = playlistFile.loadFileAsString();
        var jsonObject = JSON::parse(jsonString);
        if (jsonObject.isArray())
        {
			jsonObject.remove(index);
			jsonString = JSON::toString(jsonObject);
			playlistFile.replaceWithText(jsonString);
		}
    }
    else
    {
        DBG("PlaylistComponent::removeSongFromJson - File not found");  //This shouldn't happen anyway, because the file should exist, it is created when the first track is added  
    }

}