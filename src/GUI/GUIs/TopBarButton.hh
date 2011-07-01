////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::TopBarButton
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

#ifndef __Viewer_GUIs_TopBarButton__
#define __Viewer_GUIs_TopBarButton__

#include <Viewer/Button.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{  

namespace GUIs
{

class TopBarButton : public Button
{
public:
  TopBarButton( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~TopBarButton();

  void Render( RWWrapper& windowApp );
  double PreferedRatio() { return 1.0; }
protected:
  Sprite fBar;
};

} // ::GUIs

} // ::Viewer

#endif
