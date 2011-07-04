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
///          coordinates (as used in GUI objects) goes from [0,1]. The sf
///          events use window (size) coordinates (from top left). This
///          class converts between the three. Furthermore as 3d frames need
///          to position a viewport relative to the bottom left position
///          and the RenderWindow windw (size) NOT resolution, a couple of 
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
  static inline sf::Vector2<double> GetWindowSize();
  static inline void SetResolution( double width, double height );
  static inline sf::Vector2<double> GetResolution();

  static sf::Vector2<double> WindowToResolutionCoord( const sf::Vector2<double>& windowCoord );
  static sf::Vector2<double> ResolutionToWindowCoord( const sf::Vector2<double>& resolutionCoord );

  static sf::Rect<double> WindowToResolutionRect( const sf::Rect<double>& windowRect );
  static sf::Rect<double> ResolutionToWindowRect( const sf::Rect<double>& resolutionRect );

  // Useful functions

  FrameCoord();
  FrameCoord( sf::Rect<double>& rhs );

  // Now Frame dependent functions

  sf::Vector2<double> ResolutionToFrameCoord( const sf::Vector2<double>& resolutionCoord ) const;
  sf::Vector2<double> FrameToResolutionCoord( const sf::Vector2<double>& frameCoord ) const;
  
  sf::Rect<double> ResolutionToFrameRect( const sf::Rect<double>& resolutionRect ) const;
  sf::Rect<double> FrameToResolutionRect( const sf::Rect<double>& frameRect ) const;

  // Frame functions

  inline void SetRect( const sf::Rect<double> frameRect );
  inline sf::Rect<double> GetRect() const;
  sf::Rect<double> Get3dViewport() const;
  
  bool ContainsPoint( const sf::Vector2<double>& resolutionCoord ) const;

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

sf::Vector2<double> 
FrameCoord::GetWindowSize()
{
  return sf::Vector2<double>( fsWindowWidth, fsWindowHeight );
}

void 
FrameCoord::SetResolution( double width, double height )
{
  fsResolutionWidth = width;
  fsResolutionHeight = height;
}

sf::Vector2<double> 
FrameCoord::GetResolution()
{
  return sf::Vector2<double>( fsResolutionWidth, fsResolutionHeight );
}

void 
FrameCoord::SetRect( const sf::Rect<double> frameRect )
{
  fRect = frameRect;
}

sf::Rect<double> 
FrameCoord::GetRect() const
{
  return fRect;
}

} // ::Viewer

#endif
