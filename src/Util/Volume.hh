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
#include <Viewer/Colour.hh>
#include <Viewer/Polyhedron.hh>

namespace Viewer {

class Volume {

public:

    Volume() { }

    Volume(
        const std::string& name,
        bool visible,
        const Colour& colour,
        const Vector3& translation,
        const Vector3& rotationAxis,
        double rotationAngle,
        const std::vector< Volume* >& daughters,
        const Polyhedron& polyhedron
    )
    {
        fName = name;
        fVisible = visible;
        fColour = colour;
        fTranslation = translation;
        fRotationAxis = rotationAxis;
        fRotationAngle = rotationAngle;
        fDaughterVolumes = daughters;
        fPolyhedron = polyhedron;
    }

    virtual ~Volume() { }
    virtual std::string GetName() const { return fName; }
    virtual bool IsVisible() const { return fVisible; }
    virtual bool SetVisibility( bool visible ) { fVisible = visible; }
    virtual Colour GetColour() const { return fColour; }
    virtual Vector3 GetTranslation() const { return fTranslation; }
    virtual Vector3 GetRotationAxis() const { return fRotationAxis; }
    virtual double GetRotationAngle() const { return fRotationAngle; }
    virtual int GetNoDaughters() const { return fDaughterVolumes.size(); }
    virtual const Volume* GetDaughter( int n ) const { return fDaughterVolumes.at(n); }
    virtual const Polyhedron* GetPolyhedron() const { return &fPolyhedron; }
    virtual void Render();

    static std::string Tag() { return "volume"; }
    static const std::string NAME_TAG;
    static const std::string VISIBLE_TAG;
    static const std::string COLOUR_TAG;
    static const std::string TRANSLATION_TAG;
    static const std::string ROTATION_AXIS_TAG;
    static const std::string ROTATION_ANGLE_TAG;
    static const std::string POLYHEDRON_TAG;

private:

    std::string fName;
    bool fVisible;
    Colour fColour;
    Vector3 fTranslation;
    Vector3 fRotationAxis;
    double fRotationAngle;
    std::vector< Volume* > fDaughterVolumes;
    Polyhedron fPolyhedron;

}; // class Volume

}; // namespace Viewer

#endif // __Viewer_Volume__
