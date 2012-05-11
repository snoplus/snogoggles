#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Viewer/RWWrapper.hh>
#include <Viewer/RectPtr.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/PixelImage.hh>
#include <Viewer/Text.hh>
using namespace Viewer;

RWWrapper::RWWrapper( sf::RenderWindow& renderWindow )
  : fRenderWindow( renderWindow )
{
  fFont = sf::Font::GetDefaultFont(); // Bug fix line, SFML issue #59
}

void 
RWWrapper::Draw( Sprite& object )
{
  sf::Sprite sfmlSprite( object.GetTexture() );
  sf::Rect<double> resPos = object.GetRect()->GetRect( Rect::eResolution );
  sfmlSprite.SetPosition( resPos.Left, resPos.Top );
  sfmlSprite.SetScale( resPos.Width / object.GetTexture().GetWidth(), resPos.Height / object.GetTexture().GetHeight() );
  DrawObject( sfmlSprite );
}

void 
RWWrapper::Draw( Text& object )
{
  sf::Text sfmlText( object.GetString(), fFont );
  sf::Rect<double> resPos = object.GetRect()->GetRect( Rect::eResolution );
  sfmlText.SetPosition( resPos.Left, resPos.Top );
  // Now the character size, start with the height divided by number of lines
  double characterSize = resPos.Height / object.GetNumLines();
  if( characterSize * object.GetMaxLineLength() / 2.0 > resPos.Width )
    // Too large go for safer smaller
    characterSize = resPos.Width * 2.0 / object.GetMaxLineLength();
  if( characterSize < 1.0 )
    characterSize = 1.0;
  sfmlText.SetCharacterSize( characterSize ); // Must use this and not scale to avoid bounding box bug.
  sfmlText.SetColor( object.GetColour() );
  DrawObject( sfmlText );
}

void
RWWrapper::Draw( PixelImage& object )
{
  sf::Sprite sfmlSprite( object.GetTexture() );
  sf::Rect<double> resPos = object.GetRect()->GetRect( Rect::eResolution );
  sfmlSprite.SetPosition( resPos.Left, resPos.Top );
  sfmlSprite.SetScale( resPos.Width / object.GetTexture().GetWidth(), resPos.Height / object.GetTexture().GetHeight() );
  DrawObject( sfmlSprite );
}

void 
RWWrapper::DrawObject( sf::Drawable& object )
{
  fRenderWindow.Draw( object );
}

sf::Time
RWWrapper::GetFrameTime()
{
  return fClock.Restart();
}
