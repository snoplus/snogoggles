#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Viewer/ViewerWindow.hh>
#include <Viewer/ImageManager.hh>
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
  fWindowApp = new sf::RenderWindow( sf::VideoMode( 800, 600 ), "SNO Goggles" ); // Need to load Resolution
  FrameCoord::SetResolution( 800, 600 );
  FrameCoord::SetWindowSize( 800, 600 );
  // Draw a splash background
  ImageManager& im = ImageManager::GetInstance();
  sf::Sprite sp = im.NewSprite( "Logo.png" );
  sp.SetPosition( 400 - sp.GetSize().x / 2.0, 300 - sp.GetSize().y / 2.0 );

  fWindowApp->Clear( sf::Color( 255, 255, 255 ) );
  fWindowApp->Draw( sp );
  fWindowApp->Display();

  // Very temp
  ConfigurationTable a;
  fFrameManager.Initialise( a );
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
}

void
ViewerWindow::RenderLoop()
{
  fFrameManager.Render2d( *fWindowApp );
  fFrameManager.RenderGUI( *fWindowApp );
  
  fWindowApp->Display();
}
