#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Serializable.hh>

namespace Viewer {

void Serializable::LoadFromParentTable( ConfigurationTable* parentTable, const std::string& name )
{
    ConfigurationTable* table = parentTable->GetTable( name );
    Load( table );
}

void Serializable::SaveToParentTable( ConfigurationTable* parentTable, const std::string& name ) const
{
    ConfigurationTable* table = parentTable->NewTable( name );
    Save( table );
}

void Serializable::LoadSafeFromParentTable( ConfigurationTable* parentTable, const std::string& name )
{
    try { LoadFromParentTable( parentTable, name ); }
    catch( ConfigurationTable::NoTableError& e ) { }
}

}; // namespace Viewer
