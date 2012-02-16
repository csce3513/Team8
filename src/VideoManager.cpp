////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VideoManager.cpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 16FEB12 by Robert M. Baker
// Version : 1.0.0
// This is a source file for 'Game'; it defines the implementation for a video manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 16FEB12 by Robert M. Baker
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
		GLWindowHandle = nullptr;
		GLDeviceContext = nullptr;
		GLRenderContext = nullptr;
}

VideoManager::~VideoManager() noexcept
{
	// Perform necessary cleanup.

		Shutdown();
}

void VideoManager::Initialize( const HWND WindowHandle, const GLdouble ScreenWidth, const GLdouble ScreenHeight )
{
	// Create local variables.

		PIXELFORMATDESCRIPTOR PixelFormatDescriptor;

	// Initialise video system.

		GLWindowHandle = WindowHandle;
		GLDeviceContext = GetDC( GLWindowHandle );

		if( !GLDeviceContext )
			throw exception();

		ZERO_MEMORY( &PixelFormatDescriptor, sizeof( PIXELFORMATDESCRIPTOR ) );
		PixelFormatDescriptor.nSize = sizeof( PIXELFORMATDESCRIPTOR );
		PixelFormatDescriptor.nVersion = 1;
		PixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		PixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
		PixelFormatDescriptor.cColorBits = 24;

		if( !SetPixelFormat( GLDeviceContext, ChoosePixelFormat( GLDeviceContext, &PixelFormatDescriptor ), &PixelFormatDescriptor ) )
			throw exception();

		GLRenderContext = wglCreateContext( GLDeviceContext );

		if( !GLRenderContext )
			throw exception();

		if( !wglMakeCurrent( GLDeviceContext, GLRenderContext ) )
			throw exception();

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( Null, ScreenWidth, ScreenHeight, Null, Null, 1 );
		glDisable( GL_DEPTH_TEST );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glTranslatef( 0.375, 0.375, 0 );
		Initialized = true;
}

void VideoManager::Shutdown()
{
	// Shutdown video system.

		if( Initialized )
		{
			if( !wglMakeCurrent( nullptr, nullptr ) )
				throw exception();

			if( !wglDeleteContext( GLRenderContext ) )
				throw exception();

			GLRenderContext = nullptr;

// For some reason, this causes a segfault.
//			if( !ReleaseDC( GLWindowHandle, GLDeviceContext ) )
//				throw exception();

			GLDeviceContext = nullptr;
			GLWindowHandle = nullptr;
			Initialized = false;
		}
}

void VideoManager::Update()
{
	// Update video system.

		SwapBuffers( GLDeviceContext );
		glClear( GL_COLOR_BUFFER_BIT );
}

void VideoManager::Begin()
{
	// Begin rendering in the specified mode.

		glBegin( GL_QUADS );
}

void VideoManager::End()
{
	// End the current rendering mode.

		glEnd();
}

void VideoManager::DrawQuad( const GLint Left, const GLint Top, const GLint Width, const GLint Height,
                             const GLfloat Red, const GLfloat Green, const GLfloat Blue )
{
	// Draw a quad at the specified coordinates with the specified dimensions.

		glColor3f( Red, Green, Blue );
		glVertex2i( Left, Top );
		glVertex2i( ( Left + Width - 1 ), Top );
		glVertex2i( ( Left + Width - 1 ), ( Top + Height - 1 ) );
		glVertex2i( Left, ( Top + Height - 1 ) );
}

} // 'Game' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Game' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'VideoManager.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
