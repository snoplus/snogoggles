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

namespace Viewer {
	class Polyhedron;

class GeodesicSphere {
private:
	GeodesicSphere();
public:
	const Polyhedron& GetPolyhedron();
private:
	Polyhedron* fPolyhedron;

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
