////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::DefaultHits3d
///
/// \brief   Responsible for filtering and rendering hits.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	06/07/11 : Olivia Wasalski - New File \n
/// 	06/07/11 : Olivia Wasalski - Refactored so that hits are only
///                                  filtered when needed. \n
///     11/07/11 : Olivia Wasalski - Undid last revision. Hits are now displayed. \n
///     xx/xx/xx : Olivia Wasalski - Basically rewritten to use VBOs \n
///     05/21/12 : Olivia Wasalski - Removed dependence on global sphere; 
///                                  was the source of lag. \n
///
/// \details    Implements functionality specified by the hit manager class.
///             Filters hits if either the render state or the current EV 
///             changes. Stores each hit 2 ways, as a full hexagon and an
///             outline of a hexagon in 2 seperate VBOs. The full hexagon hits
///             are rendered with the depth buffer enabled, and the outline 
///             hits are rendered with the depth buffer disabled to create
///             the effect that the hits in the back are outlines. Also has 
///             a mode where it all of the PMT array. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_DefaultHits3d__
#define __Viewer_Frames_DefaultHits3d__

#include <Viewer/HitManager3d.hh>
#include <Viewer/HitBuffer.hh>
#include <Viewer/RenderState.hh>
#include <TVector3.h>

#include <string>
#include <vector>

namespace RAT {
    namespace DS {
        class PMTProperties;
    };
};

namespace Viewer {
    namespace GUIs {
        class CheckBoxLabel;
    };

    namespace RIDS {
        class EV;
        class PMTHit;
    };

    class ColourPalette;
    class RenderState;
    class ConfigurationTable;
    class GUIManager;

namespace Frames {

class DefaultHits3d : public HitManager3d {
public:

    DefaultHits3d();

    static std::string Name() { return "DefaultHits"; }
    std::string GetName() { return Name(); }
    void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );
    void LoadConfiguration( ConfigurationTable* configTable );
    void SaveConfiguration( ConfigurationTable* configTable );
    void EventLoop( );
    void RenderHits( RIDS::EV* ev, RAT::DS::PMTProperties* pmtList, const RenderState& renderState );

private:

    bool NeedToRecreateVBOs( RIDS::EV* ev, const RenderState& renderState );
    void SaveHitsToBuffer( RIDS::EV* ev, RAT::DS::PMTProperties* pmtList, const RenderState& renderState );
    bool Equals( const RenderState& a, const RenderState& b );

    RAT::DS::PMTProperties* fCurrentPMTList;
    RIDS::EV* fCurrentEV;
    RenderState fCurrentRenderState;
    ColourPalette* fCurrentPalette;

    HitBuffer fPMTListBuffer;
    HitBuffer fFullBuffer;
    HitBuffer fOutlineBuffer;

    static const std::string fDisplayAllPMTsTag;
    static const std::string fPMTTypeTag;
    static const std::string fDisplayFrontPMTsOnlyTag;

    bool fDisplayAllPMTs;
    bool fDisplayFrontPMTsOnly;

    GUIs::CheckBoxLabel* fAllPMTsGUI;
    GUIs::CheckBoxLabel* fFrontGUI;

}; // class DefaultHits3d

}; // namespace Frames 
}; // namespace Viewer

#endif // Viewer_Frames_DefaultHits3d_hh
