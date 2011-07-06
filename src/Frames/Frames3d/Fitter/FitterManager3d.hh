////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames3d::FitterManager3d
///
/// \brief   Abstract class which is responsible for interacting
///	     with various fitters.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	date : Olivia Wasalski - New File \n
///
/// \details 	The fitter manager is responsible for: \n
///
///		Interacting with the RAT fitters. \n
///		Displaying fit results (ex. fit vertex position) . \n
///		Creating GUI objects which allow fitter options to be processed. \n
///		Appropriately responding when passed Viewer::Events. \n
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames3d_FitterManager3d__
#define __Viewer_Frames3d_FitterManager3d__

#include <Viewer/Module3d.hh>

#include <string>

namespace Viewer {
namespace Frames3d {

class FitterManager3d : public Module3d {

public:

    virtual ~FitterManager3d() { }

    static std::string TableName() { return "FitterManager3d"; }
    std::string GetTableName() { return TableName(); }

    /// Renders the fit vertex.
    virtual void RenderFitVertex(  ) = 0;

    static inline void RenderFitVertexSafe( FitterManager3d* f )
    {
        if( f != NULL )
            f->RenderFitVertex();
    }

}; // class FitterManager3d

}; // namespace Frames3d 
}; // namespace Viewer

#endif // __Viewer_Frames3d_FitterManager3d__
