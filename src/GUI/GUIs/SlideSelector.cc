#include <SFML/Window/Event.hpp>

#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/SlideSelector.hh>
#include <Viewer/ProjectionImage.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

SlideSelector::SlideSelector( RectPtr rect, unsigned int guiID )
  : GUI( rect, guiID )
{
  fImage = new ProjectionImage( rect );
  fSliding = false;
}

SlideSelector::~SlideSelector()
{
  delete fImage;
}

void
SlideSelector::Initialise( vector<double> stops )
{
  fStops = stops;
  fCurrentPos = 0.0;
}

GUIEvent
SlideSelector::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  sf::Vector2<double> resPos = event.GetPos();
  sf::Rect<double> resRect = fRect->GetRect( Rect::eResolution );
  sf::Vector2<double> pos = sf::Vector2<double>( ( resPos.x - resRect.left ) / resRect.width, ( resPos.y - resRect.top ) / resRect.height );
  switch( event.type )
    {
    case sf::Event::MouseButtonPressed:
      fSliding = true;
    case sf::Event::MouseMoved:
      if( fSliding )
        {
          fCurrentPos = pos.x;
          for( vector<double>::const_iterator iTer = fStops.begin(); iTer != fStops.end(); iTer++ )
            if( fabs( fCurrentPos - *iTer ) < 0.05 )
              fCurrentPos = *iTer;
          retEvent = GUIEvent( fID, fGlobalID );
        }
      break;
    case sf::Event::MouseButtonReleased:
    case sf::Event::LostFocus:
      fSliding = false;
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    }
  return retEvent;
}

void
SlideSelector::Render( RWWrapper& renderApp )
{
  const double kBarHeight = 0.1;
  const double kStopWidth = 0.05;
  fImage->Clear();
  // First draw the horizontal bar
  sf::Vector2<double> pos( 0.0, 0.5 - kBarHeight / 2.0 );
  sf::Vector2<double> size( 1.0, kBarHeight );
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  // Now draw the stop points
  pos.y = 0.1;
  size.x = kStopWidth;
  size.y = 0.4;
  for( vector<double>::const_iterator iTer = fStops.begin(); iTer != fStops.end(); iTer++ )
    {
      pos.x = *iTer;
      fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
    }
  // Now draw the current position
  pos.x = fCurrentPos;
  size.y = 0.8;
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetA( eActive ) );

  fImage->Update();
  renderApp.Draw( *fImage );
}
