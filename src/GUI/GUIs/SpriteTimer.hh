////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::SpriteTimer
///
/// \brief   Generic timer with a sprite
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

#ifndef __Viewer_GUIs_SpriteTimer__
#define __Viewer_GUIs_SpriteTimer__

#include <string>

#include <Viewer/GenericTimer.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{  
  class RWWrapper;
  class Sprite;
namespace GUIs
{

class SpriteTimer : public GenericTimer
{
public:

  SpriteTimer( RectPtr rect, 
	       unsigned int guiID );
  
  virtual ~SpriteTimer();

  void SetTexture( const std::string& filename );
  
  void Render( RWWrapper& windowApp );
  
protected:
  Sprite* fSprite;

};


} // ::GUIs

} // ::Viewer

#endif
