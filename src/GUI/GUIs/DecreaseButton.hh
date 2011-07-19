////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::DecreaseButton
///
/// \brief   Button with an exit square
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     30/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_DecreaseButton__
#define __Viewer_GUIs_DecreaseButton__

#include <Viewer/Button.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{  
namespace GUIs
{

class DecreaseButton : public Button
{
public:
  DecreaseButton( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~DecreaseButton();
  
  void RenderT( sf::RenderWindow& windowApp );
  void Render( RWWrapper& windowApp );
protected:
  Sprite fButton;
};


} // ::GUIs

} // ::Viewer

#endif
