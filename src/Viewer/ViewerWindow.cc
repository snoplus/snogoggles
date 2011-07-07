#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <string>
#include <iostream>
using namespace std;

#include <Viewer/ViewerWindow.hh>
#include <Viewer/ImageManager.hh>
#include <Viewer/Configuration.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/FrameCoord.hh>
using namespace Viewer;

ViewerWindow* ViewerWindow::fViewer = NULL;

ViewerWindow::ViewerWindow()
{
  // TODO 
}

void
ViewerWindow::Initialise()
{
  // Load the configuration
  Configuration loadConfig( false );  
  int resX = loadConfig.GetI( "resX" ); 
  int resY = loadConfig.GetI( "resY" );
  FrameCoord::SetResolution( resX, resY );
  FrameCoord::SetWindowSize( resX, resY );

  fWindowApp = new sf::RenderWindow( sf::VideoMode( resX, resY ), "SNO Goggles" ); // Need to load Resolution
  // Draw a splash background
  ImageManager& im = ImageManager::GetInstance();
  sf::Sprite sp = im.NewSprite( "Logo.png" );
  sp.SetPosition( 400 - sp.GetSize().x / 2.0, 300 - sp.GetSize().y / 2.0 );

  fWindowApp->Clear( sf::Color( 255, 255, 255 ) );
  fWindowApp->Draw( sp );
  fWindowApp->Display();

  fFrameManager.Initialise( loadConfig );
}

void
ViewerWindow::Run()
{
  while( fWindowApp->IsOpened() )
    {
      EventLoop();
      RenderLoop();
    }
}

void
ViewerWindow::Destruct()
{
  Configuration saveConfig( true );
  saveConfig.SetI( "resX", static_cast<int>( FrameCoord::GetResolution().x ) );
  saveConfig.SetI( "resY", static_cast<int>( FrameCoord::GetResolution().y ) );
  fFrameManager.SaveConfiguration( saveConfig );
  saveConfig.SaveConfiguration();
  
  delete fWindowApp;
}

void
ViewerWindow::EventLoop()
{
  sf::Event event;
   while( fWindowApp->PollEvent( event ) )
    {
      switch( event.Type )
	{
// First ViewerWindow Specific Events
	case sf::Event::Closed:
	  fWindowApp->Close();
	  break;
	case sf::Event::Resized:
	  FrameCoord::SetWindowSize( event.Size.Width, event.Size.Height );
	  break;
	case sf::Event::LostFocus:
	case sf::Event::GainedFocus:
	  break;
// Now events to use and then pass to frames
	case sf::Event::KeyPressed:
	  if( event.Key.Code == sf::Key::Escape )
	    {
	      fWindowApp->Close();
	      break;
	    }
//Drop through
	default:
	  fFrameManager.NewEvent( event );
	}
      if( event.Type == sf::Event::Closed )
	fWindowApp->Close();
    }
  // Now get Frames to deal with events
  fFrameManager.EventLoop();
}

void
ViewerWindow::RenderLoop()
{
  fWindowApp->SetActive();
  SetGlobalGLStates();

  // SetGlobalGLStates clears the background colour to white.
  // This SFML call is unnecessary.
  //fWindowApp->Clear( sf::Color( 255, 255, 255 ) );

  fFrameManager.Render3d();
  fWindowApp->SaveGLStates(); // This call seems to be necessary.
  fFrameManager.Render2d( *fWindowApp );
  fFrameManager.RenderGUI( *fWindowApp );
  fWindowApp->RestoreGLStates(); // Matches the save call above.

  fWindowApp->Display();
}

void 
ViewerWindow::SetGlobalGLStates()
{
  glClearColor(1.f, 1.f, 1.f, 1.f); // Sets the clear color to white.
  glClearDepth(1.f); // Sets the depth buffer clear to 1.
  glClearStencil(0); // Sets the stencil buffer clear to 0.

  // Clears the color, depth and stencil buffers.
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

  // Enable Z-buffer read and write
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
}
