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

#include <Viewer/PixelImage.hh>

namespace Viewer
{
  class Colour;

class ProjectionImage : public PixelImage
{
public:
  ProjectionImage( RectPtr rect ) : PixelImage( rect ) { }
  ProjectionImage( RectPtr rect,
		   const int width,
		   const int height ) : PixelImage( rect, width, height ) { }
  void DrawDot( const sf::Vector2<double>& position,  /// < In local Coords
		const Colour& colour ); 

  /// Draw a standard size square
  void DrawSquare( const sf::Vector2<double>& position, /// < In local Coords
		   const Colour& colour ); 

  void DrawSquare( const sf::Vector2<double>& position, /// < In local Coords 
		   const sf::Vector2<double>& size,     /// < In local Coords
		   const Colour& colour );
  /// Draw a standard size hollow square
  void DrawHollowSquare( const sf::Vector2<double>& position, /// < In local Coords 
			 const Colour& colour );

  void DrawHollowSquare( const sf::Vector2<double>& position, /// < In local Coords 
			 const sf::Vector2<double>& size,     /// < In local Coords
			 const Colour& colour );
  /// Set the standard square size
  void SetSquareSize( const sf::Vector2<double>& size ); /// < In local Coords
  /// Get the standard square size
  sf::Vector2<double> GetSquareSize(); /// < In local Coords
private:
  /// Private draw square function
  void DrawSquare( const sf::Vector2<int>& position, /// < In pixels
		   const sf::Vector2<int>& size, /// < In pixels
		   const Colour& colour );
  sf::Vector2<int> fSquareSize; /// < Standard size of a square
};

} // ::Viewer

#endif
