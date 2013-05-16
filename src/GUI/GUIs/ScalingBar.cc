#include <SFML/Graphics/Rect.hpp>

using namespace std;

#include <Viewer/ScalingBar.hh>
#include <Viewer/Scaler.hh>
#include <Viewer/Button.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

ScalingBar::ScalingBar( RectPtr rect,
                        unsigned int guiID )
  : GUI( rect, guiID ), fGUIManager( rect )
{

}

ScalingBar::~ScalingBar()
{

}

void 
ScalingBar::Initialise()
{
  fGUIManager.Clear();
  sf::Rect<double> size;
  size.left = 0.0; size.width = 0.9;
  size.top = 0.0; size.height = 1.0;
  fScaler = dynamic_cast<GUIs::Scaler*>( fGUIManager.NewGUI<GUIs::Scaler>( size, Rect::eLocal ) );
  // Also add a reset button
  size.left = 0.9; size.width = 0.1;
  GUIs::Button* button = dynamic_cast<GUIs::Button*>( fGUIManager.NewGUI<GUIs::Button>( size, Rect::eLocal ) );
  button->Initialise( 44 );
}

void 
ScalingBar::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}

GUIEvent 
ScalingBar::NewEvent( const Event& event )
{
  vector<GUIEvent> guiEvents = fGUIManager.NewEvent( event );
  for( vector<GUIEvent>::const_iterator iTer = guiEvents.begin(); iTer != guiEvents.end(); iTer++ )
    if( iTer->IsNULL() == false && iTer->fguiID == 1 )
        fScaler->Reset();
      return GUIEvent( fID, fGlobalID );
  return GUIEvent();
}

void 
ScalingBar::SetState( const double min,
                      const double max )
{
  fScaler->SetState( min, max );
}

double 
ScalingBar::GetMin() const
{
  return fScaler->GetMin();
}

double 
ScalingBar::GetMax() const
{
  return fScaler->GetMax();
}

void 
ScalingBar::Reset()
{
  fScaler->Reset();
}
