////////////////////////////////////////////////////////////////////////
/// \class Event
///
/// \brief   Wrapper for sf::Events to simplify position access and 
///          conversion into the resolution space.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  All sf::Events are in the window space, all viewer obejcts
///          use resolution space. This converts between.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Event__
#define __Viewer_Event__

#include <SFML/Window/Event.hpp>

namespace Viewer
{

class Event : public sf::Event
{
public:

  Event( sf::Event::EventType eventType ) { Type = eventType; }
  /// Construct with the sf::Event and window space
  Event( sf::Event& event );
  /// Return the position, returns (0,0) if not a position event.
  sf::Vector2<double> GetPos() const;
};

} // ::Viewer

#endif
