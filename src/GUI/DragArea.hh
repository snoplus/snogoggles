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

namespace Viewer
{
namespace GUIs
{

class DragArea : public GUI
{
public:
  inline DragArea( const sf::Rect<double>& rect, unsigned int guiID );
  virtual ~DragArea() {};

  virtual void RenderT( sf::RenderWindow& windowApp ) { };
  virtual void Render( RWWrapper& windowApp ) { };
  virtual GUIReturn NewEvent( UIEvent& event );

  inline sf::Vector2<double> GetMoveDelta();
protected:
  sf::Vector2<double> fStartPos;
  sf::Vector2<double> fCurrentPos;
  bool fPressed;
};

DragArea::DragArea( const sf::Rect<double>& rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fPressed = false;
}

sf::Vector2<double>
DragArea::GetMoveDelta()
{
  return fCurrentPos - fStartPos;
}

} // ::GUIs

} // ::Viewer

#endif
