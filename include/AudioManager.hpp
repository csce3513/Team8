////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AudioManager.hpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 10MAR12 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'Game'; it defines the interface for an audio manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 10MAR12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for an audio manager class.
  *
  * @section Description
  *
  * This header file defines the interface for an audio manager class.
  */

#ifndef __QMX_GAME_AUDIOMANAGER_HPP_
#define __QMX_GAME_AUDIOMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define AUDIOMANAGER               AudioManager::GetSingleton()
#define AUDIOMANAGER_P             AudioManager::GetSingletonPointer()
#define AUDIOMANAGER_INFINITE_LOOP -1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'AudioManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class AudioManager AudioManager.hpp "include/AudioManager.hpp"
  *
  * @brief This class defines algorithms for an audio manager.
  *
  * These algorithms are useful when it is necessary to manage and play back audio files.
  *
  * Platform Independent     : Yes
  * Architecture Independent : Yes
  * Thread-Safe              : No
  */

class AudioManager : public Singleton< AudioManager >
{
public:

	// Public Data Types

		/**
		  * @brief This enumeration defines all valid audio types.
		  */

		enum AudioType
		{
			SFXSample,
			SFXStream,
			MusicSample,
			MusicStream,
			MaxAudioTypes
		};

		/**
		  * @brief This enumeration defines all valid channel groups.
		  */

		enum ChannelGroup
		{
			MasterGroup,
			SFXGroup,
			MusicGroup,
			MaxChannelGroups
		};

		/**
		  * @brief This enumeration defines all valid channel group properties.
		  */

		enum ChannelGroupProperty
		{
			PauseState,
			MuteState,
			VolumeState
		};

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		AudioManager();

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~AudioManager() noexcept;

	// Public Methods

		/**
		  * @brief This method initializes the audio manager.
		  *
		  * @param MaxChannels
		  * 	This is the maximum number of virtual channels.
		  *
		  * @param InitFlags
		  * 	These are the initialization flags.
		  *
		  * @param ExDriverData
		  * 	This is a pointer to extra driver data to use when initializing the audio manager.
		  *
		  * @exception std::exception
		  * 	If the audio manager fails to initialize properly.
		  */

		void Allocate( const int32_t MaxChannels = AUDIOMANAGER_DEF_MAX_CHANNELS,
		               const FMOD_INITFLAGS InitFlags = AUDIOMANAGER_DEF_INIT_FLAGS,
		               void* ExDriverData = nullptr );

		/**
		  * @brief This method shuts down the input manager.
		  *
		  * @exception std::exception
		  * 	If the audio manager fails to shut down properly.
		  */

		void Deallocate();

		/**
		  * @brief This method updates the audio system.
		  *
		  * @exception std::exception
		  * 	If the audio manager fails to update properly.
		  */

		void Update();

		/**
		  * @brief This method loads an audio file and adds it to the appropriate audio map using the specified values.
		  *
		  * @param Type
		  * 	This is the audio type to load.
		  *
		  * @param ID
		  * 	This is the ID to use when creating the audio map entry.
		  *
		  * @param Path
		  * 	This is the path to the audio file.
		  *
		  * @param Mode
		  * 	This is the mode to use when loading the audio file.
		  *
		  * @param ExInfo
		  * 	This is a pointer to extra data to use when loading the audio file.
		  *
		  * @exception std::exception
		  * 	If 'Type' is equal to 'MaxAudioTypes', the specified ID already exists, or an error occurs during loading.
		  */

		void Load( const AudioType Type,
		           const std::string& ID,
		           const std::string& Path,
		           const FMOD_MODE Mode = AUDIOMANAGER_DEF_MODE,
		           FMOD_CREATESOUNDEXINFO* ExInfo = nullptr );

		/**
		  * @brief This method unloads an audio sample or stream.
		  *
		  * @param Type
		  * 	This is the audio type to unload.
		  *
		  * @param ID
		  * 	This is the ID to use when searching the appropriate map.
		  *
		  * @exception std::exception
		  * 	If 'Type' is equal to 'MaxAudioTypes', the specified ID does not exist, or an error occurs during unloading.
		  */

		void Unload( const AudioType Type, const std::string& ID );

		/**
		  * @brief This method plays back an audio sample or stream.
		  *
		  * @param Type
		  * 	This is the audio type to playback.
		  *
		  * @param ID
		  * 	This is the ID to use when searching the appropriate audio map.
		  *
		  * @param Volume
		  * 	This is the volume of the audio sample or stream.
		  *
		  * @param Pitch
		  * 	This is the pitch of the audio sample or stream.
		  *
		  * @param Pan
		  * 	This is the pan of the audio sample or stream.
		  *
		  * @param LoopCount
		  * 	This is the number of times to loop the audio sample or stream.
		  *
		  * @param Priority
		  * 	This is the priority of the audio sample or stream.
		  *
		  * @param ChannelIndex
		  * 	This is the channel index of the audio sample or stream.
		  *
		  * @exception std::exception
		  * 	If 'Type' is equal to 'MaxAudioTypes', the specified ID does not exist, or an error occurs during playback.
		  */

		void Play( const AudioType Type,
		           const std::string& ID,
		           const float Volume = AUDIOMANAGER_DEF_VOLUME,
		           const float Pitch = AUDIOMANAGER_DEF_PITCH,
		           const float Pan = AUDIOMANAGER_DEF_PAN,
		           const int32_t LoopCount = AUDIOMANAGER_DEF_LOOP_COUNT,
		           const int32_t Priority = AUDIOMANAGER_DEF_PRIORITY,
		           const FMOD_CHANNELINDEX ChannelIndex = AUDIOMANAGER_DEF_CHANNEL_INDEX );

		/**
		  * @brief This method stops playback of all instances of the specified audio sample or stream.
		  *
		  * @param Type
		  * 	This is the audio type to stop.
		  *
		  * @param ID
		  * 	This is the ID to use when searching the appropriate audio map.
		  *
		  * @exception std::exception
		  * 	If 'Type' is equal to 'MaxAudioTypes', the specified ID does not exist, or an error occurs during stopping.
		  */

		void Stop( const AudioType Type, const std::string& ID );

		/**
		  * @brief This method gets the specified channel group property
		  *
		  * @param Value
		  * 	This is the value which will receive the specified property.
		  *
		  * @param Group
		  * 	This is the channel group to use when getting the property.
		  *
		  * @param Property
		  * 	This is the property to get.
		  *
		  * @exception std::exception
		  * 	If 'Group' is equal to 'MaxChannelGroups'.
		  */

		template< typename NType > void GetChannelGroupProperty( NType& Value, const ChannelGroup Group, const ChannelGroupProperty Property ) const
		{
			// Check arguments.

				if( Group == MaxChannelGroups )
					throw std::exception();

			// Get specified channel group property.

				switch( Property )
				{
					case PauseState:
					{
						Value = static_cast< NType >( ChannelGroups[ Group ].IsPaused );

						break;
					}

					case MuteState:
					{
						Value = static_cast< NType >( ChannelGroups[ Group ].IsMuted );

						break;
					}

					case VolumeState:
					{
						Value = static_cast< NType >( ChannelGroups[ Group ].Volume );

						break;
					}
				}
		}

		/**
		  * @brief This method sets the specified channel group property.
		  *
		  * @param Value
		  * 	This is the new value with which to set the specified property.
		  *
		  * @param Group
		  * 	This is the channel group to use when setting the property.
		  *
		  * @param Property
		  * 	This is the property to set.
		  *
		  * @exception std::exception
		  * 	If 'Group' is equal to 'MaxChannelGroups'.
		  */

		template< typename NType > void SetChannelGroupProperty( const NType Value, const ChannelGroup Group, const ChannelGroupProperty Property )
		{
			// Check arguments.

				if( Group == MaxChannelGroups )
					throw std::exception();

			// Set specified channel group property using specified value.

				switch( Property )
				{
					case PauseState:
					{
						ChannelGroups[ Group ].IsPaused = static_cast< bool >( Value );

						if( FMOD_ChannelGroup_SetPaused( ChannelGroups[ Group ].Instance, static_cast< FMOD_BOOL >( Value ) != FMOD_OK ) )
							throw std::exception();

						break;
					}

					case MuteState:
					{
						ChannelGroups[ Group ].IsMuted = static_cast< bool >( Value );

						if( FMOD_ChannelGroup_SetMute( ChannelGroups[ Group ].Instance, static_cast< FMOD_BOOL >( Value ) != FMOD_OK ) )
							throw std::exception();

						break;
					}

					case VolumeState:
					{
						ChannelGroups[ Group ].Volume = static_cast< float >( Value );

						if( FMOD_ChannelGroup_SetVolume( ChannelGroups[ Group ].Instance, static_cast< float >( Value ) != FMOD_OK ) )
							throw std::exception();

						break;
					}
				}
		}

private:

	// Private Data Types

		/**
		  * @brief This structure defines the interface for sound properties.
		  */

		struct SoundData
		{
			/**
			  * @brief This is the sound pointer.
			  */

			FMOD_SOUND* Instance;

			/**
			  * @brief This is the sound's channel group.
			  */

			FMOD_CHANNELGROUP* Group;
		};

		/**
		  * @brief This structure defines the interface for audio type properties.
		  */

		struct AudioMapData
		{
			std::unordered_map< std::string, SoundData > Instance;
			int32_t Group;
		};

		/**
		  * @brief This structure defines the interface for channel group properties.
		  */

		struct ChannelGroupData
		{
			/**
			  * @brief This is the channel group pointer.
			  */

			FMOD_CHANNELGROUP* Instance;

			/**
			  * @brief This is the channel group's pause state.
			  */

			bool IsPaused;

			/**
			  * @brief This is the channel group's mute state.
			  */

			bool IsMuted;

			/**
			  * @brief This is the channel group's default volume.
			  */

			float Volume;
		};

	// Private Fields

		/**
		  * @brief This is the flag used to determine initialization state.
		  */

		bool Initialized;

		/**
		  * @brief This is a pointer to the audio system.
		  */

		FMOD_SYSTEM* SystemInstance;

		/**
		  * @brief This is an array of all audio maps.
		  */

		AudioMapData AudioMaps[ MaxAudioTypes ];

		/**
		  * @brief This an array of all channel groups.
		  */

		ChannelGroupData ChannelGroups[ MaxChannelGroups ];
};

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_GAME_AUDIOMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'AudioManager.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
