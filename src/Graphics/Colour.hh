////////////////////////////////////////////////////////////////////////
/// \class Viewer::Colour
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     11/07/11 : P.Jones - First Revision, new file. \n
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

  inline void SetOpenGL();
};

void
Colour::SetOpenGL()
{
  glColor4f( static_cast<float>( r ) / 255.0f, 
	     static_cast<float>( g ) / 255.0f, 
	     static_cast<float>( b ) / 255.0f, 
	     static_cast<float>( a ) / 255.0f );
}

} // ::Viewer

#endif
