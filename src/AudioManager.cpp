////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AudioManager.cpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 11MAR12 by Robert M. Baker
// Version : 1.0.0
// This is a source file for 'Game'; it defines the implementation for an audio manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 11MAR12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This source file defines the implementation for an audio manager class.
  *
  * @section Description
  *
  * This source file defines the implementation for an audio manager class.
  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <AudioManager.hpp>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Field Initializers for the 'AudioManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<> AudioManager* Singleton< AudioManager >::SingletonInstance = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'AudioManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AudioManager::AudioManager()
{
	// Initialize fields.

		Initialized = false;
		SystemInstance = nullptr;
		ZERO_ARRAY( ChannelGroups );
}

AudioManager::~AudioManager() noexcept
{
	// Perform necessary cleanup.

		Deallocate();
}

void AudioManager::Allocate( const int32_t MaxChannels, const FMOD_INITFLAGS InitFlags, void* ExDriverData )
{
	// Create local variables.

		size_t GroupIndex = 1;

	// Initialize audio system.

		if( !Initialized )
		{
			if( FMOD_System_Create( &SystemInstance ) != FMOD_OK )
				throw exception();

			if( FMOD_System_Init( SystemInstance, MaxChannels, InitFlags, ExDriverData ) != FMOD_OK )
				throw exception();

			for( size_t Index = 0; Index < MaxAudioTypes; Index += 2 )
			{
				AudioMaps[ Index ].Group = AudioMaps[ ( Index + 1 ) ].Group = GroupIndex;
				GroupIndex++;
			}

			if( FMOD_System_GetMasterChannelGroup( SystemInstance, &ChannelGroups[ MasterGroup ].Instance ) != FMOD_OK )
				throw exception();

			ChannelGroups[ MasterGroup ].Volume = AUDIOMANAGER_DEF_VOLUME;

			if( FMOD_ChannelGroup_SetVolume( ChannelGroups[ MasterGroup ].Instance, AUDIOMANAGER_DEF_VOLUME ) != FMOD_OK )
				throw exception();

			for( size_t Index = 1; Index < MaxChannelGroups; Index++ )
			{
				if( FMOD_System_CreateChannelGroup( SystemInstance, nullptr, &ChannelGroups[ Index ].Instance ) != FMOD_OK )
					throw exception();

				ChannelGroups[ Index ].Volume = AUDIOMANAGER_DEF_VOLUME;

				if( FMOD_ChannelGroup_SetVolume( ChannelGroups[ Index ].Instance, AUDIOMANAGER_DEF_VOLUME ) != FMOD_OK )
					throw exception();

				if( FMOD_ChannelGroup_AddGroup( ChannelGroups[ MasterGroup ].Instance, ChannelGroups[ Index ].Instance ) != FMOD_OK )
					throw exception();
			}

			Initialized = true;
		}
}

void AudioManager::Deallocate()
{
	// Shutdown audio system.

		if( Initialized )
		{
			for( size_t Index = 0; Index < MaxAudioTypes; Index++ )
				AudioMaps[ Index ].Instance.clear();

			if( FMOD_System_Release( SystemInstance ) != FMOD_OK )
				throw exception();

			Initialized = false;
		}
}

void AudioManager::Update()
{
	// Update the audio system.

		if( Initialized )
		{
			if( FMOD_System_Update( SystemInstance ) != FMOD_OK )
				throw exception();
		}
}

void AudioManager::Load( const AudioManager::AudioType Type,
                         const string& ID,
                         const string& Path,
                         const FMOD_MODE Mode,
                         FMOD_CREATESOUNDEXINFO* ExInfo )
{
	// Create local variables.

		FMOD_RESULT FMODResult;
		SoundData Sound = { nullptr, nullptr };

	// Check arguments.

		if( Type == MaxAudioTypes )
			throw exception();

	// Load the specified audio file and insert it into the appropriate audio map.

		if( Initialized )
		{
			if( AudioMaps[ Type ].Instance.find( ID ) != AudioMaps[ Type ].Instance.end() )
				throw exception();

			if( !( Type % 2 ) )
				FMODResult = FMOD_System_CreateSound( SystemInstance, Path.c_str(), Mode, ExInfo, &Sound.Instance );
			else
			   FMODResult = FMOD_System_CreateStream( SystemInstance, Path.c_str(), Mode, ExInfo, &Sound.Instance );

			if( FMODResult != FMOD_OK )
				throw exception();

			if( FMOD_System_CreateChannelGroup( SystemInstance, nullptr, &Sound.Group ) != FMOD_OK )
				throw exception();

			if( FMOD_ChannelGroup_AddGroup( ChannelGroups[ AudioMaps[ Type ].Group ].Instance, Sound.Group ) != FMOD_OK )
				throw exception();

			AudioMaps[ Type ].Instance[ ID ] = Sound;
		}
}

void AudioManager::Unload( const AudioManager::AudioType Type, const string& ID )
{
	// Create local variables.

		unordered_map< string, SoundData >::iterator AudioMapIterator;

	// Check arguments.

		if( Type == MaxAudioTypes )
			throw exception();

	// Unload specified audio file and remove it from the appropriate audio map.

		if( Initialized )
		{
			AudioMapIterator = AudioMaps[ Type ].Instance.find( ID );

			if( AudioMapIterator == AudioMaps[ Type ].Instance.end() )
				throw exception();

			if( FMOD_ChannelGroup_Stop( AudioMapIterator->second.Group ) != FMOD_OK )
				throw exception();

			if( FMOD_ChannelGroup_Release( AudioMapIterator->second.Group ) != FMOD_OK )
				throw exception();

			if( FMOD_Sound_Release( AudioMapIterator->second.Instance ) != FMOD_OK )
				throw exception();

			AudioMaps[ Type ].Instance.erase( AudioMapIterator );
		}
}

void AudioManager::Play( const AudioManager::AudioType Type,
                         const string& ID,
                         const float Volume,
                         const float Pitch,
                         const float Pan,
                         const int32_t LoopCount,
                         const int32_t Priority,
                         const FMOD_CHANNELINDEX ChannelIndex )
{
	// Create local variables.

		float Frequency = Null;
		FMOD_CHANNEL* Channel = nullptr;
		unordered_map< string, SoundData >::iterator AudioMapIterator;

	// Check arguments.

		if( Type == MaxAudioTypes )
			throw exception();

	// Playback specified audio sample or stream.

		if( Initialized )
		{
			AudioMapIterator = AudioMaps[ Type ].Instance.find( ID );

			if( AudioMapIterator == AudioMaps[ Type ].Instance.end() )
				throw exception();

			if( FMOD_System_PlaySound( SystemInstance, ChannelIndex, AudioMapIterator->second.Instance, true, &Channel ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_SetChannelGroup( Channel, AudioMapIterator->second.Group ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_SetLoopCount( Channel, LoopCount ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_SetPriority( Channel, Priority ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_SetPan( Channel, Pan ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_GetFrequency( Channel, &Frequency ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_SetFrequency( Channel, ( Frequency * Pitch ) ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_SetVolume( Channel, Volume ) != FMOD_OK )
				throw exception();

			if( FMOD_Channel_SetPaused( Channel, false ) != FMOD_OK )
				throw exception();
		}
}

void AudioManager::Stop( const AudioManager::AudioType Type, const string& ID )
{
	// Create local variables.

		unordered_map< string, SoundData >::iterator AudioMapIterator;

	// Check arguments.

		if( Type == MaxAudioTypes )
			throw exception();

	// Stop playback of all instances of the specified audio sample or stream.

		if( Initialized )
		{
			AudioMapIterator = AudioMaps[ Type ].Instance.find( ID );

			if( AudioMapIterator == AudioMaps[ Type ].Instance.end() )
				throw exception();

			if( FMOD_ChannelGroup_Stop( AudioMapIterator->second.Group ) != FMOD_OK )
				throw exception();
		}
}

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'AudioManager.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
