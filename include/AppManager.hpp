////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AppManager.hpp
// Robert M. Baker | Created : 11MAR12 | Last Modified : 12MAR12 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'Game'; it defines the interface for an application manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 11MAR12
  * @date    Last Modified : 12MAR12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for an application manager class.
  *
  * @section Description
  *
  * This header file defines the interface for an application manager class.
  */

#ifndef __QMX_GAME_APPMANAGER_HPP_
#define __QMX_GAME_APPMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Singleton.hpp"
#include "AudioManager.hpp"
#include "VideoManager.hpp"
#include "AppState.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define APPMANAGER   AppManager::GetSingleton()
#define APPMANAGER_P AppManager::GetSingletonPointer()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'AppManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class AppManager AppManager.hpp "include/AppManager.hpp"
  *
  * @brief This class defines algorithms for an application manager.
  *
  * These algorithms are useful when it is necessary to manage and control the state of an application.
  *
  * Platform Independent     : Yes
  * Architecture Independent : Yes
  * Thread-Safe              : No
  */

class AppManager : public Singleton< AppManager >
{
public:

	// Public Data Types

		/**
		  * @brief This enumeration defines all valid request codes for the next state.
		  */

		enum StateRequest
		{
			NoRequest,
			ChangeRequest,
			PushRequest,
			PopRequest
		};

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		AppManager();

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~AppManager() noexcept;

	// Public Methods

		/**
		  * @brief This method initializes the application manager.
		  *
		  * @param
		  * 	This is ...
		  *
		  * @exception std::exception
		  * 	If the application manager fails to initialize properly.
		  */

		void Allocate();

		/**
		  * @brief This method shuts down the application manager.
		  *
		  * @exception std::exception
		  * 	If the application manager fails to shut down properly.
		  */

		void Deallocate();

		/**
		  * @brief This method starts the application manager's main loop.
		  *
		  * @param Target
		  * 	This is the initial application state.
		  */

		void Start( AppState* Target );

		/**
		  * @brief This method requests the state be changed to the specified state.
		  *
		  * @param Target
		  * 	This is the state with which to change the current state.
		  */

		void ChangeState( AppState* Target );

		/**
		  * @brief This method requests the specified state be pushed.
		  *
		  * @param Target
		  * 	This is the state to be pushed.
		  */

		void PushState( AppState* Target );

		/**
		  * @brief This method requests the current state be popped.
		  *
		  * If the current state is the only one in the state vector, no action will be taken.
		  */

		void PopState();

private:

	// Private Methods

		/**
		  * @brief This method polls for state change requests and takes appropriate action.
		  */

		void PollStateRequest();

		/**
		  * @brief This method changes to the requested state, which exits the current state.
		  */

		void ChangeStateImp();

		/**
		  * @brief This method pushes the requested state, which pauses the current state.
		  */

		void PushStateImp();

		/**
		  * @brief This method pops the current state, which resumes the previous state.
		  */

		void PopStateImp();

	// Private Fields

		/**
		  * @brief This is the flag used to determine initialization state.
		  */

		bool Initialized;

		/**
		  * @brief This is the request code which determines the next state.
		  */

		StateRequest NextStateRequest;

		/**
		  * @brief This is a pointer to the next state.
		  */

		AppState* NextStateTarget;

		/**
		  * @brief This is a vector of application states.
		  */

		std::vector< AppState* > States;
};

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_GAME_APPMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'AppManager.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
