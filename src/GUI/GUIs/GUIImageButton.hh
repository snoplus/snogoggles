////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::GUIImageButton
///
/// \brief   GUI Image Button
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_GUIImageButton__
#define __Viewer_GUIs_GUIImageButton__

#include <Viewer/Button.hh>
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

class GUIImageButton : public Button
{
public:
  GUIImageButton( RectPtr rect, 
		  unsigned int guiID );
  virtual ~GUIImageButton();

  void Initialise( EGUITexture image );
  
  void Render( RWWrapper& renderApp );
protected:
  sf::Texture* fButton[3];
};


} // ::GUIs

} // ::Viewer

#endif
