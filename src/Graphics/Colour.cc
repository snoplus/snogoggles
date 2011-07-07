#include <Viewer/Colour.hh>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace Viewer {

const Colour Colour::Black( sf::Color::Black );
const Colour Colour::White( sf::Color::White );
const Colour Colour::Red( sf::Color::Red );
const Colour Colour::Green( sf::Color::Green );
const Colour Colour::Blue( sf::Color::Blue );
const Colour Colour::Yellow( sf::Color::Yellow );
const Colour Colour::Magenta( sf::Color::Magenta );
const Colour Colour::Cyan( sf::Color::Cyan );

Colour::Colour( const sf::Color& c )
{
    r = c.r; // Copies the red value.
    g = c.g; // Copies the green value.
    b = c.b; // Copies the blue value.
    a = c.a; // Copies the alpha value.
}

void Colour::SetColorGL( Color& colour )
{
    glColor4f( 
        colour.r/fRatio, 
        colour.g/fRatio, 
        colour.b/fRatio, 
        colour.a/fRatio 
    );
}

}; // namespace Viewer
