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
#include <Viewer/Hit.hh>
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
    namespace GUIs {
        class CheckBoxLabel;
    };

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
    void RenderHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );

private:

    void SaveAllPMTs( RAT::DS::PMTProperties* pmtList );
    void FilterHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );

    void FilterPMTCal( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );
    void FilterPMTUnCal( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );

    Colour AssignColour( RAT::DS::PMTUnCal* pmt );
    Colour AssignColour( RAT::DS::PMTCal* pmt );

    bool PassesFilters( const TVector3& pos );
    bool FilterByFront( const TVector3& pos );

    void DisplayHits( const std::vector< Hit >& hits, bool forceHollow );

    RAT::DS::EV* fCurrentEV;
    RAT::DS::PMTProperties* fCurrentPMTList;

    std::vector< Hit > fFilteredHits;
    std::vector< Hit > fAllPMTs;

    static const std::string fDisplayAllPMTsTag;
    static const std::string fPMTTypeTag;
    static const std::string fDisplayFrontPMTsOnlyTag;

    enum PMTType { UNCAL, CAL } fPMTType;   ///< Stores whether the PMTs are UnCal or Cal.
    bool fDisplayAllPMTs;
    bool fDisplayFrontPMTsOnly;

    GUIs::CheckBoxLabel* fAllPMTsGUI;
    GUIs::CheckBoxLabel* fFrontGUI;

}; // class DefaultHits3d

}; // namespace Frames 
}; // namespace Viewer

#endif // Viewer_Frames_DefaultHits3d_hh
