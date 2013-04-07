////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameOutline
///
/// \brief   This class draws the frame outline
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Draws the frame outline.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameOutline__
#define __Viewer_FrameOutline__

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/RectPtr.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class Sprite;

class FrameOutline
{
public:
  FrameOutline( RectPtr rect );
  ~FrameOutline();
  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* );
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp );
  /// Set the top bar position
  void SetRect( const sf::Rect<double>& rect );
private:
  RectPtr fRect; /// < The Top bar location

  Sprite* fLeft;
  Sprite* fBottom;
  Sprite* fRight;
  Sprite* fBottomLeft;
};

} //::Viewer

#endif
