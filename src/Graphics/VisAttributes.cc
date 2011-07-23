#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/VisAttributes.hh>

namespace Viewer {

VisAttributes::VisAttributes()
{
    fColour = Colour( sf::Color::Black );
    fVisible = false;
}

VisAttributes::VisAttributes( const Colour& colour, bool visible )
{
    fColour = colour;
    fVisible = visible;
}

void VisAttributes::Load( ConfigurationTable* configTable )
{
    bool visible = ConfigTableUtils::GetBoolean( configTable, "visible" );
    fColour.LoadFromParentTable( configTable, "colour" );
    fVisible = visible;
}

void VisAttributes::Save( ConfigurationTable* configTable ) const
{
    ConfigTableUtils::SetBoolean( configTable, "visible", fVisible );
    fColour.SaveToParentTable( configTable, "colour" );
}

}; // namespace Viewer
