////////////////////////////////////////////////////////////////////////
/// \class Viewer::Colour
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     11/07/11 : P.Jones - First Revision, new file. \n
///     14/07/11 : Olivia Wasalski - Added a constructor which accepts an sf::Color. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Colour__
#define __Viewer_Colour__

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Config.hpp>


namespace Viewer
{

class Colour : public sf::Color
{
public:
  Colour() : sf::Color() { };
  Colour( sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha = 255 ) : sf::Color( red, green, blue, alpha ) { }
  Colour( const sf::Color& color ) : sf::Color( color ) { }

  inline void SetOpenGL();

  inline Colour AddColourFraction( const Colour& newColour, double fraction );
};

void
Colour::SetOpenGL()
{
  glColor4f( static_cast<float>( r ) / 255.0f, 
	     static_cast<float>( g ) / 255.0f, 
	     static_cast<float>( b ) / 255.0f, 
	     static_cast<float>( a ) / 255.0f );
}

Colour
Colour::AddColourFraction( const Colour& newColour, double fraction )
{
  double nR = this->r + fraction * ( newColour.r - this->r );
  double nG = this->g + fraction * ( newColour.g - this->g );
  double nB = this->b + fraction * ( newColour.b - this->b );
  double nA = this->a + fraction * ( newColour.a - this->a );
  return Colour( nR, nG, nB, nA );
}

} // ::Viewer

#endif
