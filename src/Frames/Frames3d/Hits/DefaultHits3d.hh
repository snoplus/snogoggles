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
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_DefaultHits3d__
#define __Viewer_Frames_DefaultHits3d__

#include <Viewer/HitManager3d.hh>

#include <string>

namespace RAT {
    namespace DS {
        class EV;
        class PMTProperties;
    };
};

namespace Viewer {

   class PMTWrapper; 

namespace Frames {

    class FrontChecker3d;

class DefaultHits3d : public HitManager3d {

public:

    DefaultHits3d();

    static std::string Name() { return "DefaultHits"; }
    std::string GetName() { return Name(); }

    /// Creates all the GUI objects.
    void CreateGUIObjects( GUIManager* g, const sf::Rect<double>& optionsArea );

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

    void FilterByType( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList );

    void FilterByPosition( const PMTWrapper& pmt, RAT::DS::PMTProperties* pmtList );

    void AssignColour( const PMTWrapper& pmt, RAT::DS::PMTProperties* pmtList );

    static inline std::string DisplayAllPMTsTag() { return "DisplayAllPMTs"; }
    static inline std::string PMTTypeTag() { return "PMTType"; }
    static inline std::string DisplayFrontPMTsOnlyTag() { return "DisplayFrontPMTsOnly"; }

    bool fDisplayAllPMTs;                   ///< Stores whether to render all (including unhit) PMTs.
    enum PMTType { UNCAL, CAL } fPMTType;   ///< Stores whether the PMTs are UnCal or Cal.
    bool fDisplayFrontPMTsOnly;             ///< Stores whether to only display front hits.


}; // class DefaultHits3d

}; // namespace Frames 
}; // namespace Viewer

#endif // Viewer_Frames_DefaultHits3d_hh
