////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::TopBarRightButton
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     30/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_TopBarRightButton__
#define __Viewer_GUIs_TopBarRightButton__

#include <Viewer/Button.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{  

namespace GUIs
{

class TopBarRightButton : public Button
{
public:
  TopBarRightButton( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~TopBarRightButton();

  void RenderT( sf::RenderWindow& windowApp );
  void Render( RWWrapper& windowApp );
protected:
  Sprite fRight;
};

} // ::GUIs

} // ::Viewer

#endif
