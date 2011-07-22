#include <Viewer/World.hh>

namespace Viewer {

World::World( Volume& volume, std::map< std::string, VisAttributes* >& visAttributes )
{
    fVolume = volume;
    fVisAttributeMap = visAttributes;
    SetVisAttributes( &fVolume );
}

void World::SetVisAttributes( Volume* volume )
{
    if( fVisAttributeMap.count( volume->GetName() ) == 0 )
        throw NoVisAttributesError( volume->GetName() );

    volume->SetVisAttributes( fVisAttributeMap[ volume->GetName() ] );

    for( int i = 0; i < volume->GetNoDaughters(); i++ )
        SetVisAttributes( volume->GetDaughter(i) );
}

void World::SetVisAttributeMap( std::map< std::string, VisAttributes* >& visAttributeMap )
{
    fVisAttributeMap = visAttributeMap;
    SetVisAttributes( &fVolume );
}

}; // namespace Viewer
