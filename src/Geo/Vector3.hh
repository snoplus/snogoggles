////////////////////////////////////////////////////////////////////////
/// \class Viewer::Vector3
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     12/07/11 : Olivia Wasalski - First Revision, new file. \n
///     12/07/11 : Olivia Wasalski - Refactored, renamed, changed inheritance tree. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Vector3__
#define __Viewer_Vector3__

#include <Viewer/Serializable.hh>
class TVector3;

namespace Viewer
{
    class ConfigurationTable;

class Vector3 : public Serializable
{
public:

    Vector3( double x = 0.0, double y = 0.0, double z = 0.0 );
    Vector3( const TVector3& v );
    void SetXYZ( double x = 0.0, double y = 0.0, double z = 0.0 );
    void Render() const;
    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

    double x, y, z;

}; // class Vector3


} // ::Viewer

#endif // __Viewer_Vector3
