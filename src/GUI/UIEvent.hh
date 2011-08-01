////////////////////////////////////////////////////////////////////////
/// \class UIEvent
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_UIEvent__
#define __Viewer_UIEvent__

#include <SFML/Window/Event.hpp>

#include <Viewer/Coord.hh>

namespace Viewer
{
  class Rect;

class UIEvent : public sf::Event
{
public:
  UIEvent( sf::Event& event, Rect& motherRect );

  Coord GetCoord() { return fCoord; }
  sf::Vector2<double> GetLocalCoord();
  sf::Vector2<double> GetResolutionCoord();
private:
  Coord fCoord;
  Rect& fMotherRect;
};

} // ::Viewer

#endif
