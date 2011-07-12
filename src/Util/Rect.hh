////////////////////////////////////////////////////////////////////////
/// \class Viewer::Rect
///
/// \brief   The  coordinates and coordinate system.
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     12/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Every coordinate considered is saved as a resolution.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Rect__
#define __Viewer_Rect__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <Viewer/Coord.hh>

namespace Viewer
{

class Rect : public Coord
{
public:
   
  void SetFromWindowRect( const sf::Rect<double>& windowRect );
  void SetFromResolutionRect( const sf::Rect<double>& resolutionRect );
  void SetFromLocalRect( const sf::Rect<double>& localRect, Rect& motherRect );

  sf::Rect<double> GetLocalRect( Rect& motherRect );
  sf::Rect<double> GetResolutionRect();
  sf::Rect<double> GetWindowRect();
  
  void SetAsGLViewport();
  sf::Rect<double> GetViewport();

  bool ContainsResolutionPoint( const sf::Vector2<double>& point );
  bool ContainsLocalPoint( const sf::Vector2<double>& point, Rect& motherRect );

protected:
  sf::Vector2<double> fSize;
};

} // ::Viewer

#endif
