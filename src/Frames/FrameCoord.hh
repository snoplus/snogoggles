////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameCoord
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

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace Viewer
{

class FrameCoord
{
public:
  static inline void SetWindowSize( double width, double height );
  static inline void SetResolution( double width, double height );

  inline void SetFrameRect( const sf::Rect<double> frameRect );

  sf::Vector2<double> ToFrameCoord( const sf::Vector2<double>& resolutionCoord ) const;
  sf::Vector2<double> ToResolutionCoord( const sf::Vector2<double>& frameCoord ) const;
  
  sf::Rect<double> ToFrameRect( const sf::Rect<double>& resolutionRect ) const;
  sf::Rect<double> ToResolutionRect( const sf::Rect<double>& frameRect ) const;

  sf::Rect<double> Get3dViewport() const;
  sf::Rect<double> GetFrameRect() const;

private:
  sf::Rect<double> fRect;
  
  static double fsWindowHeight;
  static double fsWindowWidth;
  static double fsResolutionHeight;
  static double fsResolutionWidth;
};

void 
FrameCoord::SetWindowSize( double width, double height )
{
  fsWindowWidth = width;
  fsWindowHeight = height;
}

void 
FrameCoord::SetResolution( double width, double height )
{
  fsResolutionWidth = width;
  fsResolutionHeight = height;
}

void 
FrameCoord::SetFrameRect( const sf::Rect<double> frameRect )
{
  fRect = frameRect;
}

} // ::Viewer

#endif
