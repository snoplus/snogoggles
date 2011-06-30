////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::ExitButton
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

#ifndef __Viewer_GUIs_ExitButton__
#define __Viewer_GUIs_ExitButton__

#include <Viewer/Button.hh>

namespace sf
{
  class Shape;
}

namespace Viewer
{
namespace GUIs
{

class ExitButton : public Button
{
public:
  ExitButton( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~ExitButton();

  void Render( sf::RenderWindow& windowApp, const FrameCoord& frameCoord );
  inline double PreferedRatio();
protected:
  sf::Shape* fButtonBox;
  sf::Shape* fLine1;
  sf::Shape* fLine2;
};

double
ExitButton::PreferedRatio()
{
  return 1.0;
}

} // ::GUIs

} // ::Viewer

#endif
