#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Viewer/RWWrapper.hh>
#include <Viewer/FrameCoord.hh>
#include <Viewer/Shape.hh>
#include <Viewer/Sprite.hh>
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
  sf::Rect<double> frameRect = fFrameCoord.GetRect();
  sf::Rect<double> objectRect = object.GetBoundingRect();
  newObject.SetPosition( frameRect.Left + objectRect.Left, frameRect.Top + objectRect.Top );
  newObject.Scale( objectRect.Width * frameRect.Width, objectRect.Height * frameRect.Height );
  DrawObject( newObject );
}

void 
RWWrapper::Draw( Sprite& object )
{
  sf::Sprite newObject( object );
  sf::Rect<double> frameRect = fFrameCoord.GetRect();
  sf::Rect<double> objectRect = object.GetBoundingRect();
  newObject.SetPosition( frameRect.Left + objectRect.Left, frameRect.Top + objectRect.Top );
  newObject.Resize( objectRect.Width * frameRect.Width, objectRect.Height * frameRect.Height );
  DrawObject( newObject );
}
void 
RWWrapper::Draw( sf::Text& object )
{

}

void 
RWWrapper::DrawObject( sf::Drawable& object )
{
  fRenderWindow.Draw( object );
}
