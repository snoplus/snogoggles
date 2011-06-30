#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/PinButton.hh>
#include <Viewer/FrameCoord.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

PinButton::PinButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  fButtonBox = new sf::Shape( sf::Shape::Rectangle( 0.0, 0.0, 1.0, 1.0, sf::Color( 255, 255, 255 ), 0.1, sf::Color( 0, 0, 0 ) ) );
  fLine1 = new sf::Shape( sf::Shape::Line( 0.5, 0.0, 0.5, 1.0, 0.1, sf::Color( 0, 0, 0 ) ) );
  fLine2 = new sf::Shape( sf::Shape::Line( 0.0, 0.5, 1.0, 0.5, 0.1, sf::Color( 0, 0, 0 ) ) );
}

PinButton::~PinButton()
{
  delete fButtonBox;
  delete fLine1;
  delete fLine2;
}

void 
PinButton::Render( sf::RenderWindow& windowApp, const FrameCoord& frameCoord )
{
  sf::Rect<double> boundingBox = frameCoord.FrameToResolutionRect( fRect );
  fButtonBox->SetPosition( boundingBox.Left, boundingBox.Top );
  fButtonBox->SetScale( boundingBox.Width, boundingBox.Height );
  if( fPressed )
    fButtonBox->SetColor( sf::Color( 200, 200, 200 ) );
  else
    fButtonBox->SetColor( sf::Color( 255, 255, 255 ) );
  fLine1->SetPosition( boundingBox.Left, boundingBox.Top );
  fLine1->SetScale( boundingBox.Width, boundingBox.Height );
  fLine2->SetPosition( boundingBox.Left, boundingBox.Top );
  fLine2->SetScale( boundingBox.Width, boundingBox.Height );

  windowApp.Draw( *fButtonBox );
  windowApp.Draw( *fLine1 );
  windowApp.Draw( *fLine2 );
}
