////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::DefaultTracks3d
///
/// \brief   Responsible for filtering and rendering tracks.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	07/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_DefaultTracks3d__
#define __Viewer_Frames_DefaultTracks3d__

#include <Viewer/TrackManager3d.hh>
#include <Viewer/VisMap.hh>
#include <Viewer/LineStrip.hh>

#include <string>
#include <vector>
#include <map>

namespace RAT {
    namespace DS {
        class MC;
        class MCTrack;
    };
};

namespace Viewer {
    namespace GUIs {
        class CheckBoxLabel;
    };

    class ConfigurationTable;
    class GUIManager;

namespace Frames {

class DefaultTracks3d : public TrackManager3d {

public:

    DefaultTracks3d();

    virtual ~DefaultTracks3d() { }

    static std::string Name() { return "DefaultTracks"; }
    virtual std::string GetName() { return Name(); }

    virtual void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );
    virtual void LoadConfiguration( ConfigurationTable* configTable );
    virtual void SaveConfiguration( ConfigurationTable* configTable );
    virtual void EventLoop( );
    virtual void RenderTracks( RAT::DS::MC* mc );

private:

    bool FilterByPrimaryTrack( RAT::DS::MCTrack* tr );
    bool FilterByParticleType( RAT::DS::MCTrack* tr );

    void AddParticleType( const std::string& name, int eColour );

    bool fAllParticles;
    bool fPrimaryTracksOnly;
    bool fRenderFullTrack;
    bool fRefilter;

    static const std::string ALL_PARTICLES;
    static const std::string PRIMARY_TRACKS_ONLY;
    static const std::string RENDER_FULL_TRACK;
    static const std::string VIS_MAP;

    /// Map containing the supported particle types.
    VisMap fVisMap; 
    std::map< std::string, GUIs::CheckBoxLabel* > fGUIs;
    GUIs::CheckBoxLabel* fFullTrackGUI;

    RAT::DS::MC* fCurrentMC;
    std::vector< LineStrip > fLineStrips;

}; // class DefaultTracks3d

}; // namesapce Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_DefaultTracks3d__
