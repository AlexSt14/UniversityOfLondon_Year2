/*
  ==============================================================================

    TrackInfoComponent.cpp
    Created: 20 Aug 2024 9:09:17pm
    Author:  alex_

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackInfoComponent.h"

//==============================================================================
TrackInfoComponent::TrackInfoComponent(AudioFormatManager& formatManagerToUse) : formatManager(formatManagerToUse)
{
}

TrackInfoComponent::~TrackInfoComponent()
{
}

/*Adding a track to the tracks data structure, it requires a file as parameter*/
void TrackInfoComponent::addTrack(File file)
{
    if (file.existsAsFile())
    {
        auto* reader = formatManager.createReaderFor(file);

        if (reader != nullptr)
        {
			TrackInfo track;
			track.title = file.getFileNameWithoutExtension();
            DBG("Track title: " + track.title); 
            reader->metadataValues.getValue("artist", track.artist);
            reader->metadataValues.getValue("album", track.album);
            int lengthInSeconds = reader->lengthInSamples / reader->sampleRate;
            track.length = String(lengthInSeconds / 60) + ":" + String(lengthInSeconds % 60);
            track.fileURL = URL(file);
            tracks.push_back(track);
            DBG("Track vector size: " + String(tracks.size()));  
            delete reader;
            sendCustomChangeMessage(TrackChangeType::AddTrack);  //Will notify all listeners that a track has been added
		}
    }
}
/*Retrieve tracks from json file*/
void TrackInfoComponent::retrieveTracksFromJson(var jsonObject)
{  
    if (jsonObject.isArray()) {
        for (int i = 0; i < jsonObject.size(); ++i) {
            if (jsonObject[i].isObject()) {
                TrackInfo track;
                track.title = jsonObject[i].getProperty("name", "");
                track.artist = jsonObject[i].getProperty("artist", "");
                track.album = jsonObject[i].getProperty("album", "");
                track.length = jsonObject[i].getProperty("length", "");
                track.fileURL = URL(jsonObject[i].getProperty("url", ""));

                tracks.push_back(track);
            }
        }
    }
}
/*Removing a track from the tracks data structure, it requires the index of the track to be removed*/
void TrackInfoComponent::removeTrack(int index)
{
    if (index >= 0 && index < tracks.size())
    {
        tracks.erase(tracks.begin() + index);
        sendCustomChangeMessage(TrackChangeType::RemoveTrack);  //Will notify all listeners that a track has been removed 
    }
}
/*Returns back the number of tracks inside the tracks data structure*/
int TrackInfoComponent::getNumTracks()
{
    return tracks.size();
}
/*Returns the track name info of a specific track, it requires the index of the track*/
String TrackInfoComponent::getTrackName(int index) const
{
    return (index >= 0 && index < tracks.size()) ? tracks[index].title : "";
}
/*Returns the track artist info of a specific track, it requires the index of the track*/
String TrackInfoComponent::getTrackArtist(int index) const
{
    return (index >= 0 && index < tracks.size()) ? tracks[index].artist : "";
}
/*Returns the track album info of a specific track, it requires the index of the track*/
String TrackInfoComponent::getTrackAlbum(int index) const
{
	return (index >= 0 && index < tracks.size()) ? tracks[index].album : "";
}
/*Returns the track length info of a specific track, it requires the index of the track*/
String TrackInfoComponent::getTrackLength(int index) const
{
	return (index >= 0 && index < tracks.size()) ? tracks[index].length : "not found";
}
/*Returns a pointer to the tracks data structure*/
std::vector<TrackInfoComponent::TrackInfo>* TrackInfoComponent::getTracks()
{
    return &tracks;
}
/*Custom change message that will update the currentChangeType for information purposes required by the playlistComponent*/
void TrackInfoComponent::sendCustomChangeMessage(TrackChangeType changeType)
{
    currentChangeType = changeType;
    sendChangeMessage();
}
/*Exposing the currentChangeType at request for playlistComponent*/
TrackInfoComponent::TrackChangeType TrackInfoComponent::getCurrentChangeType()
{
    return currentChangeType;
}