////////////////////////////////////////////////////////////////////////
/// \class Viewer::ProjectionImage
///
/// \brief   Pixel image for projecting upon
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     31/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Quick way to draw very many squares in a pixel area. 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ProjectionImage__
#define __Viewer_ProjectionImage__

#include <SFML/System/Vector2.hpp>

#include <Viewer/Rect.hh>
#include <Viewer/PixelImage.hh>

namespace Viewer
{
  class Colour;
  class Rect;

class ProjectionImage : public PixelImage
{
public:
  void DrawSquare( const sf::Vector2<double>& position, /// < In local Coords 
		   const sf::Vector2<double>& size,     /// < In local Coords
		   const Colour& colour );
  void DrawHollowSquare( const sf::Vector2<double>& position, /// < In local Coords 
			 const sf::Vector2<double>& size,     /// < In local Coords
			 const Colour& colour );
};

} // ::Viewer

#endif
