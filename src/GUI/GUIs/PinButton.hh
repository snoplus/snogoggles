////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::PinButton
///
/// \brief   Button with an pin square
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     30/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_PinButton__
#define __Viewer_GUIs_PinButton__

#include <Viewer/Persist.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{ 
namespace GUIs
{

class PinButton : public Persist
{
public:
  PinButton( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~PinButton();

  void RenderT( sf::RenderWindow& windowApp );
  void Render( RWWrapper& windowApp );
  inline double PreferedRatio();
protected:
  Sprite fButton;
};

double
PinButton::PreferedRatio()
{
  return 1.0;
}

} // ::GUIs

} // ::Viewer

#endif
