////////////////////////////////////////////////////////////////////////
/// \class Viewer::VisMap
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     22/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::VisMap::NoVisAttributesError
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     20/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_VisMap__
#define __Viewer_VisMap__

#include <map>
#include <string>
#include <stdexcept>

#include <Viewer/Serializable.hh>
#include <Viewer/VisAttributes.hh>

namespace Viewer
{
    class ConfigurationTable;

class VisMap : public Serializable
{
public:
    class NoVisAttributesError : public std::runtime_error
    {
        public:
            NoVisAttributesError( const std::string& param ) 
                : std::runtime_error( param ) {}
    }; 

    VisMap( ) { }

    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

    void LoadVisibility( ConfigurationTable* configTable );
    void LoadVisibilitySafe( ConfigurationTable* configTable );
    void SaveVisibility( ConfigurationTable* configTable ) const;

    const VisAttributes* GetVisAttributes( const std::string& name ) const;
    inline void AddVisAttributes( const std::string& name, const VisAttributes& visAttributes );

    void SetOpenGLColour( const std::string& name ) const;
    bool IsVisible( const std::string& name ) const;

    inline const int Count( const std::string& name ) const;
    inline const bool IsEmpty() const;

private:

    inline void CheckValidity( const std::string& name ) const;
    std::map< std::string, VisAttributes > fVisAttributeMap;

}; // class VisMap

////////////////////////////////////////////////////////////////////////
// inline methods
////////////////////////////////////////////////////////////////////////

void VisMap::AddVisAttributes( const std::string& name, const VisAttributes& visAttributes )
{
    fVisAttributeMap[ name ] = visAttributes;
}

const bool VisMap::IsEmpty() const
{
    return fVisAttributeMap.empty();
}

const int VisMap::Count( const std::string& name ) const
{
    return fVisAttributeMap.count( name );
}

void VisMap::CheckValidity( const std::string& name ) const
{
    if( fVisAttributeMap.count( name ) == 0 )
        throw NoVisAttributesError( name );
}

} // ::Viewer

#endif // __Viewer_VisMap
