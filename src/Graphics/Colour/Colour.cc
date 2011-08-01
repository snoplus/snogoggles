#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Colour.hh>

namespace Viewer {

void Colour::Load( ConfigurationTable* configTable )
{
    // define this in two steps so that if an exception is thrown 
    // in one of the colours, none of them are changed.
    int red = configTable->GetI( "r" );
    int green = configTable->GetI( "g" );
    int blue = configTable->GetI( "b" );
    int alpha = configTable->GetI( "a" );

    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void Colour::Save( ConfigurationTable* configTable ) const
{
    configTable->SetI( "r", r );
    configTable->SetI( "g", g );
    configTable->SetI( "b", b );
    configTable->SetI( "a", a );
}

}; // namespace Viewer
