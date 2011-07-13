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
///
/// \details Added in order not to make the ConfigurationTables messy.	
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_ConfigTableUtils__
#define __Viewer_ConfigTableUtils__

#include <Viewer/ConfigurationTable.hh>

#include <TVector3.h>
#include <string>

namespace Viewer {

class ConfigTableUtils {

public:

    /// Saves a TVector3 object to a config table as 3 doubles
    static void SetTVector3( ConfigurationTable* configTable, const std::string& name, const TVector3& v );

    /// Loads a TVector3 objects from a config table from 3 doubles
    static TVector3 GetTVector3( ConfigurationTable* configTable, const std::string& name );

    /// Saves a boolean to a config table as a string
    static void SetBoolean( ConfigurationTable* configTable, const std::string& name, bool value );

    /// Loads a boolean from a config table from a string
    static bool GetBoolean( ConfigurationTable* configTable, const std::string& name );

    // These methods catch the exception.
    static void GetISafe( ConfigurationTable* configTable, const std::string& name, int& value );
    static void GetDSafe( ConfigurationTable* configTable, const std::string& name, double& value );
    static void GetSSafe( ConfigurationTable* configTable, const std::string& name, std::string& value );

    static void GetBooleanSafe( ConfigurationTable* configTable, const std::string& name, bool& value );
    static void GetTVector3Safe( ConfigurationTable* configTable, const std::string& name, TVector3& value );

private:

    static const std::string TRUE_TAG;
    static const std::string FALSE_TAG;


}; // class ConfigTableUtils 

}; // namespace Viewer

#endif // __Viewer_ConfigTableUtils__
