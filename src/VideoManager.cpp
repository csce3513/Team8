////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VideoManager.cpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 12MAR12 by Robert M. Baker
// Version : 1.0.0
// This is a source file for 'Game'; it defines the implementation for a video manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 12MAR12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This source file defines the implementation for a video manager class.
  *
  * @section Description
  *
  * This source file defines the implementation for a video manager class.
  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <VideoManager.hpp>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Game
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Field Initializers for the 'VideoManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<> VideoManager* Singleton< VideoManager >::SingletonInstance = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'VideoManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoManager::VideoManager()
{
	// Initialize fields.

		Initialized = false;
		ScreenWidth = Null;
		ScreenHeight = Null;
		BaseFrameTime = glfwGetTime();
		FrameCount = Null;
		SPHandle = Null;
		VAOHandle = Null;
		VBOHandle = Null;
		ZERO_MEMORY( Vertices, ( sizeof( Vertex ) * 4 ) );
}

VideoManager::~VideoManager() noexcept
{
	// Perform necessary cleanup.

		Deallocate();
}

void VideoManager::Allocate( const int32_t Width, const int32_t Height, const bool IsFullscreen )
{
	// Initialise video system.

		if( !Initialized )
		{
			if( !glfwInit() )
				throw exception();

			if( !glfwOpenWindow( Width, Height, 8, 8, 8, 8, 0, 0, ( IsFullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW ) ) )
				throw exception();

			glfwSetWindowSizeCallback( VideoManager::WindowResize );
			glewExperimental = GL_TRUE;

			if( glewInit() != GLEW_OK )
				throw exception();

			SPHandle = glCreateProgram();
			LoadShaderImp( "QuadVertex", "./resources/video/shaders/QuadVertex.glsl", VertexShader );
			LoadShaderImp( "QuadFragment", "./resources/video/shaders/QuadFragment.glsl", FragmentShader );
			EnableShaderImp( "QuadVertex" );
			EnableShaderImp( "QuadFragment" );
			UpdateShaderProgramImp();
			glUseProgram( SPHandle );
			glGenVertexArrays( 1, &VAOHandle );
			glBindVertexArray( VAOHandle );
			glGenBuffers( 1, &VBOHandle );
			glBindBuffer( GL_ARRAY_BUFFER, VBOHandle );
			glBufferData( GL_ARRAY_BUFFER, ( sizeof( Vertex ) * 4 ), Vertices, GL_DYNAMIC_DRAW );
			glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )0 );
			glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( Vertex ), ( void* )( sizeof( float ) * 2 ) );
			glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )( ( sizeof( float ) * 2 ) + sizeof( uint32_t ) ) );
			glEnableVertexAttribArray( 0 );
			glEnableVertexAttribArray( 1 );
			glEnableVertexAttribArray( 2 );
			glEnable( GL_BLEND );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
			ScreenWidth = Width;
			ScreenHeight = Height;
			Initialized = true;
		}
}

void VideoManager::Deallocate()
{
	// Shutdown video system.

		if( Initialized )
		{
			glfwSetWindowSizeCallback( nullptr );
			glUseProgram( Null );

			for( const auto& Index : Shaders )
				UnloadShader( Index.first );

			glDeleteProgram( SPHandle );

			for( const auto& Index : Textures )
				UnloadTexture( Index.first );

			glDisableVertexAttribArray( 2 );
			glDisableVertexAttribArray( 1 );
			glDisableVertexAttribArray( 0 );
			glBindBuffer( GL_ARRAY_BUFFER, Null );
			glDeleteBuffers( 1, &VBOHandle );
			glBindVertexArray( Null );
			glDeleteVertexArrays( 1, &VAOHandle );
			glfwTerminate();
			Initialized = false;
		}
}

void VideoManager::LoadShader( const string& ID, const string& Path, const VideoManager::ShaderType Type )
{
	// Load the shader using specified arguments.

		if( Initialized )
			LoadShaderImp( ID, Path, Type );
}

void VideoManager::UnloadShader( const string& ID )
{
	// Create local variables.

		auto ShaderMapIterator = Shaders.find( ID );

	// Unload the specified shader.

		if( Initialized )
		{
			if( ShaderMapIterator == Shaders.end() )
				throw exception();

			glDetachShader( SPHandle, ShaderMapIterator->second );
			glDeleteShader( ShaderMapIterator->second );
			Shaders.erase( ShaderMapIterator );
		}
}

void VideoManager::EnableShader( const string& ID )
{
	// Enable the specified shader.

		if( Initialized )
			EnableShaderImp( ID );
}

void VideoManager::DisableShader( const string& ID )
{
	// Create local variables.

		auto ShaderMapIterator = Shaders.find( ID );

	// Enable the specified shader.

		if( Initialized )
		{
			if( ShaderMapIterator == Shaders.end() )
				throw exception();

			glDetachShader( SPHandle, ShaderMapIterator->second );
		}
}

void VideoManager::UpdateShaderProgram()
{
	// Update the shader program.

		if( Initialized )
			UpdateShaderProgramImp();
}

void VideoManager::LoadTexture( const string& ID, const string& Path )
{
	// Create local variables.

		FIBITMAP* Bitmap = nullptr;
		int32_t Width = Null;
		int32_t Height = Null;
		BYTE* PixelData = nullptr;
		uint32_t TextureHandle = Null;

	// Load the texture using specified arguments.

		if( Initialized )
		{
			if( Textures.find( ID ) != Textures.end() )
				throw exception();

			if( FreeImage_GetFileType( Path.c_str() ) != FIF_PNG )
				throw exception();

			Bitmap = FreeImage_Load( FIF_PNG, Path.c_str(), PNG_DEFAULT );
			Bitmap = FreeImage_ConvertTo32Bits( Bitmap );
			Width = FreeImage_GetWidth( Bitmap );
			Height = FreeImage_GetHeight( Bitmap );
			PixelData = FreeImage_GetBits( Bitmap );
			glGenTextures( 1, &TextureHandle );
			glBindTexture( GL_TEXTURE_2D, TextureHandle );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexImage2D( GL_TEXTURE_2D, Null, GL_RGBA8, Width, Height, Null, VIDEOMANAGER_CFG_PIXEL_FORMAT, GL_UNSIGNED_BYTE, PixelData );
			FreeImage_Unload( Bitmap );

			if( glGetError() != GL_NO_ERROR )
				throw exception();

			Textures[ ID ] = TextureHandle;
		}
}

void VideoManager::UnloadTexture( const string& ID )
{
	// Create local variables.

		auto TextureMapIterator = Textures.find( ID );

	// Unload the specified texture.

		if( Initialized )
		{
			if( TextureMapIterator == Textures.end() )
				throw exception();

			glDeleteTextures( 1, &TextureMapIterator->second );
			Textures.erase( TextureMapIterator );
		}
}

void VideoManager::SetTexture( const string& ID )
{
	// Create local variables.

		auto TextureMapIterator = Textures.find( ID );

	// Set currently active texture using specified ID.

		if( Initialized )
		{
			if( TextureMapIterator == Textures.end() )
				throw exception();

			glBindTexture( GL_TEXTURE_2D, TextureMapIterator->second );
		}
}

void VideoManager::QueueQuad( const uint8_t Layer, const string& TextureID, const VideoManager::Quad& Target )
{
	// Queue the specified quad to be rendered.

		if( Initialized )
			Quads[ Layer ][ TextureID ].push_back( Target );
}

void VideoManager::DrawQuad( const VideoManager::Quad& Target )
{
	// Create local variables.

		float X = ( ( ( float )Target.X / ( float )ScreenWidth ) * 2.0f ) - 1.0f;
		float Y = 1 - ( ( ( float )Target.Y / ( float )ScreenHeight ) * 2.0f );
		uint32_t Color = ( ( Target.Color & 0x000000FF ) << 24u ) +
		                 ( ( Target.Color & 0x0000FF00 ) <<  8u ) +
		                 ( ( Target.Color & 0x00FF0000 ) >>  8u ) +
		                 ( ( Target.Color & 0xFF000000 ) >> 24u );

	// Render the specified quad to the screen.

		if( Initialized )
		{
			Vertices[ 0 ].X = Vertices[ 2 ].X = X;
			Vertices[ 0 ].Y = Vertices[ 1 ].Y = Y;
			Vertices[ 1 ].X = Vertices[ 3 ].X = X + ( ( ( float )Target.Width / ( float )ScreenWidth ) * 2.0f );
			Vertices[ 2 ].Y = Vertices[ 3 ].Y = Y - ( ( ( float )Target.Height / ( float )ScreenHeight ) * 2.0f );
			Vertices[ 0 ].Color = Vertices[ 1 ].Color = Vertices[ 2 ].Color = Vertices[ 3 ].Color = Color;
			Vertices[ 0 ].S = Vertices[ 2 ].S = Target.UpperLeftS;
			Vertices[ 0 ].T = Vertices[ 1 ].T = Target.UpperLeftT;
			Vertices[ 1 ].S = Vertices[ 3 ].S = Target.LowerRightS;
			Vertices[ 2 ].T = Vertices[ 3 ].T = Target.LowerRightT;
			glBufferData( GL_ARRAY_BUFFER, ( sizeof( Vertex ) * 4 ), Vertices, GL_DYNAMIC_DRAW );
			glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
		}
}

void VideoManager::Update()
{
	// Update video system.

		if( Initialized )
		{
			FrameCount++;

			if( ( glfwGetTime() - BaseFrameTime ) >= 0.25 )
			{
				FrameRate = FrameCount * 4u;
				FrameCount = 0u;
				BaseFrameTime = glfwGetTime();
			}

			glClear( GL_COLOR_BUFFER_BIT );

			for( const auto& LayerIndex : Quads )
			{
				for( const auto& TextureIndex : LayerIndex.second )
				{
					SetTexture( TextureIndex.first );

					for( const auto& QuadIndex : TextureIndex.second )
						DrawQuad( QuadIndex );
				}
			}

			Quads.clear();
			glfwSwapBuffers();
		}
}

uint32_t VideoManager::GetScreenWidth()
{
	// Return current horizontal screen resolution to calling routine.

		return ScreenWidth;
}

uint32_t VideoManager::GetScreenHeight()
{
	// Return current vertical screen resolution to calling routine.

		return ScreenHeight;
}

uint32_t VideoManager::GetFrameRate()
{
	// Return current framerate to calling routine.

		return FrameRate;
}

void GLFWCALL VideoManager::WindowResize( int32_t Width, int32_t Height )
{
	// Create local variables.

		int32_t CurrentWidth = VIDEOMANAGER.ScreenWidth;
		int32_t CurrentHeight = VIDEOMANAGER.ScreenHeight;

	// Perform window resize logic.

		if( VIDEOMANAGER.Initialized )
			glViewport( ( ( Width / 2 ) - ( CurrentWidth / 2 ) ), ( ( Height / 2 ) - ( CurrentHeight / 2 ) ), CurrentWidth, CurrentHeight );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'VideoManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoManager::LoadShaderImp( const string& ID, const string& Path, const VideoManager::ShaderType Type )
{
	// Create local variables.

		int Result = Null;
		ifstream File;
		ostringstream Buffer;
		uint32_t ShaderHandle = Null;

	// Load the shader using specified arguments.

		if( Shaders.find( ID ) != Shaders.end() )
			throw exception();

		File.open( Path );

		if( !File.is_open() )
			throw exception();

		Buffer << File.rdbuf();
		File.close();
		const char* BufferString = Buffer.str().c_str();
		ShaderHandle = glCreateShader( Type );
		glShaderSource( ShaderHandle, 1, &BufferString, nullptr );
		glCompileShader( ShaderHandle );
		glGetShaderiv( ShaderHandle, GL_COMPILE_STATUS, &Result );

		if( !Result )
			throw exception();

		Shaders[ ID ] = ShaderHandle;
}

void VideoManager::EnableShaderImp( const string& ID )
{
	// Create local variables.

		auto ShaderMapIterator = Shaders.find( ID );

	// Enable the specified shader.

		if( ShaderMapIterator == Shaders.end() )
			throw exception();

		glAttachShader( SPHandle, ShaderMapIterator->second );
}

void VideoManager::UpdateShaderProgramImp()
{
	// Create local variables.

		int Result = Null;

	// Update the shader program.

		glLinkProgram( SPHandle );
		glGetProgramiv( SPHandle, GL_LINK_STATUS, &Result );

		if( !Result )
			throw exception();
}

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'VideoManager.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
