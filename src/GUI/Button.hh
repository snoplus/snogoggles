////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Button
///
/// \brief   A Base class for button GUI objects
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Button__
#define __Viewer_GUIs_Button__

#include <Viewer/GUI.hh>

namespace Viewer
{
namespace GUIs
{

class Button : public GUI
{
public:
  virtual void Render( sf::RenderWindow& windowApp ) = 0;
  virtual UIEvent NewEvent( sf::Event& event );
protected:
  bool fPressed;
};

} // ::GUIs

} // ::Viewer

#endif
