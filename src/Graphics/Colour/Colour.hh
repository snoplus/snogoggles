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
///     15/07/11 : Olivia Wasalski - Slight revision to make Colour const correct. \n
///     22/07/11 : Olivia Wasalski - Colour now also inherits fron Serializable. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Colour__
#define __Viewer_Colour__

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Config.hpp>

#include <Viewer/Serializable.hh>

namespace Viewer
{
    class ConfigurationTable;

class Colour : public sf::Color, public Serializable
{
public:
  /// Important that default colour is white
  Colour() : sf::Color( 255, 255, 255, 255 ) { };
  Colour( sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha = 255 ) : sf::Color( red, green, blue, alpha ) { }
  Colour( const sf::Color& color ) : sf::Color( color ) { }
  Colour( const ConfigurationTable* configTable );

  inline void SetOpenGL() const;
  inline void ClearOpenGL() const;

  Colour AddColourFraction( const Colour& newColour, double fraction ) const;

  void Load( const ConfigurationTable* configTable );
  void Save( ConfigurationTable* configTable ) const;
};

void
Colour::ClearOpenGL() const
{
  glClearColor( static_cast<float>( r ) / 255.0f, 
		static_cast<float>( g ) / 255.0f, 
		static_cast<float>( b ) / 255.0f, 
		static_cast<float>( a ) / 255.0f );
}

void
Colour::SetOpenGL() const
{
  glColor4f( static_cast<float>( r ) / 255.0f, 
	     static_cast<float>( g ) / 255.0f, 
	     static_cast<float>( b ) / 255.0f, 
	     static_cast<float>( a ) / 255.0f );
}

} // ::Viewer

#endif
