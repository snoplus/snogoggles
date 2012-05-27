#include <Viewer/World.hh>
#include <Viewer/SerializableFactory.hh>

namespace Viewer {

World::World( Volume& volume )
{
    fVolume = volume;
//    SetVisMap( visAttributes );
}

void World::SetVisAttributes( Volume* volume )
{
/*    volume->SetVisAttributes( fVisMap.GetVisAttributes( volume->GetName() ) );

    for( int i = 0; i < volume->GetNoDaughters(); i++ )
        SetVisAttributes( volume->GetDaughter(i) );*/
}

/*void World::SetVisMap( VisMap& visAttributeMap )
{
//    fVisMap = visAttributeMap;
//    SetVisAttributes( &fVolume );
}*/

void World::Load( ConfigurationTable* configTable )
{
    SerializableFactory* s = SerializableFactory::GetInstance();
    Volume volume = s->New< Volume >( configTable, "volume" );
//    VisMap visMap = s->New< VisMap >( configTable, "visAttributes" );

    fVolume = volume;
//    SetVisMap( visMap );
}

void World::Save( ConfigurationTable* configTable ) const
{
    fVolume.SaveToParentTable( configTable, "volume" );
//    fVisMap.SaveToParentTable( configTable, "visAttributes" );
}

}; // namespace Viewer
