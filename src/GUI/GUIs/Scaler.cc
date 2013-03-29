#include <SFML/Window/Event.hpp>

#include <Viewer/Scaler.hh>
#include <Viewer/Event.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

const double kBarSize = 0.1; // Bar width 
const double kOverlap = kBarSize / 2.0;

Scaler::Scaler( RectPtr rect,
                unsigned int guiID )
  : GUI( rect, guiID )
{
  fMinValue = 0.0;
  fMaxValue = 0.99;
  fState = eNormal;
  fImage = new ProjectionImage( rect );
}

Scaler::~Scaler()
{
  delete fImage;
}

GUIEvent 
Scaler::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  sf::Vector2<double> resPos = event.GetPos();
  sf::Rect<double> resRect = fRect->GetRect( Rect::eResolution );
  sf::Vector2<double> pos = sf::Vector2<double>( ( resPos.x - resRect.left ) / resRect.width, ( resPos.y - resRect.top ) / resRect.height );
  switch( event.type )
    {
    case sf::Event::MouseButtonPressed: // Change the state to scaling
      if( fabs( pos.x - fMinValue ) < fabs( pos.x - fMaxValue ) )
        fState = eScalingMin;
      else
        fState = eScalingMax;
      break;
    case sf::Event::MouseMoved: // Change the scaling value
      if( fState == eScalingMin && pos.x < fMaxValue - kOverlap )
        fMinValue = pos.x;
      else if( fState == eScalingMax && pos.x > fMinValue + kOverlap )
        fMaxValue = pos.x;
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    case sf::Event::MouseButtonReleased: // Change the state back to normal
      if( fState == eScalingMin && pos.x < fMaxValue - kOverlap )
        fMinValue = pos.x;
      else if( fState == eScalingMax && pos.x > fMinValue + kOverlap )
        fMaxValue = pos.x;
    case sf::Event::LostFocus:
      fState = eNormal;
      retEvent = GUIEvent( fID, fGlobalID );
      if( fMinValue < 0.0 )
        fMinValue = 0.0;
      if( fMaxValue > 0.99 )
        fMaxValue = 0.99;
      break;
    }
  return retEvent;
}

void 
Scaler::Render( RWWrapper& renderApp )
{
  fImage->Clear();
  sf::Vector2<double> pos = sf::Vector2<double>( 0.0, 0.5 - kBarSize / 2.0 );
  sf::Vector2<double> size = sf::Vector2<double>( 1.0, kBarSize );
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  pos = sf::Vector2<double>( fMinValue, 0.1 );
  size = sf::Vector2<double>( 0.05, 0.8 );
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  pos.x = fMaxValue - size.x;
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  fImage->Update();
  renderApp.Draw( *fImage );
}
