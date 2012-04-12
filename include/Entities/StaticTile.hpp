////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StaticTile.hpp
// Robert M. Baker | Created : 12MAR12 | Last Modified : 11APR12 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'Game'; it defines the interface for a simple, stationary tile class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 12MAR12
  * @date    Last Modified : 11APR12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for a simple, stationary tile class.
  *
  * @section Description
  *
  * This header file defines the interface for a simple, stationary tile class.
  */

#ifndef __QMX_GAME_STATICTILE_HPP_
#define __QMX_GAME_STATICTILE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"
#Include "Entity.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'StaticTile' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class StaticTile StaticTile.hpp "include/StaticTile.hpp"
  *
  * @brief This class defines algorithms for a simple, stationary tile class.
  *
  * These algorithms are useful when it is necessary to represent stationary objects such as floors, walls, or background objects.
  *
  * Platform Independent     : Yes
  * Architecture Independent : Yes
  * Thread-Safe              : No
  */

class StaticTile : public Entity
{
public:

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		StaticTile();

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~StaticTile() noexcept;

	// Public Methods

		//

private:

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'Logic' method.
		  */

		void LogicImp();

	// Private Fields

		//
};

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_GAME_STATICTILE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'StaticTile.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
