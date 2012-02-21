////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::GenericTimer
///
/// \brief   Generic button
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     11/07/11 : Olivia Wasalski - First Revision, New File. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_GenericTimer__
#define __Viewer_GUIs_GenericTimer__

#include <Viewer/Timer.hh>
#include <Viewer/RectPtr.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{  
  class Sprite;
namespace GUIs
{

class GenericTimer : public Timer
{
public:

  GenericTimer( RectPtr rect, unsigned int guiID );
  
  virtual ~GenericTimer();

  void Render( RWWrapper& windowApp );
  
protected:
  sf::Texture* fTextures[2];
  Sprite* fSprite;
};


} // ::GUIs

} // ::Viewer

#endif
