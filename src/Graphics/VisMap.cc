#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
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

void VisMap::LoadVisibilitySafe( ConfigurationTable* configTable )
{
    try { LoadVisibility( configTable ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void VisMap::LoadVisibility( ConfigurationTable* configTable )
{
    std::map< std::string, VisAttributes >::iterator itr;
    for( itr = fVisAttributeMap.begin(); itr != fVisAttributeMap.end(); itr++ )
        itr->second.SetVisibility( ConfigTableUtils::GetBoolean( configTable, itr->first ) );
}

void VisMap::SaveVisibility( ConfigurationTable* configTable ) const
{
    std::map< std::string, VisAttributes >::const_iterator itr;
    for( itr = fVisAttributeMap.begin(); itr != fVisAttributeMap.end(); itr++ )
        ConfigTableUtils::SetBoolean( configTable, itr->first, itr->second.IsVisible() );
}

const VisAttributes* VisMap::GetVisAttributes( const std::string& name ) const
{
    CheckValidity( name );
    std::map< std::string, VisAttributes >::const_iterator itr;
    itr = fVisAttributeMap.find( name );
    return &( itr->second );
}

void VisMap::SetOpenGLColour( const std::string& name ) const
{
    CheckValidity( name );
    std::map< std::string, VisAttributes >::const_iterator itr;
    itr = fVisAttributeMap.find( name );
    itr->second.SetOpenGLColour();
}

bool VisMap::IsVisible( const std::string& name ) const
{
    CheckValidity( name );
    std::map< std::string, VisAttributes >::const_iterator itr;
    itr = fVisAttributeMap.find( name );
    return itr->second.IsVisible();
}

int VisMap::GetNoEntries() const 
{
    int entries = 0;
    std::map< std::string, VisAttributes >::const_iterator itr;
    for( itr = fVisAttributeMap.begin(); itr != fVisAttributeMap.end(); itr++ )
        entries++;
    return entries;
}

std::vector< std::string > VisMap::GetNames() const 
{
    std::vector< std::string > names;
    std::map< std::string, VisAttributes >::const_iterator itr;
    for( itr = fVisAttributeMap.begin(); itr != fVisAttributeMap.end(); itr++ )
        names.push_back( itr->first );
    return names;
}

}; // namespace Viewer
