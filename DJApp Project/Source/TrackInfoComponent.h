/*
  ==============================================================================

    TrackInfoComponent.h
    Created: 20 Aug 2024 9:09:17pm
    Author:  alex_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
using namespace juce;

//==============================================================================
/*
*/
class TrackInfoComponent  : public Component,
        					public ChangeBroadcaster
{
public:
    /*Struct to hold track info data*/
    struct TrackInfo
    {
        String title;
        String artist;
        String album;
        String length;
        URL fileURL;
    };
    /*Struct to hold the change type*/
    enum TrackChangeType
    {
        AddTrack,
        RemoveTrack
    };
    TrackInfoComponent(AudioFormatManager& formatManagerToUse);
    ~TrackInfoComponent() override;
    /*Adding a track to the tracks data structure, it requires a file as parameter*/
    void addTrack(File file);
    /*Retrieve tracks from json file, it requires a var data type json array*/
    void retrieveTracksFromJson(var jsonObject);
    /*Removing a track from the tracks data structure, it requires the index of the track to be removed*/
    void removeTrack(int index);
    /*Returns back the number of tracks inside the tracks data structure*/
    int getNumTracks();
    /*Returns a pointer to the tracks data structure*/
    std::vector<TrackInfoComponent::TrackInfo>* getTracks();
    /*Returns the track info of a specific track, it requires the index of the track*/
    String getTrackName(int index) const;
    String getTrackArtist(int index) const;
    String getTrackAlbum(int index) const;
    String getTrackLength(int index) const;
    /*Tracks data structure holding the struct as the type*/
    std::vector<TrackInfo> tracks;
    /*Custom change message that will update the currentChangeType for information purposes required by the playlistComponent*/
    void sendCustomChangeMessage(TrackChangeType changeType);
    /*Exposing the currentChangeType at request for playlistComponent*/
    TrackInfoComponent::TrackChangeType getCurrentChangeType();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackInfoComponent)

    
    TrackChangeType currentChangeType;
    AudioFormatManager& formatManager;
};
