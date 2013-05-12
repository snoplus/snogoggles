#include <SFML/Window/Event.hpp>

#include <sstream>
using namespace std;

#include <Viewer/DesktopPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Persist.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Text.hh>
using namespace Viewer;

DesktopPanel::DesktopPanel( RectPtr rect )
  : Panel( rect, "DesktopPanel" ), fCurrentDesktop(0)
{
 
}

DesktopPanel::~DesktopPanel()
{

}

void
DesktopPanel::NewEvent( const Event& event )
{
  Panel::NewEvent( event );
  const unsigned int numDesktops = GUIProperties::GetInstance().GetNumDesktops();
  if( event.type == sf::Event::KeyReleased )
    {
      if( event.key.control && event.key.shift && event.key.code == sf::Keyboard::Tab )
	{
	  if( fCurrentDesktop == 0 )
	    ChangeDesktop( numDesktops - 1 );
	  else
	    ChangeDesktop( ( fCurrentDesktop - 1 ) % numDesktops );
	}
      else if( event.key.control && !event.key.shift && event.key.code == sf::Keyboard::Tab )
	ChangeDesktop( ( fCurrentDesktop + 1 ) % numDesktops );
    }
}

void
DesktopPanel::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID >= 0 && fEvents.front().fguiID < GUIProperties::GetInstance().GetNumDesktops() )
        ChangeDesktop( fEvents.front().fguiID );
       fEvents.pop();
    }
}


void 
DesktopPanel::PreInitialise( const ConfigurationTable* configTable )
{
  const double numDesktops = static_cast<double>( GUIProperties::GetInstance().GetNumDesktops() );
  for( unsigned int iGUI = 0; iGUI < GUIProperties::GetInstance().GetNumDesktops(); iGUI++ )
    {
      sf::Rect<double> size( iGUI * 1.0 / numDesktops, 0.0, 1.0 / numDesktops, 1.0 );
      GUIs::Persist* tab = dynamic_cast<GUIs::Persist*>( fGUIManager.NewGUI<GUIs::Persist>( size, Rect::eLocal ) );
      tab->Initialise( 30 );
    }
  if( configTable != NULL )
    ChangeDesktop( configTable->GetI( "desktop" ) );
  else 
    ChangeDesktop( 0 );
}

void
DesktopPanel::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "desktop", fCurrentDesktop );
}

void
DesktopPanel::ChangeDesktop( const unsigned int newDesktop )
{
  for( unsigned int iGUI = 0; iGUI < GUIProperties::GetInstance().GetNumDesktops(); iGUI++ )
    {
      if( iGUI != newDesktop )
        dynamic_cast<GUIs::Persist*>( fGUIManager.GetGUI( iGUI ) )->SetState( false );
      else
        dynamic_cast<GUIs::Persist*>( fGUIManager.GetGUI( iGUI ) )->SetState( true );
    }
  fCurrentDesktop = newDesktop;
}
