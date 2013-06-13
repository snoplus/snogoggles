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

void 
AxisScaler::SetLimits( const double min,
                       const double max,
                       bool override )
{
  if( override )
    {
      fMaxLimit = max;
      fMinLimit = min;
      fMaxValue = max;
      fMinValue = min;
    }
  else
    {
      if( max > fMaxLimit )
        fMaxLimit = max;
      if( min < fMinLimit )
        fMinLimit = min;
    }
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
      if( fState == eScalingMin && pos.x < ValueToPos( fMaxValue ) - kOverlap )
        fMinValue = PosToValue( pos.x );
      else if( fState == eScalingMax && pos.x > ValueToPos( fMinValue ) + kOverlap )
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
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetA( eBase ) );
  pos = sf::Vector2<double>( ValueToPos( fMinValue ), 0.05 );
  size = sf::Vector2<double>( 0.025, 0.9 );
  if( fState == eNormal || fState == eScalingMax )
    fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetA( eBase ) );
  else if( fState == eScalingMin || fState == eBoth )
    fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetA( eActive ) );
  pos.x = ValueToPos( fMaxValue ) - size.x;
  if( fState == eNormal || fState == eScalingMin )
    fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetA( eBase ) );
  else if( fState == eScalingMax || fState == eBoth )
    fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetA( eActive ) );
  // Draw labels
  sf::Rect<double> textSize( 0.0, 0.5, 1.0 / 5.0, 0.5 );
  Text minLimit( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  stringstream temp; 
  temp.precision(0);
  temp << fixed << fMinLimit;
  minLimit.SetString( temp.str() );
  fAxisText.push_back( minLimit );
  
  textSize = sf::Rect<double>( 1.0 - 1.0 / 5.0, 0.5, 1.0 / 5.0, 0.5 );
  Text maxLimit( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  temp.str(""); temp << fMaxLimit;
  maxLimit.SetString( temp.str() );
  fAxisText.push_back( maxLimit );

  fImage->Update();
  renderApp.Draw( *fImage );
  for( vector<Text>::iterator iTer = fAxisText.begin(); iTer != fAxisText.end(); iTer++ )
    {
      iTer->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      renderApp.Draw( *iTer );
    }
}
