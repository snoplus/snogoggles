////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::MapArea
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

#ifndef __Viewer_GUIs_MapArea__
#define __Viewer_GUIs_MapArea__

#include <SFML/System/Vector2.hpp>

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
namespace GUIs
{

class MapArea : public GUI
{
public:
  inline MapArea( RectPtr rect, unsigned int guiID );
  virtual ~MapArea() {};

  virtual void Render( RWWrapper& windowApp ) { };
  virtual GUIEvent NewEvent( const Event& event );

  inline sf::Vector2<double> GetPosition();
protected:
  sf::Vector2<double> fCurrentPos;
};

inline
MapArea::MapArea( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 

}

inline sf::Vector2<double>
MapArea::GetPosition()
{
  return fCurrentPos;
}

} // ::GUIs

} // ::Viewer

#endif
