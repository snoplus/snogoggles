////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::CheckBoxLabel
///
/// \brief   Label with a check box next to it
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     30/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_CheckBoxLabel__
#define __Viewer_GUIs_CheckBoxLabel__

#include <string>

#include <Viewer/Persist.hh>
#include <Viewer/RectPtr.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{ 
  class Sprite;
  class Text;
  class RWWrapper;

namespace GUIs
{

class CheckBoxLabel : public Persist
{
public:
  CheckBoxLabel( RectPtr rect, unsigned int guiID );
  virtual ~CheckBoxLabel();

  void SetLabel( const std::string& label );

  void Render( RWWrapper& windowApp );
protected:
  sf::Texture* fBoxTextures[2];
  Sprite* fBox;
  Text* fLabel;
};

} // ::GUIs

} // ::Viewer

#endif
