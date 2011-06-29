#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Viewer/ViewerWindow.hh>
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
  // Draw a splash background
  
  fWindowApp->Display();
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
      if( event.Type == sf::Event::Closed )
	fWindowApp->Close();
    }
}

void
ViewerWindow::RenderLoop()
{
  fWindowApp->Display();
}
