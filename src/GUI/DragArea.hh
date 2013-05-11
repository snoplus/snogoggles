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

  inline sf::Vector2<double> GetMoveDelta() const;

  sf::Vector2<double> GetStartPos() const { return fStartPos; }
  sf::Vector2<double> GetEndPos() const { return fCurrentPos; }
  bool IsLeftPressed() const { return fLeftPressed; }
  bool IsRightPressed() const { return fRightPressed; }
protected:
  sf::Vector2<double> fStartPos;
  sf::Vector2<double> fCurrentPos;
  bool fLeftPressed;
  bool fRightPressed;
};

inline
DragArea::DragArea( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fLeftPressed = false;
  fRightPressed = false;
}

inline sf::Vector2<double>
DragArea::GetMoveDelta() const
{
  return fCurrentPos - fStartPos;
}

} // ::GUIs

} // ::Viewer

#endif
