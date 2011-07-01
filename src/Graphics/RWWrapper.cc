#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Viewer/RWWrapper.hh>
#include <Viewer/FrameCoord.hh>
#include <Viewer/Shape.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Text.hh>
using namespace Viewer;

#include <iostream>
using namespace std;

RWWrapper::RWWrapper( sf::RenderWindow& renderWindow, FrameCoord& frameCoord )
  : fRenderWindow( renderWindow ), fFrameCoord( frameCoord )
{

}

void 
RWWrapper::Draw( Shape& object )
{
  sf::Shape newObject( object );
  sf::Rect<double> objectRect = fFrameCoord.FrameToResolutionRect( object.GetBoundingRect() );
  newObject.SetPosition( objectRect.Left, objectRect.Top );
  newObject.Scale( objectRect.Width, objectRect.Height );
  DrawObject( newObject );
}

void 
RWWrapper::Draw( Sprite& object )
{
  sf::Sprite newObject( object );
  sf::Rect<double> objectRect = fFrameCoord.FrameToResolutionRect( object.GetBoundingRect() );
  newObject.SetPosition(  objectRect.Left, objectRect.Top );
  newObject.Resize( objectRect.Width, objectRect.Height );
  DrawObject( newObject );
}
void 
RWWrapper::Draw( Text& object )
{
  sf::Text newObject( object );
  sf::Rect<float> textRect = newObject.GetRect();
  sf::Rect<double> objectRect = fFrameCoord.FrameToResolutionRect( object.GetBoundingRect() );
  newObject.SetPosition( objectRect.Left, objectRect.Top );
  newObject.Scale( objectRect.Width / textRect.Width, objectRect.Height / textRect.Height );
  DrawObject( newObject );
}

void 
RWWrapper::DrawObject( sf::Drawable& object )
{
  fRenderWindow.Draw( object );
}
