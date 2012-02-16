////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main.cpp
// Robert M. Baker | Created : 15FEB12 | Last Modified : 16FEB12 by Robert M. Baker
// Version : 1.0.0
// This is the main source file for 'Game'.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 15FEB12
  * @date    Last Modified : 16FEB12 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This is the main source file for 'Game'.
  *
  * @section Description
  *
  * This is the main source file for 'Game'.
  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Main.hpp>

using namespace std;
using namespace Game;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'WindowProcedure' Function
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowProcedure( HWND WindowHandle, UINT Message, WPARAM WParameter, LPARAM LParameter )
{
	// Create local variables.

		LRESULT Result = Null;

	// Execute window procedure logic.

		switch( Message )
		{
			case WM_CLOSE:
			{
				DestroyWindow( WindowHandle );

				break;
			}

			case WM_DESTROY:
			{
				PostQuitMessage( Null );

				break;
			}

			default:
			{
				Result = DefWindowProc( WindowHandle, Message, WParameter, LParameter );
			}
		}

	// Return result to calling routine.

		return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'WinMain' Function
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain( HINSTANCE InstanceHandle, HINSTANCE PrevInstanceHandle, char* CmdLine, int CmdShow )
{
	// Create local variables.

		int Result = Success;
		bool Done = false;
		WNDCLASSEX WindowClass;
		HWND WindowHandle;
		MSG Message;

		GLint PlayerX = 0;
		GLint PlayerSpeed = 5;

	// Instantiate singleton classes.

		InputManager InputManagerSingleton;
		AudioManager AudioManagerSingleton;
		VideoManager VideoManagerSingleton;

	// Execute main code.

		try
		{
			// Register main window class.

				ZERO_MEMORY( &WindowClass, sizeof( WNDCLASSEX ) );
				WindowClass.cbSize = sizeof( WNDCLASSEX );
				WindowClass.lpfnWndProc = WindowProcedure;
				WindowClass.hInstance = InstanceHandle;
				WindowClass.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
				WindowClass.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );
				WindowClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
				WindowClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
				WindowClass.lpszClassName = "GameMainWindow";

				if( !RegisterClassEx( &WindowClass ) )
					throw exception();

			// Create main window.

				WindowHandle = CreateWindowEx( WS_EX_CLIENTEDGE,
			                                  "GameMainWindow",
			                                  "Game",
			                                  WS_OVERLAPPEDWINDOW,
			                                  CW_USEDEFAULT,
			                                  CW_USEDEFAULT,
			                                  SCREEN_WIDTH,
			                                  SCREEN_HEIGHT,
			                                  nullptr,
			                                  nullptr,
			                                  InstanceHandle,
			                                  nullptr );

				if( !WindowHandle )
					throw exception();

			// Show main window.

				ShowWindow( WindowHandle, CmdShow );

			// Initialize input manager.

				INPUT_MANAGER.Initialize( reinterpret_cast< size_t >( WindowHandle ) );

			// Initialize audio manager.

				AUDIO_MANAGER.Initialize();
				AUDIO_MANAGER.Load( "./startup.mp3", "Startup" );
				AUDIO_MANAGER.Load( "./music.mp3", "Music", true );
				AUDIO_MANAGER.Play( "Startup" );
				AUDIO_MANAGER.Play( "Music", true );

			// Initialize video manager.

				VIDEO_MANAGER.Initialize( WindowHandle, SCREEN_WIDTH, SCREEN_HEIGHT );

			// Enter main event loop.

				do
				{
					if( PeekMessage( &Message, nullptr, Null, Null, PM_REMOVE ) )
					{
						if( Message.message == WM_QUIT )
							Done = true;
						else
						{
							TranslateMessage( &Message );
							DispatchMessage( &Message );
						}
					}

					// Main Loop

						INPUT_MANAGER.Update();
						AUDIO_MANAGER.Update();
						VIDEO_MANAGER.Update();

						VIDEO_MANAGER.Begin();
						VIDEO_MANAGER.DrawQuad( 0, ( SCREEN_HEIGHT - 64 ), SCREEN_WIDTH, 64, 0.0f, 0.75f, 0.0f );
						VIDEO_MANAGER.DrawQuad( PlayerX, ( SCREEN_HEIGHT - 95 ), 32, 32, 0.75f, 0.75f, 0.75f );
						VIDEO_MANAGER.End();

						if( INPUT_MANAGER_KEYBOARD.isKeyDown( OIS::KC_ESCAPE ) )
							PostQuitMessage( Success );

						if( INPUT_MANAGER_KEYBOARD.isKeyDown( OIS::KC_LEFT ) )
							PlayerX -= PlayerSpeed;

						if( INPUT_MANAGER_KEYBOARD.isKeyDown( OIS::KC_RIGHT ) )
							PlayerX += PlayerSpeed;

					// End of 'Main Loop'
				} while( !Done );

				Result = Message.wParam;
		}
		catch( exception Exception )
		{
			MessageBox( nullptr, Exception.what(), "Error!", ( MB_ICONEXCLAMATION | MB_OK ) );
		}

	// Return result to calling routine.

		return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Main.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
