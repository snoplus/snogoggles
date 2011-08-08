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
#include <Viewer/Sprite.hh>
#include <Viewer/GUIImageManager.hh>

namespace Viewer
{  
namespace GUIs
{

class GUIImageButton : public Button
{
public:
  GUIImageButton( const sf::Rect<double>& rect, unsigned int guiID );
  virtual ~GUIImageButton();

  void Initialise( EGUIImage image );
  
  void RenderT( sf::RenderWindow& windowApp );
  void Render( RWWrapper& windowApp );
protected:
  Sprite fButton[3];
};


} // ::GUIs

} // ::Viewer

#endif
