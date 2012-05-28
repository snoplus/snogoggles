#include <SFML/Window/Event.hpp>

#include <Viewer/ScalingBar.hh>
#include <Viewer/Event.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

ScalingBar::ScalingBar( RectPtr rect,
                        unsigned int guiID )
  : GUI( rect, guiID )
{
  fMinValue = 0.0;
  fMaxValue = 0.99;
  fState = eNormal;
  fImage = new ProjectionImage( rect );
}

ScalingBar::~ScalingBar()
{
  delete fImage;
}

GUIEvent 
ScalingBar::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  sf::Vector2<double> resPos = event.GetPos();
  sf::Rect<double> resRect = fRect->GetRect( Rect::eResolution );
  sf::Vector2<double> pos = sf::Vector2<double>( ( resPos.x - resRect.Left ) / resRect.Width, ( resPos.y - resRect.Top ) / resRect.Height );
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed: // Change the state to scaling
      if( fabs( pos.x - fMinValue ) < fabs( pos.x - fMaxValue ) )
	fState = eScalingMin;
      else
	fState = eScalingMax;
      break;
    case sf::Event::MouseMoved: // Change the scaling value
      if( fState == eScalingMin )
	fMinValue = pos.x;
      else if( fState == eScalingMax )
	fMaxValue = pos.x;
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    case sf::Event::MouseButtonReleased: // Change the state back to normal
    case sf::Event::LostFocus:
      fState = eNormal;
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    }
  return retEvent;
}

void 
ScalingBar::Render( RWWrapper& renderApp )
{
  fImage->Clear();
  sf::Vector2<double> pos( fMinValue, 0.25 );
  sf::Vector2<double> size( 0.05, 0.5 );
  fImage->DrawSquare( pos, size, ColourPalette::gPalette.GetColour( fMinValue ) );
  pos.x = fMaxValue - size.x;
  fImage->DrawSquare( pos, size, ColourPalette::gPalette.GetColour( fMaxValue ) );
  pos = sf::Vector2<double>( 0.0, 0.5 - size.x / 2.0 );
  size = sf::Vector2<double>( 1.0, size.x );
  fImage->DrawSquare( pos, size, ColourPalette::gPalette.GetPrimaryColour( eGrey ) );
  fImage->Update();
  renderApp.Draw( *fImage );
}
