////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::GUIImagePersist
///
/// \brief   Persistant GUI image
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_GUIImagePersist__
#define __Viewer_GUIs_GUIImagePersist__

#include <Viewer/Persist.hh>
#include <Viewer/GUITextureManager.hh>
#include <Viewer/RectPtr.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{  
namespace GUIs
{

class GUIImagePersist : public Persist
{
public:
  GUIImagePersist( RectPtr rect, 
		   unsigned int guiID );
  virtual ~GUIImagePersist();

  void Initialise( EGUITexture image );
  
  void Render( RWWrapper& renderApp );
protected:
  sf::Texture* fPersist[3];
};


} // ::GUIs

} // ::Viewer

#endif
