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
  class Rect;
  class Shape;
  class Sprite;
  class Text;
  class ProjectionImage;

class RWWrapper
{
public:
  enum ETextAspect { eNone, eWidth, eHeight };

  RWWrapper( sf::RenderWindow& renderWindow, Rect& motherRect );

  void Draw( Shape& object );
  void Draw( Sprite& object );
  void Draw( ProjectionImage& object );
  void Draw( Text& object, ETextAspect textScaling = eNone );
  unsigned int GetFrameTime();

protected:
  void DrawObject( sf::Drawable& object );

  sf::RenderWindow& fRenderWindow;
  Rect& fMotherRect;
};

} // ::Viewer

#endif
