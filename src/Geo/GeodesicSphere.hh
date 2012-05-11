////////////////////////////////////////////////////////////////////////
/// \class Viewer::GeodesicSphere
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	06/08/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
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
