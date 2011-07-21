////////////////////////////////////////////////////////////////////////
/// \class Viewer::GeoTranslator
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	20/07/11 : Olivia Wasalski - New File \n
///
/// \details 
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_GeoTranslator__
#define __Viewer_GeoTranslator__

#include <Viewer/Polygon.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Volume.hh>

#include <map>

namespace Viewer {

    class ConfigurationTable;
    class World;
    class VisAttributes;

class GeoTranslator {

public:

    static void SetWorld( ConfigurationTable* configTable, World* value );
    static World* GetWorld( ConfigurationTable* configTable );

    static void SetVisAttributeMap( ConfigurationTable* configTable, 
        const std::string& name, std::map< std::string, VisAttributes* >& value );
    static std::map< std::string, VisAttributes* > GetVisAttributeMap( 
        ConfigurationTable* configTable, const std::string& name );

    static void SetVisAttributes( ConfigurationTable* configTable, 
        const std::string& name, const VisAttributes* value );
    static VisAttributes* GetVisAttributes( ConfigurationTable* configTable, 
        const std::string& name );

    static void SetVolume( ConfigurationTable* configTable, 
        const std::string& name, Volume& value );
    static Volume GetVolume( ConfigurationTable* configTable,
        const std::string& name );

    static void SetPolyhedron( ConfigurationTable* configTable, 
        const std::string& name, const Polyhedron& value );
    static Polyhedron GetPolyhedron( ConfigurationTable* configTable, 
        const std::string& name );

    static void SetPolygon( ConfigurationTable* configTable, 
        const std::string& name, const Polygon& value );
    static Polygon GetPolygon( ConfigurationTable* configTable, 
        const std::string& name );

private:

    static const std::string VOLUME;
    static const std::string VOLUME_NAME;
    static const std::string VOLUME_TRANSLATION;
    static const std::string VOLUME_ROTATION_AXIS;
    static const std::string VOLUME_ROTATION_ANGLE;

    static const std::string POLYHEDRON;
    static const std::string POLYGON;
    static const std::string VERTEX;

    static const std::string VIS_ATTRIBUTES;
    static const std::string VIS_ATTRIBUTES_NAMES;
    static const std::string VIS_ATTRIBUTES_COLOUR;
    static const std::string VIS_ATTRIBUTES_VISIBLE;


}; // class GeoTranslator 

}; // namespace Viewer

#endif // __Viewer_GeoTranslator__
