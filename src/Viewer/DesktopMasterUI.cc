#include <SFML/Window/Keyboard.hpp>

#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include <Viewer/DesktopMasterUI.hh>
#include <Viewer/RadioCheckBoxes.hh>
#include <Viewer/Event.hh>
#include <Viewer/Configuration.hh>
using namespace Viewer;

DesktopMasterUI::DesktopMasterUI( RectPtr rect,
				  unsigned int numDesktops )
  : fRect( rect ), fNumDesktops( numDesktops ), fGUIManager( rect )
{
  
}

DesktopMasterUI::~DesktopMasterUI()
{
  fDesktopRadio = NULL; // GUI Manager deletes this
}

void 
DesktopMasterUI::NewEvent( const Event& event )
{
  if( event.Type == sf::Event::KeyPressed )
    {
      if( event.Key.Code == sf::Keyboard::Up && event.Key.Control == true )
        fDesktopRadio->SetState( ( fDesktopRadio->GetState() + 1 ) % fNumDesktops );
      else if( event.Key.Code == sf::Keyboard::Down && event.Key.Control == true )
        fDesktopRadio->SetState( ( fDesktopRadio->GetState() - 1 ) % fNumDesktops );
      if( event.Key.Code == sf::Keyboard::Right && event.Key.Control == true )
        fDesktopRadio->SetState( ( fDesktopRadio->GetState() + 2 ) % fNumDesktops );
      else if( event.Key.Code == sf::Keyboard::Left && event.Key.Control == true )
        fDesktopRadio->SetState( ( fDesktopRadio->GetState() - 2 ) % fNumDesktops );
      fCurrentDesktop = fDesktopRadio->GetState();
    }
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void 
DesktopMasterUI::EventLoop()
{
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0:
          fCurrentDesktop = fDesktopRadio->GetState();
          break;
        }
      fEvents.pop();
    }
}

void 
DesktopMasterUI::Initialise()
{
  fCurrentDesktop = 0;
  sf::Rect<double> size;
  size.Left = 0.0; size.Top = 0.0; size.Height = 1.0; size.Width = 1.0;
  fDesktopRadio = fGUIManager.NewGUI<GUIs::RadioCheckBoxes>( size );
  vector<string> desktopNames;
  for( int iDesktop = 0; iDesktop < fNumDesktops; iDesktop++ )
    {
      stringstream sName;
      sName << iDesktop;
      desktopNames.push_back( sName.str() );
    }
  fDesktopRadio->Initialise( desktopNames, 4 );
}

void 
DesktopMasterUI::LoadConfiguration( Configuration& config )
{
  fCurrentDesktop = config.GetI( "currentDesktop" );
  fDesktopRadio->SetState( fCurrentDesktop );
}

void 
DesktopMasterUI::SaveConfiguration( Configuration& config )
{
  config.SetI( "currentDesktop", fCurrentDesktop );
}

void 
DesktopMasterUI::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}
