////////////////////////////////////////////////////////////////////////
/// \class Viewer::ConfigTableUtils
///
/// \brief   Utility functions to save more complicated objects to
///          configuration tables.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	06/07/11 : Olivia Wasalski - New File \n
/// 	13/07/11 : Olivia Wasalski - Added methods for polyhedrons, polygons
///                and vector3s. \n
/// 	19/07/11 : Olivia Wasalski - Added methods for volumes. \n
///
/// \details Added in order not to make the ConfigurationTables messy.	
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_ConfigTableUtils__
#define __Viewer_ConfigTableUtils__

#include <Viewer/Vector3.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Colour.hh>
#include <string>

namespace Viewer {

class ConfigTableUtils {

public:

  static void SetBoolean( ConfigurationTable* configTable, 
                          const std::string& name, bool value );
  static bool GetBoolean( const ConfigurationTable* configTable, 
                          const std::string& name );
  
  template<typename T> static inline T
  GetEnum( const ConfigurationTable* configTable, const std::string& name );
  
  // These methods catch the exception.
  static void GetISafe( const ConfigurationTable* configTable, 
                        const std::string& name, int& value );
  static void GetDSafe( const ConfigurationTable* configTable, 
                        const std::string& name, double& value );
  static void GetSSafe( const ConfigurationTable* configTable, 
                        const std::string& name, std::string& value );
  
  static void GetBooleanSafe( const ConfigurationTable* configTable, 
                              const std::string& name, bool& value );
  template<typename T> static inline void GetEnumSafe( const ConfigurationTable* configTable, 
                                                       const std::string& name, T& value );

private:

    static const std::string TRUE_TAG;
    static const std::string FALSE_TAG;


}; // class ConfigTableUtils 

template<typename T> inline T 
ConfigTableUtils::GetEnum( const ConfigurationTable* configTable, const std::string& name )
{
    int temp = configTable->GetI( name );
    return static_cast< T >( temp );
}

template<typename T> inline void 
ConfigTableUtils::GetEnumSafe( const ConfigurationTable* configTable, const std::string& name, T& value )
{
    try{ value = GetEnum< T >( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

}; // namespace Viewer

#endif // __Viewer_ConfigTableUtils__
