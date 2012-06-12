////////////////////////////////////////////////////////////////////////
/// \class Viewer::Serializable
///
/// \brief   Facilitates saving more complex objects to configuration tables.
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     22/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Serializable__
#define __Viewer_Serializable__

#include <string>

namespace Viewer
{
    class ConfigurationTable;

class Serializable
{
public:

    virtual void Load( const ConfigurationTable* configTable ) = 0;
    virtual void Save( ConfigurationTable* configTable ) const = 0;

    void LoadFromParentTable( const ConfigurationTable* parentTable, const std::string& name );
    void SaveToParentTable( ConfigurationTable* parentTable, const std::string& name ) const;

    void LoadSafeFromParentTable( const ConfigurationTable* parentTable, const std::string& name );

}; // class Serializable

} // ::Viewer

#endif // __Viewer_Serializable
