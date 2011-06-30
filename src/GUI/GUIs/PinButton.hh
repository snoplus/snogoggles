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

#include <Viewer/Button.hh>

namespace sf
{
  class Shape;
}

namespace Viewer
{
namespace GUIs
{

class PinButton : public Button
{
public:
  PinButton( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~PinButton();

  void Render( sf::RenderWindow& windowApp, const FrameCoord& frameCoord );
  inline double PreferedRatio();
protected:
  sf::Shape* fButtonBox;
  sf::Shape* fLine1;
  sf::Shape* fLine2;
};

double
PinButton::PreferedRatio()
{
  return 1.0;
}

} // ::GUIs

} // ::Viewer

#endif
