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

#include <Viewer/Volume.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Colour.hh>
#include <string>

namespace Viewer {

class ConfigTableUtils {

public:

    static void SetBoolean( ConfigurationTable* configTable, 
        const std::string& name, bool value );
    static bool GetBoolean( ConfigurationTable* configTable, 
        const std::string& name );

    static void SetColour( ConfigurationTable* configTable, 
        const std::string& name, Colour value );
    static Colour GetColour( ConfigurationTable* configTable, 
        const std::string& name );

    static void SetVector3( ConfigurationTable* configTable, 
        const std::string& name, const Vector3& value );
    static Vector3 GetVector3( ConfigurationTable* configTable, 
        const std::string& name );

    // These methods catch the exception.
    static void GetISafe( ConfigurationTable* configTable, 
        const std::string& name, int& value );
    static void GetDSafe( ConfigurationTable* configTable, 
        const std::string& name, double& value );
    static void GetSSafe( ConfigurationTable* configTable, 
        const std::string& name, std::string& value );

    static void GetBooleanSafe( ConfigurationTable* configTable, 
        const std::string& name, bool& value );
    static void GetVector3Safe( ConfigurationTable* configTable, 
        const std::string& name, Vector3& value );

private:

    static const std::string TRUE_TAG;
    static const std::string FALSE_TAG;

    static const std::string VECTOR3_X;
    static const std::string VECTOR3_Y;
    static const std::string VECTOR3_Z;

    static const std::string COLOUR_R;
    static const std::string COLOUR_G;
    static const std::string COLOUR_B;
    static const std::string COLOUR_A;


}; // class ConfigTableUtils 

}; // namespace Viewer

#endif // __Viewer_ConfigTableUtils__
