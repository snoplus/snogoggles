////////////////////////////////////////////////////////////////////////
/// \class Viewer::Coord
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

#ifndef __Viewer_Coord__
#define __Viewer_Coord__

#include <SFML/System/Vector2.hpp>

namespace Viewer
{
  class Rect;

class Coord
{
public:
 
  void SetFromWindowCoord( const sf::Vector2<double>& windowCoord );
  void SetFromResolutionCoord( const sf::Vector2<double>& resolutionCoord );
  void SetFromLocalCoord( const sf::Vector2<double>& localCoord, Rect& motherRect );

  sf::Vector2<double> GetLocalCoord( Rect& motherRect );
  sf::Vector2<double> GetResolutionCoord();
  sf::Vector2<double> GetWindowCoord();

protected:
  sf::Vector2<double> fPosition;
  
///////////////////////////////////////////////////////////////////////
// Static aspect below
///////////////////////////////////////////////////////////////////////
public:
  static inline void SetWindowSize( double width, double height );
  static inline sf::Vector2<double> GetWindowSize();
  static inline void SetWindowResolution( double width, double height );
  static inline sf::Vector2<double> GetWindowResolution();

protected:
  static double fsWindowHeight;
  static double fsWindowWidth;
  static double fsResolutionHeight;
  static double fsResolutionWidth;
};

void 
Coord::SetWindowSize( double width, double height )
{
  fsWindowWidth = width;
  fsWindowHeight = height;
}

sf::Vector2<double> 
Coord::GetWindowSize()
{
  return sf::Vector2<double>( fsWindowWidth, fsWindowHeight );
}

void 
Coord::SetWindowResolution( double width, double height )
{
  fsResolutionWidth = width;
  fsResolutionHeight = height;
}

sf::Vector2<double> 
Coord::GetWindowResolution()
{
  return sf::Vector2<double>( fsResolutionWidth, fsResolutionHeight );
}

} // ::Viewer

#endif
