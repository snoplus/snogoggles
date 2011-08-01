#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Viewer/RWWrapper.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Shape.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/PixelImage.hh>
#include <Viewer/Text.hh>
using namespace Viewer;

#include <iostream>
using namespace std;

RWWrapper::RWWrapper( sf::RenderWindow& renderWindow, Rect& motherRect )
  : fRenderWindow( renderWindow ), fMotherRect( motherRect )
{

}

void 
RWWrapper::Draw( Shape& object )
{
  sf::Shape newObject( object );
  Rect drawRect;
  sf::Rect<double> oldObjectRect = object.GetBoundingRect(); // C++0x needed, this is annoying
  drawRect.SetFromLocalRect( oldObjectRect, fMotherRect );
  sf::Rect<double> objectRect = drawRect.GetResolutionRect();
  newObject.SetPosition( objectRect.Left, objectRect.Top );
  newObject.Scale( objectRect.Width, objectRect.Height );
  DrawObject( newObject );
}

void 
RWWrapper::Draw( Sprite& object )
{
  sf::Sprite newObject( object );
  Rect drawRect;
  sf::Rect<double> oldObjectRect = object.GetBoundingRect(); // C++0x needed, this is annoying
  drawRect.SetFromLocalRect( oldObjectRect, fMotherRect );
  sf::Rect<double> objectRect = drawRect.GetResolutionRect();
  newObject.SetPosition(  objectRect.Left, objectRect.Top );
  newObject.Resize( objectRect.Width, objectRect.Height );
  DrawObject( newObject );
}
void 
RWWrapper::Draw( Text& object, ETextAspect textScaling )
{
  sf::Text newObject( object );
  sf::Rect<float> textRect = newObject.GetRect();
  Rect drawRect;
  sf::Rect<double> oldObjectRect = object.GetBoundingRect(); // C++0x needed, this is annoying
  drawRect.SetFromLocalRect( oldObjectRect, fMotherRect );
  sf::Rect<double> objectRect = drawRect.GetResolutionRect();
  newObject.SetPosition( objectRect.Left, objectRect.Top );
  switch( textScaling )
    {
    case eNone:
      newObject.Scale( objectRect.Width / textRect.Width, objectRect.Height / textRect.Height );
      break;
    case eWidth:
      newObject.Scale( objectRect.Width / textRect.Width, objectRect.Width / textRect.Width ) ;
      break;
    case eHeight:
      newObject.Scale( objectRect.Height / textRect.Height, objectRect.Height / textRect.Height );
      break;
    }
  DrawObject( newObject );
}

void
RWWrapper::Draw( PixelImage* object )
{
  sf::Sprite sprite = object->ToSprite();
  DrawObject( sprite );
}

void 
RWWrapper::DrawObject( sf::Drawable& object )
{
  fRenderWindow.Draw( object );
}

unsigned int 
RWWrapper::GetFrameTime()
{
  return fRenderWindow.GetFrameTime();
}
