////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AudioManager.hpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 15FEB12 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'Game'; it defines the interface for an audio manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 15FEB12 by Robert M. Baker
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

#include <exception>
#include <string>
#include <unordered_map>
#include <fmod/fmod.h>

#include "Base.hpp"
#include "Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define AUDIO_MANAGER   AudioManager::GetSingleton()
#define AUDIO_MANAGER_P AudioManager::GetSingletonPointer()

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
		  * @exception std::exception
		  * 	If the audio manager fails to initialize properly.
		  */

		void Initialize();

		/**
		  * @brief This method shuts down the input manager.
		  */

		void Shutdown();

		/**
		  * @brief This method updates the audio system.
		  */

		void Update();

		/**
		  * @brief This method loads an audio file and adds it to the appropriate audio map using the specified values.
		  *
		  * @param Path
		  * 	This is the path to the audio file to load.
		  *
		  * @param ID
		  * 	This is the ID to use when creating the audio map entry.
		  *
		  * @param IsStream
		  * 	This is a flag that determines if the specified file is loaded as a sample or a stream.
		  */

		void Load( const std::string& Path, const std::string& ID, const bool IsStream = false );

		/**
		  * @brief This method plays back the specified sample or stream.
		  *
		  * @param ID
		  * 	This is the ID of the sample or stream to play back.
		  *
		  * @param IsStream
		  * 	This is a flag that determines whether a sample or stream is played back.
		  */

		void Play( const std::string& ID, const bool IsStream = false );

private:

	// Private Data Types

		typedef std::unordered_map< std::string, FMOD_SOUND* > AudioMap;

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
		  * @brief This is a map of all audio samples.
		  */

		AudioMap Samples;

		/**
		  * @brief This is a map of all audio streams.
		  */

		AudioMap Streams;
};

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_GAME_AUDIOMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'AudioManager.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
