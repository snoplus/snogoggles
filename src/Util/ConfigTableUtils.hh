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

private:

    static inline std::string TrueTag() { return "TRUE"; }
    static inline std::string FalseTag() { return "FALSE"; }


}; // class ConfigTableUtils 

}; // namespace Viewer

#endif // __Viewer_ConfigTableUtils__
