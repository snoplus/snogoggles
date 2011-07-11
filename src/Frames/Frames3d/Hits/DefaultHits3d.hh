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
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_DefaultHits3d__
#define __Viewer_Frames_DefaultHits3d__

#include <Viewer/HitManager3d.hh>
#include <Viewer/GUIReturn.hh>
#include <TVector3.h>

#include <string>
#include <vector>

namespace RAT {
    namespace DS {
        class EV;
        class PMTProperties;
        class PMTUnCal;
        class PMTCal;
    };
};

namespace Viewer {

    class ConfigurationTable;
    class GUIManager;

namespace Frames {

    class FrontChecker3d;

class DefaultHits3d : public HitManager3d {

public:

    DefaultHits3d();

    static std::string Name() { return "DefaultHits"; }
    std::string GetName() { return Name(); }

    /// Creates all the GUI objects.
    void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );

    /// Loads configuration
    void LoadConfiguration( ConfigurationTable* configTable );

    /// Saves configuration
    void SaveConfiguration( ConfigurationTable* configTable );

    /// Event loop for the camera manager.
    void EventLoop( const GUIReturn& g );

    /// Renders hits.
    void RenderHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );

private:

    void DisplayAllPMTs( RAT::DS::PMTProperties* pmtList );

    void RenderUnCalHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );

    void RenderCalHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );

    void SetColour( RAT::DS::PMTUnCal* pmt );

    void SetColour( RAT::DS::PMTCal* pmt );

    void RenderHit( RAT::DS::PMTUnCal* pmt, RAT::DS::PMTProperties* pmtList );

    void RenderHit( RAT::DS::PMTCal* pmt, RAT::DS::PMTProperties* pmtList );

    void RenderFrontSolidHitOnly( const TVector3& pos );

    void RenderFrontHollowHitOnly( const TVector3& pos );

    void RenderSolidOrHollowHit( const TVector3& pos );

    static const std::string fDisplayAllPMTsTag;
    static const std::string fPMTTypeTag;
    static const std::string fDisplayFrontPMTsOnlyTag;

    bool fDisplayAllPMTs;                   ///< Stores whether to render all (including unhit) PMTs.
    enum PMTType { UNCAL, CAL } fPMTType;   ///< Stores whether the PMTs are UnCal or Cal.
    bool fDisplayFrontPMTsOnly;             ///< Stores whether to only display front hits.



}; // class DefaultHits3d

}; // namespace Frames 
}; // namespace Viewer

#endif // Viewer_Frames_DefaultHits3d_hh
