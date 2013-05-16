#include <SFML/Window/Event.hpp>

#include <sstream>
using namespace std;

#include <Viewer/AxisScaler.hh>
#include <Viewer/Event.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Text.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

const double kBarSize = 0.1; // Bar width 
const double kOverlap = kBarSize / 2.0;

AxisScaler::AxisScaler( RectPtr rect,
                        unsigned int guiID )
  : GUI( rect, guiID )
{
  fMinValue = 0.0;
  fMaxValue = 1.0;
  fState = eNormal;
  fImage = new ProjectionImage( rect );
}

AxisScaler::~AxisScaler()
{
  delete fImage;
}

GUIEvent 
AxisScaler::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  sf::Vector2<double> resPos = event.GetPos();
  sf::Rect<double> resRect = fRect->GetRect( Rect::eResolution );
  sf::Vector2<double> pos = sf::Vector2<double>( ( resPos.x - resRect.left ) / resRect.width, ( resPos.y - resRect.top ) / resRect.height );
  switch( event.type )
    {
    case sf::Event::MouseButtonPressed: // Change the state to scaling
      if( event.mouseButton.button == sf::Mouse::Left && fabs( PosToValue( pos.x ) - fMinValue ) < fabs( PosToValue( pos.x ) - fMaxValue ) )
        fState = eScalingMin;
      else if( event.mouseButton.button == sf::Mouse::Left )
        fState = eScalingMax;
      else if( event.mouseButton.button == sf::Mouse::Right )
        fState = eBoth;
      break;
    case sf::Event::MouseMoved: // Change the scaling value
      if( fState == eScalingMin && PosToValue( pos.x ) < fMaxValue - kOverlap )
        fMinValue = PosToValue( pos.x );
      else if( fState == eScalingMax && PosToValue( pos.x ) > fMinValue + kOverlap )
        fMaxValue = PosToValue( pos.x );
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    case sf::Event::MouseButtonReleased: // Change the state back to normal
      if( fState == eScalingMin && PosToValue( pos.x ) < fMaxValue - kOverlap )
        fMinValue = PosToValue( pos.x );
      else if( fState == eScalingMax && PosToValue( pos.x ) > fMinValue + kOverlap )
        fMaxValue = PosToValue( pos.x );
    case sf::Event::LostFocus:
      fState = eNormal;
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    }
  if( fMinValue < fMinLimit )
    fMinValue = fMinLimit;
  if( fMaxValue > fMaxLimit )
    fMaxValue = fMaxLimit;
  return retEvent;
}

double
AxisScaler::PosToValue( double pos ) const
{
  return pos * ( fMaxLimit - fMinLimit ) + fMinLimit;
}

double 
AxisScaler::ValueToPos( double value ) const
{
  return ( value - fMinLimit ) / ( fMaxLimit - fMinLimit ); 
}

void 
AxisScaler::Render( RWWrapper& renderApp )
{
  fAxisText.clear();
  fImage->Clear();
  sf::Vector2<double> pos = sf::Vector2<double>( 0.0, 0.25 - kBarSize / 2.0 );
  sf::Vector2<double> size = sf::Vector2<double>( 1.0, kBarSize );
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  pos = sf::Vector2<double>( ValueToPos( fMinValue ), 0.05 );
  size = sf::Vector2<double>( 0.05, 0.9 );
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  pos.x = ValueToPos( fMaxValue ) - size.x;
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  // Draw ticks and labels
  size = sf::Vector2<double>( 0.025, 2.0 * kBarSize );
  for( int iTick = 0; iTick < 5; iTick++ )
    {
      pos = sf::Vector2<double>( static_cast<double>( iTick ) / 5.0 + 0.1, 0.25 - kBarSize );
      fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
      sf::Rect<double> textSize( pos.x - 0.1, 0.5, 1.0 / 5.0, 0.5 );
      Text label( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
      stringstream temp;
      temp << fixed;
      temp.precision(0);
      temp << PosToValue( pos.x );
      label.SetString( temp.str() );
      fAxisText.push_back( label );
    }
  fImage->Update();
  renderApp.Draw( *fImage );
  for( vector<Text>::iterator iTer = fAxisText.begin(); iTer != fAxisText.end(); iTer++ )
    {
      iTer->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      renderApp.Draw( *iTer );
    }
}
