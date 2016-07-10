// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IMediaControls.h"
#include "IMediaOutput.h"
#include "IMediaPlayer.h"
#include "IMediaTracks.h"
#include "AllowWindowsPlatformTypes.h"


class FMeMediaPlayer
	: public IMediaControls
	, public IMediaOutput
	, public IMediaPlayer
	, public IMediaTracks
{
public:

	/** Default constructor. */
	FMeMediaPlayer();

	/** Virtual destructor. */
	virtual ~FMeMediaPlayer();

public:

	//~ IMediaControls interface

	virtual FTimespan GetDuration() const override;
	virtual float GetRate() const override;
	virtual EMediaState GetState() const override;
	virtual TRange<float> GetSupportedRates(EMediaPlaybackDirections Direction, bool Unthinned) const override;
	virtual FTimespan GetTime() const override;
	virtual bool IsLooping() const override;
	virtual bool Seek(const FTimespan& Time) override;
	virtual bool SetLooping(bool Looping) override;
	virtual bool SetRate(float Rate) override;
	virtual bool SupportsRate(float Rate, bool Unthinned) const override;
	virtual bool SupportsScrubbing() const override;
	virtual bool SupportsSeeking() const override;

public:

	//~ IMediaOutput interface

	virtual void SetAudioSink(IMediaAudioSink* Sink) override;
	virtual void SetCaptionSink(IMediaStringSink* Sink) override;
	virtual void SetImageSink(IMediaTextureSink* Sink) override;
	virtual void SetVideoSink(IMediaTextureSink* Sink) override;

public:

	//~ IMediaPlayer interface

	virtual void Close() override;
	virtual IMediaControls& GetControls() override;
	virtual IMediaOutput& GetOutput() override;
	virtual IMediaTracks& GetTracks() override;
	virtual FString GetUrl() const override;
	virtual bool Open(const FString& Url, const IMediaOptions& Options) override;
	virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions& Options) override;

	DECLARE_DERIVED_EVENT(FMeMediaPlayer, IMediaPlayer::FOnMediaEvent, FOnMediaEvent);
	virtual FOnMediaEvent& OnMediaEvent() override
	{
		return MediaEvent;
	}

public:

	//~ IMediaTracks interface

	virtual uint32 GetAudioTrackChannels(int32 TrackIndex) const override;
	virtual uint32 GetAudioTrackSampleRate(int32 TrackIndex) const override;
	virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;
	virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;
	virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;
	virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;
	virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;
	virtual uint32 GetVideoTrackBitRate(int32 VideoTrackIndex) const override;
	virtual FIntPoint GetVideoTrackDimensions(int32 VideoTrackIndex) const override;
	virtual float GetVideoTrackFrameRate(int32 TrackIndex) const override;
	virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;

private:

	/** Callback for events from the native media engine. */
	void HandleMediaEngineEvent(DWORD meEvent);

private:

	/** Whether playback should loop to the beginning. */
	bool Looping;

	/** The native media engine. */
	TComPtr<IMFMediaEngine> MediaEngine;

	/** Holds an event delegate that is invoked when a media event occurred. */
	FOnMediaEvent MediaEvent;
};


#include "HideWindowsPlatformTypes.h"
