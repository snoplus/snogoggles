////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::IncreaseButton
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

#ifndef __Viewer_GUIs_IncreaseButton__
#define __Viewer_GUIs_IncreaseButton__

#include <Viewer/Button.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{  
namespace GUIs
{

class IncreaseButton : public Button
{
public:
  IncreaseButton( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~IncreaseButton();
  
  void RenderT( sf::RenderWindow& windowApp );
  void Render( RWWrapper& windowApp );
protected:
  Sprite fButton;
};


} // ::GUIs

} // ::Viewer

#endif
