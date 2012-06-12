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
  if( event.Type == sf::Event::KeyPressed )
    {
      if( event.Key.Code == sf::Keyboard::Up && event.Key.Control == true )
        fCurrentDesktop += 1 % numDesktops;
      else if( event.Key.Code == sf::Keyboard::Down && event.Key.Control == true )
        fCurrentDesktop -= 1 % numDesktops;
      if( event.Key.Code == sf::Keyboard::Right && event.Key.Control == true )
        fCurrentDesktop += 2 % numDesktops;
      else if( event.Key.Code == sf::Keyboard::Left && event.Key.Control == true )
        fCurrentDesktop -= 2 % numDesktops;
    }
}

void
DesktopPanel::EventLoop()
{
  DataStore& events = DataStore::GetInstance();
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID >= 10 && fEvents.front().fguiID < 10 + GUIProperties::GetInstance().GetNumDesktops() )
        fCurrentDesktop = fEvents.front().fguiID - 10;
      for( unsigned int iDesktop = 10; iDesktop < 10 + GUIProperties::GetInstance().GetNumDesktops(); iDesktop++ )
        if( iDesktop != fCurrentDesktop + 10 )
          dynamic_cast<GUIs::Persist*>( fGUIs[iDesktop] )->SetState( false );
      fEvents.pop();
    }
  if( fLabels.count( 0 ) )
    {
      stringstream temp;
      temp << fCurrentDesktop;
      fLabels[0]->SetString( temp.str() );
    }
}

void 
DesktopPanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
  dynamic_cast<GUIs::Persist*>( fGUIs[fCurrentDesktop + 10] )->SetState( true );
}

void
DesktopPanel::PostInitialise( const ConfigurationTable* configTable )
{

}

void
DesktopPanel::LoadGUIConfiguration( const ConfigurationTable* config )
{
  for( unsigned int uGUIs = 0; uGUIs < config->GetNumTables(); uGUIs++ )
    {
      const ConfigurationTable* objectConfig = config->GetTable( uGUIs );
      if( objectConfig->GetName() == string( "gui" ) )
        {
          sf::Rect<double> posRect( objectConfig->GetD( "x" ), objectConfig->GetD( "y" ), objectConfig->GetD( "width" ), objectConfig->GetD( "height" ) );
          fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI< GUIs::Persist >( posRect, objectConfig->GetI( "effect" ) );
          dynamic_cast<GUIs::Persist*>( fGUIs[objectConfig->GetI( "effect" )] )->Initialise( 12 );
        }
    }
}

void
DesktopPanel::SaveConfiguration( ConfigurationTable* configTable )
{

}
