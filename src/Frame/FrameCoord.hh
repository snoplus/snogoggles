////////////////////////////////////////////////////////////////////////
/// \class FrameCoord
///
/// \brief   The Frame coordinates and coordinate system.
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Frames are positioned from the top left of the RenderWindow.
///          The position goes from [0, Resoution] in x and y. Local frame
///          coordinates (as used in GUI objects) goes from [0,1]. This
///          class converts between the two. Furthermore as 3d frames need
///          to position a viewport relative to the bottom left position
///          and the RenderWindow size NOT resolution, a couple of 
///          convinience methods are added to convert.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameCoord__
#define __Viewer_FrameCoord__

#include <SFML/Rect.hpp>
#include <SFML/Vector2.hpp>

namespace Viewer
{

class FrameCoord
{
public:
  static inline void SetWindowSize( double width, double height );
  static inline void SetResolution( double width, double height );

  inline void SetFrameRect( const sf::Rect frameRect );

  sf::Vector2<double> ToFrameCoord( const sf::Vector2<double>& resolutionCoord ) const;
  sf::Vector2<double> ToResolutionCoord( const sf::Vector2<double>& frameCoord ) const;
  
  sf::Rect ToFrameRect( const sf::Rect& resolutionRect ) const;
  sf::Rect ToResolutionRect( const sf::Rect& frameRect ) const;

  sf::Rect Get3dViewport() const;
  sf::Rect GetFrameRect() const;

private:
  sf::Rect fRect;
  
  static double fsWindowHeight;
  static double fsWindowWidth;
  static double fsResolutionHeight;
  static double fsResolutionWidth;
};

void SetWindowSize( double width, double height )
{
  fsWindowWidth = width;
  fsWindowHeight = height;
}

void SetResolution( double width, double height )
{
  fsResolutionWidth = width;
  fsResolutionHeight = height;
}

void SetFrameRect( const sf::Rect frameRect )
{
  fRect = frameRect;
}

} // ::Viewer

#endif
