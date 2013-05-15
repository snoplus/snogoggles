#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <sstream>

#include <Viewer/RWWrapper.hh>
#include <Viewer/RectPtr.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/PixelImage.hh>
#include <Viewer/Text.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

RWWrapper::RWWrapper( sf::RenderWindow& renderWindow )
  : fRenderWindow( renderWindow )
{
  stringstream fontFileName;
  fontFileName << getenv( "VIEWERROOT" ) << "/gui/" << GUIProperties::GetInstance().GetConfiguration( "Font" )->GetS( "type" );
  fFont.loadFromFile( fontFileName.str() );
}

void 
RWWrapper::Draw( Sprite& object )
{
  sf::Sprite sfmlSprite( object.GetTexture() );
  sf::Rect<double> resPos = object.GetRect()->GetRect( Rect::eResolution );
  sfmlSprite.setPosition( resPos.left, resPos.top );
  sfmlSprite.setScale( resPos.width / object.GetTexture().getSize().x, resPos.height / object.GetTexture().getSize().y );
  DrawObject( sfmlSprite );
}

void 
RWWrapper::Draw( Text& object )
{
  sf::Text sfmlText( object.GetString(), fFont );
  sf::Rect<double> resPos = object.GetRect()->GetRect( Rect::eResolution );
  if( object.GetCharSize() > 0 )
    sfmlText.setCharacterSize( object.GetCharSize() );
  else
    {
      // First find the largest character size that works
      for( unsigned int charSize = 2; charSize < 40; charSize++ )
        {
          sfmlText.setCharacterSize( charSize );
          const sf::Rect<float> bounds = sfmlText.getGlobalBounds();
          if( bounds.width > resPos.width || bounds.height > resPos.height )
            {
              sfmlText.setCharacterSize( charSize - 1 );
              break;
            }
        }
    }
  double yOffset = sfmlText.getGlobalBounds().top;
  // Now se the position
  sfmlText.setPosition( resPos.left - sfmlText.getGlobalBounds().left, resPos.top - yOffset );
  sfmlText.setColor( object.GetColour() );
  DrawObject( sfmlText );
}

void
RWWrapper::Draw( PixelImage& object )
{
  sf::Sprite sfmlSprite( object.GetTexture() );
  sf::Rect<double> resPos = object.GetRect()->GetRect( Rect::eResolution );
  sfmlSprite.setPosition( resPos.left, resPos.top );
  sfmlSprite.setScale( resPos.width / object.GetTexture().getSize().x, resPos.height / object.GetTexture().getSize().y );
  DrawObject( sfmlSprite );
}

void 
RWWrapper::DrawObject( sf::Drawable& object )
{
  fRenderWindow.draw( object );
}

sf::Time
RWWrapper::GetFrameTime()
{
  return fClock.getElapsedTime();
}
