////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::DragArea
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

#ifndef __Viewer_GUIs_DragArea__
#define __Viewer_GUIs_DragArea__

#include <SFML/System/Vector2.hpp>

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
namespace GUIs
{

class DragArea : public GUI
{
public:
  inline DragArea( RectPtr rect, unsigned int guiID );
  virtual ~DragArea() {};

  virtual void Render( RWWrapper& windowApp ) { };
  virtual GUIEvent NewEvent( const Event& event );

  inline sf::Vector2<double> GetMoveDelta();
protected:
  sf::Vector2<double> fStartPos;
  sf::Vector2<double> fCurrentPos;
  bool fPressed;
};

inline
DragArea::DragArea( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fPressed = false;
}

inline sf::Vector2<double>
DragArea::GetMoveDelta()
{
  return fCurrentPos - fStartPos;
}

} // ::GUIs

} // ::Viewer

#endif
