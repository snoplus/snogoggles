#include <SFML/Graphics/Rect.hpp>

#include <sstream>
using namespace std;

#include <Viewer/Panel.hh>
#include <Viewer/Event.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Text.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;

Panel::Panel( RectPtr rect,
              const string& guiConfigName )
  : fRect( rect ), fGUIManager( rect ), fGUIConfigName( guiConfigName ), fEnabled( true )
{

}

Panel::~Panel()
{
  fGUIs.clear();
  for( map< int, Text* >::iterator iTer = fLabels.begin(); iTer != fLabels.end(); iTer++ )
    delete iTer->second;
  fLabels.clear();
  for( unsigned int uText = 0; uText < fTexts.size(); uText++ )
    delete fTexts[uText];
  fTexts.clear();
}

void 
Panel::NewEvent( const Event& event )
{
  if( !fEnabled )
    return;
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void 
Panel::PreInitialise( const ConfigurationTable* configTable )
{
  const ConfigurationTable* guiConfig = GUIProperties::GetInstance().GetConfiguration( fGUIConfigName );
  sf::Rect<double> panelRect( guiConfig->GetD( "x" ), guiConfig->GetD( "y" ), guiConfig->GetD( "width" ), guiConfig->GetD( "height" ) );
  fRect->SetRect( panelRect, Rect::eLocal );
  for( unsigned int uGUIs = 0; uGUIs < guiConfig->GetNumTables(); uGUIs++ )
    {
      const ConfigurationTable* objectConfig = guiConfig->GetTable( uGUIs );
      if( objectConfig->GetName() == string( "gui" ) ) // Then it is a GUI object
        {// PHIL: To implement, panels must do this themselves
          //sf::Rect<double> posRect( objectConfig->GetD( "x" ), objectConfig->GetD( "y" ), objectConfig->GetD( "width" ), objectConfig->GetD( "height" ) );
          //fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI( objectConfig->GetS( "type" ), posRect, objectConfig->GetI( "effect" ) );
        }
      else if( objectConfig->GetName() == string( "label" ) ) // Then it is a Label(Text) object
        {
          sf::Rect<double> posRect( objectConfig->GetD( "x" ), objectConfig->GetD( "y" ), objectConfig->GetD( "width" ), objectConfig->GetD( "height" ) );
          fLabels[objectConfig->GetI( "result" )] = new Text( RectPtr( fRect->NewDaughter( posRect, Rect::eLocal ) ) );
        }
      else if( objectConfig->GetName() == string( "text" ) ) // Should be Text then
        {
          sf::Rect<double> posRect( objectConfig->GetD( "x" ), objectConfig->GetD( "y" ), objectConfig->GetD( "width" ), objectConfig->GetD( "height" ) );
          Text* tempText = new Text( RectPtr( fRect->NewDaughter( posRect, Rect::eLocal ) ) );
          tempText->SetString( objectConfig->GetS( "caption" ) );
          fTexts.push_back( tempText );
        }
    }
  // Call the dervied class LoadGUIConfiguration
  LoadGUIConfiguration( guiConfig );
}

void
Panel::PostInitialise( const ConfigurationTable* configTable )
{

}

void 
Panel::Render( RWWrapper& renderApp )
{
  if( !fEnabled )
    return;
  fGUIManager.Render( renderApp );
  for( map< int, Text* >::iterator iTer = fLabels.begin(); iTer != fLabels.end(); iTer++ )
    {
      iTer->second->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      renderApp.Draw( *(iTer->second) );
    }
  for( unsigned int uText = 0; uText < fTexts.size(); uText++ )
    {
      fTexts[uText]->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      renderApp.Draw( *fTexts[uText] );
    }
}
