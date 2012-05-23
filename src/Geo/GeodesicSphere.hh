////////////////////////////////////////////////////////////////////////
/// \class Viewer::GeodesicSphere
///
/// \brief   Singleton class which manages the 3D geodesic sphere.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	06/08/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	Loads from file, creates and stores the VBOs necessary
///             to render the 3D geodesic frame. Singleton class so 
///             that the data is only stored once in memory during the
///             process. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GeodesicSphere__
#define __Viewer_GeodesicSphere__

#include <Viewer/VBO.hh>

namespace Viewer {
	class Polyhedron;
	class Colour;

class GeodesicSphere {
private:
	GeodesicSphere();
	const Colour GetColour();
public:
	const Polyhedron& GetPolyhedron();
    void Render() const;
private:
	Polyhedron* fPolyhedron;
    VBO fOutlineVBO;
    VBO fFullVBO;

////////////////////////////////////////////////////////////////////////
// Static Section
////////////////////////////////////////////////////////////////////////
public:
	static GeodesicSphere* GetInstance();
private:
	static GeodesicSphere* fInstance;

}; // class GeodesicSphere

}; // namespace Viewer

#endif // __Viewer_GeodesicSphere__
