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
  sf::Text sfmlText( object.GetString() );
  sf::Rect<double> resPos = object.GetRect()->GetRect( Rect::eResolution );
  sf::Rect<float> textRect = sfmlText.GetGlobalBounds(); 
  // The should be located at (0,0) at this stage, however it is often at (0,5) etc... due to character height matching
  double widthRatio = ( textRect.Width - textRect.Left ) / resPos.Width;
  double heightRatio = ( textRect.Height ) / resPos.Height; 
  double topCorrection = textRect.Top;
  if( widthRatio > heightRatio ) // Must minimise by width
    {
      sfmlText.Scale( 1.0 / widthRatio, 1.0 / widthRatio );
      topCorrection *= 1.0 / widthRatio;
    }
  else
    {
      sfmlText.Scale( 1.0 / heightRatio, 1.0 / heightRatio );
      topCorrection *= 1.0 / heightRatio;
    }
  sfmlText.SetPosition( resPos.Left, resPos.Top - topCorrection / 2.0 );
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
