#include <Viewer/ConfigurationTable.hh>
#include <Viewer/SerializableFactory.hh>
#include <Viewer/StringUtils.hh>
#include <Viewer/VisMap.hh>

namespace Viewer {

void VisMap::Load( ConfigurationTable* configTable )
{
    std::map< std::string, VisAttributes > visAttributes;
    std::vector< std::string > names;
    StringUtils::SplitString( configTable->GetS( "names" ), " ", names );
    SerializableFactory* s = SerializableFactory::GetInstance();

    for( int i = 0; i < names.size(); i++ )
        visAttributes[ names.at(i) ] = s->New< VisAttributes >( configTable, names.at(i) );

    fVisAttributeMap = visAttributes;
}

void VisMap::Save( ConfigurationTable* configTable ) const
{
    std::string names = "";
    std::map< std::string, VisAttributes >::const_iterator itr;
    for( itr = fVisAttributeMap.begin(); itr != fVisAttributeMap.end(); itr++ )
    {
        names += itr->first;
        names += " ";
        itr->second.SaveToParentTable( configTable, itr->first );
    }
    configTable->SetS( "names", names );
}

const VisAttributes* VisMap::GetVisAttributes( const std::string& name ) const
{
    if( fVisAttributeMap.count( name ) == 0 )
        throw NoVisAttributesError( name );

    std::map< std::string, VisAttributes >::const_iterator itr;
    itr = fVisAttributeMap.find( name );
    return &( itr->second );
}

}; // namespace Viewer
