////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VideoManager.hpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 12MAR12 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'Game'; it defines the interface for a video manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 12MAR12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for a video manager class.
  *
  * @section Description
  *
  * This header file defines the interface for a video manager class.
  */

#ifndef __QMX_GAME_VIDEOMANAGER_HPP_
#define __QMX_GAME_VIDEOMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define VIDEOMANAGER   VideoManager::GetSingleton()
#define VIDEOMANAGER_P VideoManager::GetSingletonPointer()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'VideoManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class VideoManager VideoManager.hpp "include/VideoManager.hpp"
  *
  * @brief This class defines algorithms for a video manager.
  *
  * These algorithms are useful when it is necessary to draw textured polygons to a window.
  *
  * Platform Independent     : Yes
  * Architecture Independent : Yes
  * Thread-Safe              : No
  */

class VideoManager : public Singleton< VideoManager >
{
public:

	// Public Data Types

		/**
		  * @brief This enumeration defines all valid shader types.
		  */

		enum ShaderType
		{
			VertexShader = GL_VERTEX_SHADER,
			FragmentShader = GL_FRAGMENT_SHADER
		};

		/**
		  * @brief This struct defines the interface for a 2D quad.
		  */

		struct Quad
		{
			/**
			  * @brief This is the upper-left vertex x-coordinate of the quad in absolute screen coordinates.
			  */

			int32_t X;

			/**
			  * @brief This is the upper-left vertex y-coordinate of the quad in absolute screen coordinates.
			  */

			int32_t Y;

			/**
			  * @brief This is the pixel width of the quad.
			  */

			int32_t Width;

			/**
			  * @brief This is the pixel height of the quad.
			  */

			int32_t Height;

			/**
			  * @brief This is the RGBA color of the quad.
			  */

			uint32_t Color;

			/**
			  * @brief This is the upper-left selection vertex x-coordinate within the texture in relative coordinates.
			  */

			float UpperLeftS;

			/**
			  * @brief This is the upper-left selection vertex y-coordinate within the texture in absolute coordinates.
			  */

			float UpperLeftT;

			/**
			  * @brief This is the lower-right selection vertex x-coordinate within the texture in relative coordinates.
			  */

			float LowerRightS;

			/**
			  * @brief This is the lower-right selection vertex y-coordinate within the texture in relative coordinates.
			  */

			float LowerRightT;
		};

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		VideoManager();

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~VideoManager() noexcept;

	// Public Methods

		/**
		  * @brief This method initializes the video manager.
		  *
		  * @param Width
		  * 	This is the horizontal resolution of the render window.
		  *
		  * @param Height
		  * 	This is the vertical resolution of the render window.
		  *
		  * @param IsFullscreen
		  * 	This is the flag which determines whether or not to use fullscreen.
		  *
		  * @exception std::exception
		  * 	If the input manager fails to initialize properly.
		  */

		void Allocate( const int32_t Width = VIDEOMANAGER_DEF_WIDTH,
		               const int32_t Height = VIDEOMANAGER_DEF_HEIGHT,
		               const bool IsFullscreen = VIDEOMANAGER_DEF_IS_FULLSCREEN );

		/**
		  * @brief This method shuts down the video system.
		  */

		void Deallocate();

		/**
		  * @brief This method loads a shader.
		  *
		  * @param ID
		  * 	This is the shader ID to use when inserting into the shader map.
		  *
		  * @param Path
		  * 	This is the path to the shader file.
		  *
		  * @param Type
		  * 	This is the shader type to load.
		  *
		  * @exception std::exception
		  * 	If the specified shader ID already exists or the shader fails to load properly.
		  */

		void LoadShader( const std::string& ID, const std::string& Path, const ShaderType Type );

		/**
		  * @brief This method unloads a shader.
		  *
		  * @param ID
		  * 	This is the shader ID to unload.
		  *
		  * @exception std::exception
		  * 	If the specified shader ID does not exist.
		  */

		void UnloadShader( const std::string& ID );

		/**
		  * @brief This method enables a shader.
		  *
		  * @param ID
		  * 	This is the shader ID to enable.
		  *
		  * @exception std::exception
		  * 	If the specified shader ID does not exist.
		  */

		void EnableShader( const std::string& ID );

		/**
		  * @brief This method disables a shader.
		  *
		  * @param ID
		  * 	This is the shader ID to disable.
		  *
		  * @exception std::exception
		  * 	If the specified shader ID does not exist.
		  */

		void DisableShader( const std::string& ID );

		/**
		  * @brief This method updates the shader program.
		  *
		  * @exception std::exception
		  * 	If the shader program fails to link.
		  */

		void UpdateShaderProgram();

		/**
		  * @brief This method loads a texture.
		  *
		  * @param ID
		  * 	This is the texture ID to use when inserting into the texture map.
		  *
		  * @param Path
		  * 	This is the path to the texture file.
		  *
		  * @exception std::exception
		  * 	If the specified texture ID already exists.
		  */

		void LoadTexture( const std::string& ID, const std::string& Path );

		/**
		  * @brief This method unloads a texture.
		  *
		  * @param ID
		  * 	This is the texture ID to unload.
		  *
		  * @exception std::exception
		  * 	If the specified texture ID does not exist.
		  */

		void UnloadTexture( const std::string& ID );

		/**
		  * @brief This method sets the currently active texture.
		  *
		  * @param ID
		  * 	This is the texture ID to use.
		  *
		  * @exception std::exception
		  * 	If the specified texture ID does not exist.
		  */

		void SetTexture( const std::string& ID );

		/**
		  * @brief This method queues a quad to be rendered.
		  *
		  * If the specified texture ID does not exist, an exception will be thrown when an attempt is made to set it as the active texture.
		  *
		  * @param Layer
		  * 	This is the layer to render the quad on (lower valued layers are under higher valued layers).
		  *
		  * @param TextureID
		  * 	This is the ID of the texture to apply to the quad.
		  *
		  * @param Target
		  * 	This is the quad to be queued.
		  */

		void QueueQuad( const uint8_t Layer, const std::string& TextureID, const Quad& Target );

		/**
		  * @brief This method renders a quad to the screen.
		  *
		  * @param Target
		  * 	This is the quad to be rendered.
		  */

		void DrawQuad( const Quad& Target );

		/**
		  * @brief This method updates the video system.
		  */

		void Update();

		/**
		  * @brief This method gets the current horizontal screen resolution.
		  *
		  * @return
		  * 	The current horizontal screen resolution.
		  */

		uint32_t GetScreenWidth();

		/**
		  * @brief This method gets the current vertical screen resolution.
		  *
		  * @return
		  * 	The current vertical screen resolution.
		  */

		uint32_t GetScreenHeight();

		/**
		  * @brief This method gets the current framerate.
		  *
		  * @return
		  * 	The current framerate.
		  */

		uint32_t GetFrameRate();

		/**
		  * @brief This method is the window resize callback.
		  *
		  * @param Width
		  * 	This is the new screen horizontal resolution.
		  *
		  * @param Height
		  * 	This is the new screen vertical resolution.
		  */

		static void GLFWCALL WindowResize( int32_t Width, int32_t Height );

private:

	// Private Data Types

		/**
		  * @brief This struct defines the interface for a 2D vertex.
		  */

		struct Vertex
		{
			/**
			  * @brief This is the x-coordinate of the vertex.
			  */

			float X;

			/**
			  * @brief This is the y-coordinate of the vertex.
			  */

			float Y;

			/**
			  * @brief This is the RGBA color of the vertex.
			  */

			uint32_t Color;

			/**
			  * @brief This is the x-coordinate of the texture.
			  */

			float S;

			/**
			  * @brief This is the y-coordinate of the texture.
			  */

			float T;
		};

	// Private Type Definitions

		typedef std::unordered_map< uint8_t, std::unordered_map< std::string, std::vector< Quad > > > QuadMap;

	// Private Methods

		/**
		  * @brief This method is the implementation for 'LoadShader'.
		  *
		  * It is made private to prevent external calls, and exists to allow loading of shaders before 'Initialized' is set to 'true'.
		  *
		  * @param ID
		  * 	This is the shader ID to use when inserting into the shader map.
		  *
		  * @param Path
		  * 	This is the path to the shader file.
		  *
		  * @param Type
		  * 	This is the shader type to load.
		  *
		  * @exception std::exception
		  * 	If the specified shader ID already exists or the shader fails to load properly.
		  */

		void LoadShaderImp( const std::string& ID, const std::string& Path, const ShaderType Type );

		/**
		  * @brief This method is the implementation for 'EnableShader'.
		  *
		  * It is made private to prevent external calls, and exists to allow enabling of shaders before 'Initialized' is set to 'true'.
		  *
		  * @param ID
		  * 	This is the shader ID to enable.
		  *
		  * @exception std::exception
		  * 	If the specified shader ID does not exist.
		  */

		void EnableShaderImp( const std::string& ID );

		/**
		  * @brief This method is the implementation for 'UpdateShaderProgram'.
		  *
		  * It is made private to prevent external calls, and exists to allow updating the shader program before 'Initialized' is set to 'true'.
		  *
		  * @exception std::exception
		  * 	If the shader program fails to link.
		  */

		void UpdateShaderProgramImp();

	// Private Fields

		/**
		  * @brief This is the flag used to determine initialization state.
		  */

		bool Initialized;

		/**
		  * @brief This is the horizontal resolution of the render window.
		  */

		int32_t ScreenWidth;

		/**
		  * @brief This is the vertical resolution of the render window.
		  */

		int32_t ScreenHeight;

		/**
		  * @brief This is a base time used in calculating frame rate.
		  */

		double BaseFrameTime;

		/**
		  * @brief This is a counter used in calculating frame rate.
		  */

		uint32_t FrameCount;

		/**
		  * @brief This is the current frame rate.
		  */

		uint32_t FrameRate;

		/**
		  * @brief This is the map containing all loaded shaders.
		  */

		UInt32Map Shaders;

		/**
		  * @brief This is the handle to the Shader Program.
		  */

		uint32_t SPHandle;

		/**
		  * @brief This is the handle to the Vertex Array Object.
		  */

		uint32_t VAOHandle;

		/**
		  * @brief This is the handle to the Vertex Buffer Object.
		  */

		uint32_t VBOHandle;

		/**
		  * @brief This is vertices array used to render quads.
		  */

		Vertex Vertices[ 4 ];

		/**
		  * @brief This is the map containing all loaded textures.
		  */

		UInt32Map Textures;

		/**
		  * @brief This is the map containing all queued quads.
		  */

		QuadMap Quads;
};

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_GAME_VIDEOMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'VideoManager.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
