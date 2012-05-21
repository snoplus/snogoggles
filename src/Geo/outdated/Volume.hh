////////////////////////////////////////////////////////////////////////
/// \class Viewer::Volume
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	19/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Volume__
#define __Viewer_Volume__

#include <string>
#include <iostream>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Serializable.hh>
#include <Viewer/Vector3.hh>

namespace Viewer {

    class VisAttributes;
    class ConfigurationTable;

class Volume : public Serializable {

public:

    Volume() { }

    Volume(
        const std::string& name,
        const Vector3& translation,
        const Vector3& rotationAxis,
        double rotationAngle,
        const Polyhedron& polyhedron
    );

    virtual ~Volume() { }
    virtual const std::string GetName() const { return fName; }
    virtual const Vector3 GetTranslation() const { return fTranslation; }
    virtual const Vector3 GetRotationAxis() const { return fRotationAxis; }
    virtual const double GetRotationAngle() const { return fRotationAngle; }
    virtual const Polyhedron& GetPolyhedron() const { return fPolyhedron; }
    virtual void Render() const;

    virtual void AddDaughter( Volume& volume ) { fDaughterVolumes.push_back( volume ); }
    virtual const int GetNoDaughters() const { return fDaughterVolumes.size(); }
    virtual Volume* GetDaughter( int n ) { return &fDaughterVolumes.at(n); }

    virtual void SetVisAttributes( const VisAttributes* visAttributes )
    { fVisAttributes = visAttributes; }
    virtual const VisAttributes* GetVisAttributes()
    { return fVisAttributes; }

    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

private:

    void SetAll(
        const std::string& name,
        const Vector3& translation,
        const Vector3& rotationAxis,
        double rotationAngle,
        const Polyhedron& polyhedron
    );

    std::string fName;
    Vector3 fTranslation;
    Vector3 fRotationAxis;
    double fRotationAngle;
    std::vector< Volume > fDaughterVolumes;
    Polyhedron fPolyhedron;

    const VisAttributes* fVisAttributes;

}; // class Volume

}; // namespace Viewer

#endif // __Viewer_Volume__
