////////////////////////////////////////////////////////////////////////
/// \class Viewer::RWWrapper
///
/// \brief   sf::RenderWindow Wrapper
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Allows convineince of Drawing without having to cooridinate
///          correct
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RWWrapper__
#define __Viewer_RWWrapper__

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>

namespace sf
{
  class Drawable;
  class Shader;
  class RenderWindow;
}

namespace Viewer
{
  class Sprite;
  class Text;
  class PixelImage;

class RWWrapper
{
public:
  /// Must construct with a renderWindow
  RWWrapper( sf::RenderWindow& renderWindow );

  /// Draw a sprite onto the screen
  void Draw( Sprite& object );
  /// Draw some text onto the screen
  void Draw( Text& object );
  /// Draw a pixel image onto the screen
  void Draw( PixelImage& object );
  /// Return the time elapsed since the last frame
  sf::Time GetFrameTime();
  /// Called on new frame
  inline void NewFrame();
protected:
  /// Draw a sfml Drawable (everything that can be drawn is drawable)
  void DrawObject( sf::Drawable& object );

  sf::Clock fClock; /// < Calculates the time between frames
  sf::RenderWindow& fRenderWindow; /// < Reference to the RenderWindow
  sf::Font fFont;
};

inline void
RWWrapper::NewFrame()
{
  fClock.restart();
}

} // ::Viewer

#endif
