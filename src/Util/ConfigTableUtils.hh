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
///
/// \details Added in order not to make the ConfigurationTables messy.	
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_ConfigTableUtils__
#define __Viewer_ConfigTableUtils__

#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Vector3.hh>
#include <Viewer/Polygon.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Colour.hh>
#include <TVector3.h>
#include <string>

namespace Viewer {

class ConfigTableUtils {

public:

    static void SetTVector3( ConfigurationTable* configTable, const std::string& name, const TVector3& v );
    static TVector3 GetTVector3( ConfigurationTable* configTable, const std::string& name );

    static void SetBoolean( ConfigurationTable* configTable, const std::string& name, bool value );
    static bool GetBoolean( ConfigurationTable* configTable, const std::string& name );

    static void SetColour( ConfigurationTable* configTable, const std::string& name, Colour value );
    static Colour GetColour( ConfigurationTable* configTable, const std::string& name );

    static void SetPolyhedron( ConfigurationTable* configTable, const Polyhedron& value );
    static Polyhedron GetPolyhedron( ConfigurationTable* configTable );

    static void SetPolygon( ConfigurationTable* configTable, const std::string& name, const Polygon& value );
    static Polygon GetPolygon( ConfigurationTable* configTable, const std::string& name );

    static void SetVector3( ConfigurationTable* configTable, const std::string& name, const Vector3& value );
    static Vector3 GetVector3( ConfigurationTable* configTable, const std::string& name );

    // These methods catch the exception.
    static void GetISafe( ConfigurationTable* configTable, const std::string& name, int& value );
    static void GetDSafe( ConfigurationTable* configTable, const std::string& name, double& value );
    static void GetSSafe( ConfigurationTable* configTable, const std::string& name, std::string& value );

    static void GetBooleanSafe( ConfigurationTable* configTable, const std::string& name, bool& value );
    static void GetTVector3Safe( ConfigurationTable* configTable, const std::string& name, TVector3& value );
    static void GetVector3Safe( ConfigurationTable* configTable, const std::string& name, Vector3& value );

private:

    static const std::string TRUE_TAG;
    static const std::string FALSE_TAG;


}; // class ConfigTableUtils 

}; // namespace Viewer

#endif // __Viewer_ConfigTableUtils__
