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

namespace sf
{
  class Drawable;
  class Shader;
  class RenderWindow;
}

namespace Viewer
{
  class FrameCoord;
  class Shape;
  class Sprite;
  class Text;

class RWWrapper
{
public:
  RWWrapper( sf::RenderWindow& renderWindow, FrameCoord& frameCoord );

  void Draw( Shape& object );
  void Draw( Sprite& object );
  void Draw( Text& object );

protected:
  void DrawObject( sf::Drawable& object );

  sf::RenderWindow& fRenderWindow;
  FrameCoord& fFrameCoord;
};

} // ::Viewer

#endif
