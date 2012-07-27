#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <string>
#include <stdio.h>
using namespace std;

#include <Viewer/ViewerWindow.hh>
#include <Viewer/TextureManager.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Rect.hh>
#include <Viewer/RectPtr.hh>
#include <Viewer/Event.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/DesktopManager.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/DataStore.hh>
using namespace Viewer;

const int kConfigVersion = 1;

ViewerWindow::ViewerWindow()
{
  fMotherRect = &Rect::NewMother();
  sf::Rect<double> rect;
  // Mother Rect is the whole screen
  rect.left = 0.0; rect.width = 1.0; rect.top = 0.0; rect.height = 1.0;
  fMotherRect->SetRect( rect, Rect::eLocal );
}

ViewerWindow::~ViewerWindow()
{
  // All in the ~ViewerWindow, note MotherRect is deleted when reference count reaches zero.
}

void
ViewerWindow::PreInitialise( const ConfigurationTable* configTable )
{
  // Attempt to initialize the size of the depth and stencil buffers.
  // Fails on Linux, not sure about Mac.
  sf::ContextSettings settings;
  settings.depthBits         = 24; // Request a 24 bits depth buffer
  settings.stencilBits       = 8;  // Request a 8 bits stencil buffer
  sf::VideoMode fullScreen = sf::VideoMode::getDesktopMode();
  fullScreen.height -= 40.0; // Mac systems require this
  if( configTable != NULL )
    {
      fullScreen.width = configTable->GetI( "width" );
      fullScreen.height = configTable->GetI( "height" );
    }
  fWindowApp = new sf::RenderWindow( fullScreen, "SNO Goggles", sf::Style::Default, settings  ); 
  Rect::SetWindowSize( fWindowApp->getSize().x, fWindowApp->getSize().y );
  Rect::SetWindowResolution( fWindowApp->getSize().x, fWindowApp->getSize().y );  

  // This usage of width and height should not occur elsewhere in the viewer code, make use of Rects and Viewer::Sprite instead
  TextureManager& textures = TextureManager::GetInstance();
  sf::Texture* snoSplash = textures.GetTexture( "Logo.png" );
  sf::Texture* sfmlSplash = textures.GetTexture( "sfml.png" );
  const int windowWidth = fWindowApp->getSize().x;
  const int windowHeight = fWindowApp->getSize().y;
  // Can't draw textures directly, must wrap in a sprite and set the position.
  sf::Sprite snoSprite( *snoSplash );
  snoSprite.setPosition( windowWidth / 2 - snoSplash->getSize().x / 2, windowHeight / 2 - snoSplash->getSize().y / 2 );
  sf::Sprite sfmlSprite( *sfmlSplash );
  sfmlSprite.setPosition( windowWidth - sfmlSplash->getSize().x, windowHeight - sfmlSplash->getSize().y );
  // Now draw these logos
  fWindowApp->clear( sf::Color( 255, 255, 255, 255 ) ); 
  fWindowApp->draw( snoSprite );
  fWindowApp->draw( sfmlSprite );
  fWindowApp->display();
  // Now start building the desktop and frames
  fDesktopManager = new DesktopManager( RectPtr( fMotherRect ) );
  fDesktopManager->PreInitialise( configTable );
  fRWWrapper = new RWWrapper( *fWindowApp );
}

void
ViewerWindow::PostInitialise( const ConfigurationTable* configTable )
{
  fDesktopManager->PostInitialise( configTable );
}

void
ViewerWindow::Run()
{
  while( fWindowApp->isOpen() )
    {
      if( !EventLoop() ) // Returns false on user controlled close
        break;
      RenderLoop();
    }
}
void
ViewerWindow::SaveConfiguration( ConfigurationTable* configTable )
{
  sf::Vector2<double> size = Rect::GetWindowResolution();
  configTable->SetI( "width", size.x );
  configTable->SetI( "height", size.y );
  fDesktopManager->SaveConfiguration( configTable );
}

void
ViewerWindow::Destruct()
{
  // Must delete textures before the window, or get sfml segfault
  TextureManager::GetInstance().ClearTextures();
  delete fDesktopManager;
  delete fRWWrapper;
  fWindowApp->close();
  delete fWindowApp;
}

bool
ViewerWindow::EventLoop()
{
  DataStore::GetInstance().Reset();
  sf::Event event;
  while( fWindowApp->pollEvent( event ) )
    {
      switch( event.type )
        {
          // First ViewerWindow Specific Events
        case sf::Event::Closed:
          fWindowApp->close();
          break;
        case sf::Event::Resized:
          Rect::SetWindowSize( event.size.width, event.size.height );
          break;
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
          break;
          
          // Now events to use and then pass to frames
        case sf::Event::KeyPressed:
          if( event.key.code == sf::Keyboard::Escape )
            {
              // Start closing the viewer
              return false;
            }
          //Drop through
        default:
          Event viewerEvent( event );
          fDesktopManager->NewEvent( viewerEvent );
        }
    }
  // Now get Frames to deal with events
  fDesktopManager->EventLoop();
  return true;
}

void
ViewerWindow::RenderLoop()
{
  fRWWrapper->NewFrame();
  fWindowApp->setActive();
  SetGlobalGLStates();

  // SetGlobalGLStates clears the background colour to white.
  // This SFML call is unnecessary.
  //fWindowApp->Clear( sf::Color( 255, 255, 255 ) );

  fDesktopManager->ProcessData();
  fDesktopManager->Render3d( *fRWWrapper );
  fWindowApp->pushGLStates(); // This call seems to be necessary.
  fDesktopManager->Render2d( *fRWWrapper );
  fDesktopManager->RenderGUI( *fRWWrapper );
  fWindowApp->popGLStates(); // Matches the save call above.

  fWindowApp->display();
}

void 
ViewerWindow::SetGlobalGLStates()
{
  GUIProperties::GetInstance().GetGUIColourPalette().GetBackground().ClearOpenGL();
  glClearDepth(1.f); // Sets the depth buffer clear to 1.
  glClearStencil(0); // Sets the stencil buffer clear to 0.

  // Clears the color, depth and stencil buffers.
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

  // Enable Z-buffer read and write
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
}
