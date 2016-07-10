// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MeMediaPCH.h"

#if (WINVER >= _WIN32_WINNT_WIN8)

#include "MeMediaPlayer.h"
#include "AllowWindowsPlatformTypes.h"


/* FMeMediaPlayer structors
 *****************************************************************************/

FMeMediaPlayer::FMeMediaPlayer()
	: Looping(false)
{ }


FMeMediaPlayer::~FMeMediaPlayer()
{
	Close();
}


/* IMediaControls interface
 *****************************************************************************/

FTimespan FMeMediaPlayer::GetDuration() const
{
	if (MediaEngine == nullptr)
	{
		return FTimespan::Zero();
	}

	double Duration = MediaEngine->GetDuration();

	if (Duration != Duration) // NaN
	{
		return FTimespan::Zero();
	}

	if (Duration == INFINITY)
	{
		return FTimespan::MaxValue();
	}

	return FTimespan::FromSeconds(Duration);
}


float FMeMediaPlayer::GetRate() const
{
	return (MediaEngine != nullptr) ? MediaEngine->GetPlaybackRate() : 0.0f;
}


EMediaState FMeMediaPlayer::GetState() const
{

}


TRange<float> FMeMediaPlayer::GetSupportedRates(EMediaPlaybackDirections Direction, bool Unthinned) const
{
	if (Direction == EMediaPlaybackDirections::Reverse)
	{
		return TRange<float>::Empty();
	}

	return TRange<float>(1.0f); // todo
}


FTimespan FMeMediaPlayer::GetTime() const
{
	return (MediaEngine != nullptr) ? FTimespan::FromSeconds(MediaEngine->GetCurrentTime()) : FTimespan::Zero();
}

bool FMeMediaPlayer::IsLooping() const
{
	return Looping;
}


bool FMeMediaPlayer::Seek(const FTimespan& Time)
{
	return ((MediaEngine != nullptr) && SUCCEEDED(MediaEngine->SetCurrentTime(Time.GetTotalSeconds())));
}


bool FMeMediaPlayer::SetLooping(bool InLooping)
{
	Looping = InLooping;

	return true;
}


bool FMeMediaPlayer::SetRate(float Rate)
{
	if (MediaEngine == nullptr)
	{
		if (!MediaEngine->SetPlaybackRate(Rate))
		{
			return false;
		}

		if (Rate == 0.0f)
		{
			return SUCCEEDED(MediaEngine->Pause());
		}

		if (Rate == 1.0f)
		{
			return SUCCEEDED(MediaEngine->Play());
		}
	}

	return false;
}


bool FMeMediaPlayer::SupportsRate(float Rate, bool Unthinned) const
{
	if (MediaEngine == nullptr)
	{
		return false;
	}

	// there is no direct way to check rates, so we'll try to set the default rate
	double DefaultRate = MediaEngine->GetDefaultPlaybackRate();

	if (FAILED(MediaEngine->SetDefaultPlaybackRate(Rate)))
	{
		return false;
	}

	MediaEngine->SetDefaultPlaybackRate(DefaultRate);

	return true;
}


bool FMeMediaPlayer::SupportsScrubbing() const
{
	return false; // todo
	//return CanScrub;
}



bool FMeMediaPlayer::SupportsSeeking() const
{
	return false; // todo
	//return (((Capabilities & MFSESSIONCAP_SEEK) != 0) && (Duration > FTimespan::Zero()));
}


/* IMediaOutput interface
 *****************************************************************************/

void FMeMediaPlayer::SetAudioSink(IMediaAudioSink* Sink)
{
}


void FMeMediaPlayer::SetCaptionSink(IMediaStringSink* Sink)
{
}


void FMeMediaPlayer::SetImageSink(IMediaTextureSink* Sink)
{
}


void FMeMediaPlayer::SetVideoSink(IMediaTextureSink* Sink)
{
}


/* IMediaPlayer interface
 *****************************************************************************/

void FMeMediaPlayer::Close()
{
}


IMediaControls& FMeMediaPlayer::GetControls()
{
	return *this;
}


IMediaOutput& FMeMediaPlayer::GetOutput()
{
	return *this;
}


IMediaTracks& FMeMediaPlayer::GetTracks()
{
	return *this;
}


FString FMeMediaPlayer::GetUrl() const
{
	return FString(); // todo
}


bool FMeMediaPlayer::Open(const FString& Url, const IMediaOptions& Options)
{
	return false; // todo
}


bool FMeMediaPlayer::Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions& Options)
{
	return false; // todo
}


/* IMediaTracks interface
 *****************************************************************************/

uint32 FMeMediaPlayer::GetAudioTrackChannels(int32 TrackIndex) const
{
	return 0; // todo
}


uint32 FMeMediaPlayer::GetAudioTrackSampleRate(int32 TrackIndex) const
{
	return 0; // todo
}


int32 FMeMediaPlayer::GetNumTracks(EMediaTrackType TrackType) const
{
	switch (TrackType)
	{
	case EMediaTrackType::Audio:
		return 0; // todo
	case EMediaTrackType::Video:
		return 0; // todo
	default:
		return 0;
	}
}


int32 FMeMediaPlayer::GetSelectedTrack(EMediaTrackType TrackType) const
{/*
	switch (TrackType)
	{
	case EMediaTrackType::Audio:
		return SelectedAudioTrack;
	case EMediaTrackType::Video:
		return SelectedVideoTrack;
	default:
		return INDEX_NONE;
	}*/

	return INDEX_NONE;
}


FText FMeMediaPlayer::GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const
{/*
	switch (TrackType)
	{
	case EMediaTrackType::Audio:
		if (AudioStreams.IsValidIndex(TrackIndex))
		{
			return AudioStreams[TrackIndex]->GetDisplayName();
		}
		break;

	case EMediaTrackType::Caption:
		if (CaptionStreams.IsValidIndex(TrackIndex))
		{
			return CaptionStreams[TrackIndex]->GetDisplayName();
		}

	case EMediaTrackType::Video:
		if (VideoStreams.IsValidIndex(TrackIndex))
		{
			return VideoStreams[TrackIndex]->GetDisplayName();
		}

	default:
		break;
	}*/

	return FText::GetEmpty();
}


FString FMeMediaPlayer::GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const
{/*
	switch (TrackType)
	{
	case EMediaTrackType::Audio:
		if (AudioStreams.IsValidIndex(TrackIndex))
		{
			return AudioStreams[TrackIndex]->GetLanguage();
		}
		break;

	case EMediaTrackType::Caption:
		if (CaptionStreams.IsValidIndex(TrackIndex))
		{
			return CaptionStreams[TrackIndex]->GetLanguage();
		}

	case EMediaTrackType::Video:
		if (VideoStreams.IsValidIndex(TrackIndex))
		{
			return VideoStreams[TrackIndex]->GetLanguage();
		}

	default:
		break;
	}*/

	return FString();
}


FString FMeMediaPlayer::GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const
{/*
	switch (TrackType)
	{
	case EMediaTrackType::Audio:
		if (AudioStreams.IsValidIndex(TrackIndex))
		{
			return AudioStreams[TrackIndex]->GetName();
		}
		break;

	case EMediaTrackType::Caption:
		if (CaptionStreams.IsValidIndex(TrackIndex))
		{
			return CaptionStreams[TrackIndex]->GetName();
		}

	case EMediaTrackType::Video:
		if (VideoStreams.IsValidIndex(TrackIndex))
		{
			return VideoStreams[TrackIndex]->GetName();
		}

	default:
		break;
	}*/

	return FString();
}


uint32 FMeMediaPlayer::GetVideoTrackBitRate(int32 TrackIndex) const
{
	return 0; // todo
	//return VideoStreams.IsValidIndex(TrackIndex) ? VideoStreams[TrackIndex]->GetBitRate() : 0;
}


FIntPoint FMeMediaPlayer::GetVideoTrackDimensions(int32 TrackIndex) const
{
	return FIntPoint::ZeroValue; // todo
	//return VideoStreams.IsValidIndex(TrackIndex) ? VideoStreams[TrackIndex]->GetDimensions() : FIntPoint::ZeroValue;
}


float FMeMediaPlayer::GetVideoTrackFrameRate(int32 TrackIndex) const
{
	return 0.0f; // todo
	//return VideoStreams.IsValidIndex(TrackIndex) ? VideoStreams[TrackIndex]->GetFrameRate() : 0.0f;
}


bool FMeMediaPlayer::SelectTrack(EMediaTrackType TrackType, int32 TrackIndex)
{/*
	switch (TrackType)
	{
	case EMediaTrackType::Audio:
		if ((TrackIndex == INDEX_NONE) || AudioStreams.IsValidIndex(TrackIndex))
		{
			if (SelectedAudioTrack != INDEX_NONE)
			{
				AudioStreams[SelectedAudioTrack]->Disable();
			}

			SelectedAudioTrack = TrackIndex;

			if (SelectedAudioTrack != INDEX_NONE)
			{
				AudioStreams[SelectedAudioTrack]->Enable();
			}

			return true;
		}

	case EMediaTrackType::Caption:
		if ((TrackIndex == INDEX_NONE) || CaptionStreams.IsValidIndex(TrackIndex))
		{
			if (SelectedCaptionTrack != INDEX_NONE)
			{
				CaptionStreams[SelectedCaptionTrack]->Disable();
			}

			SelectedCaptionTrack = TrackIndex;

			if (SelectedCaptionTrack != INDEX_NONE)
			{
				CaptionStreams[SelectedCaptionTrack]->Enable();
			}

			return true;
		}

	case EMediaTrackType::Video:
		if ((TrackIndex == INDEX_NONE) || VideoStreams.IsValidIndex(TrackIndex))
		{
			if (SelectedVideoTrack != INDEX_NONE)
			{
				VideoStreams[SelectedVideoTrack]->Disable();
			}

			SelectedVideoTrack = TrackIndex;

			if (SelectedVideoTrack != INDEX_NONE)
			{
				VideoStreams[SelectedVideoTrack]->Enable();
			}

			return true;
		}

	default:
		break;
	}*/

	return false;
}


/* FMeMediaPlayer callbacks
 *****************************************************************************/

void FMeMediaPlayer::HandleMediaEngineEvent(DWORD Event)
{
	switch (Event)
	{
	case MF_MEDIA_ENGINE_EVENT_ENDED:
	case MF_MEDIA_ENGINE_EVENT_ERROR:
		break;
	}
}


#include "HideWindowsPlatformTypes.h"

#endif //WINVER >= _WIN32_WINNT_WIN8
