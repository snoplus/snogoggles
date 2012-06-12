////////////////////////////////////////////////////////////////////////
/// \class Viewer::SerializableFactory
///
/// \brief   Facilitates creating serializable objects from config tables.
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     22/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_SerializableFactory__
#define __Viewer_SerializableFactory__

#include <string>

namespace Viewer
{
    class Configuration;
    class ConfigurationTable;

class SerializableFactory
{
public:
    template< typename T > inline T 
    New( const ConfigurationTable* configTable, const std::string& name );

    template< typename T > inline T* 
    NewPtr( const ConfigurationTable* configTable, const std::string& name );

    // Only called from XMLLoader3d.cc, should not be used.
    template< typename T > inline T* 
    NewPtrFromThisTable( const ConfigurationTable* configTable );

////////////////////////////////////////////////////////////////////////
// static section
////////////////////////////////////////////////////////////////////////
public:
    static SerializableFactory* GetInstance();
private:
    static SerializableFactory* fInstance;

}; // class SerializableFactory

////////////////////////////////////////////////////////////////////////
// inline methods
////////////////////////////////////////////////////////////////////////

template< typename T > inline T 
SerializableFactory::New( const ConfigurationTable* configTable, const std::string& name )
{
    T t;
    t.LoadFromParentTable( configTable, name );
    return t;
}

template< typename T > inline T* 
SerializableFactory::NewPtr( const ConfigurationTable* configTable, const std::string& name )
{
    T* t = new T();
    t->LoadFromParentTable( configTable, name );
    return t;
}

template< typename T > inline T* 
SerializableFactory::NewPtrFromThisTable( const ConfigurationTable* configTable )
{
    T* t = new T();
    t->Load( configTable );
    return t;
}


} // ::Viewer

#endif // __Viewer_SerializableFactory
