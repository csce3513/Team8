////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Singleton.hpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 15FEB12 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'Game'; it defines the interface for a singleton class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 15FEB12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for a singleton class.
  *
  * @section Description
  *
  * This header file defines the interface for a singleton class.
  */

#ifndef __QMX_GAME_SINGLETON_HPP_
#define __QMX_GAME_SINGLETON_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Singleton' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Singleton Singleton.hpp "include/Singleton.hpp"
  *
  * @brief This class defines the interface for a singleton class.
  *
  * This is useful when it necessary to enforce a single class instance with global scope.
  *
  * Platform Independent     : Yes
  * Architecture Independent : Yes
  * Thread-Safe              : No
  */

template< typename DType > class Singleton
{
public:

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		Singleton()
		{
			// Initialize fields.

				SingletonInstance = static_cast< DType* >( this );
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~Singleton()
		{
			// Perform necessary cleanup.

				SingletonInstance = nullptr;
		}

	// Public Methods

		/**
		  * @brief This method obtains a reference to the singleton interface for this class.
		  *
		  * Once one has the reference of the singleton, it may be used as would any other class reference.  Make certain the singleton has been instantiated
		  * before calling this function; otherwise, the application will crash on an attempt to use the reference.
		  *
		  * @return
		  * 	A reference to the singleton instance.
		  */

		static DType& GetSingleton()
		{
			// Return a singleton reference to calling routine.

				return *SingletonInstance;
		}

		/**
		  * @brief This method obtains a pointer to the singleton interface for this class.
		  *
		  * Once one has a pointer to the singleton, it may be used as would any other class pointer.  Make certain the singleton has been instantiated before
		  * calling this function; otherwise, the application will crash on an attempt to use the pointer.
		  *
		  * @return
		  * 	A pointer to the singleton instance.
		  */

		static DType* GetSingletonPointer()
		{
			// Return a singleton pointer to calling routine.

				return SingletonInstance;
		}

protected:

	// Protected Fields

		/**
		  * @brief This is the singleton pointer.
		  */

		static DType* SingletonInstance;
};

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_GAME_SINGLETON_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Singleton.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
