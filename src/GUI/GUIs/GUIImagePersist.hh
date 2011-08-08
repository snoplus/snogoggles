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
#include <Viewer/Sprite.hh>
#include <Viewer/GUIImageManager.hh>

namespace Viewer
{  
namespace GUIs
{

class GUIImagePersist : public Persist
{
public:
  GUIImagePersist( const sf::Rect<double>& rect, unsigned int guiID );
  virtual ~GUIImagePersist();

  void Initialise( EGUIImage image );
  
  void RenderT( sf::RenderWindow& windowApp );
  void Render( RWWrapper& windowApp );
protected:
  Sprite fPersist[3];
};


} // ::GUIs

} // ::Viewer

#endif
