////////////////////////////////////////////////////////////////////////
/// \class Viewer::Colour
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	07/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Colour__
#define __Viewer_Colour__

#include <SFML/Graphics.hpp>

namespace Viewer {

class Colour : public sf::Color {

public:

    /// Default constructor.
    Colour() : sf::Color() { }

    /// Detailed constructor.
    Colour( int red, int green, int blue, int alpha = 255 ) 
        : sf::Color( red, green, blue, alpha ) { }

    /// Copies the data from the input.
    Colour( const sf::Color& colour );

    /// Calls glColor4f() to set the rendering colour.
    static void SetColorGL( Color& colour );

    static const Colour Black;   ///< Black predefined colour
    static const Colour White;   ///< White predefined colour
    static const Colour Red;     ///< Red predefined colour
    static const Colour Green;   ///< Green predefined colour
    static const Colour Blue;    ///< Blue predefined colour
    static const Colour Yellow;  ///< Yellow predefined colour
    static const Colour Magenta; ///< Magenta predefined colour
    static const Colour Cyan;    ///< Cyan predefined colour

private:

    static const float fRatio = 255.0f;

}; // class Colour

}; // namespace Viewer

#endif // __Viewer_Colour__
