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
///     05/21/12 : Olivia Wasalski - Removed functionality, RIDS does not support yet. \n
///     May 23, 2012 : O.Wasalski - Renders tracks through VBO and RIDS structure. \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_DefaultTracks3d__
#define __Viewer_Frames_DefaultTracks3d__

#include <Viewer/TrackManager3d.hh>
#include <Viewer/TrackBuffer.hh>

#include <string>
#include <vector>
#include <map>

namespace Viewer {
    namespace GUIs {
        class CheckBoxLabel;
    };

    class ConfigurationTable;
    class GUIManager;
    class ColourPalette;

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
    virtual void RenderTracks( RIDS::MC& mc );

private:

    void AddParticleType( const std::string& name, float eColour );

    bool fAllParticles;
    bool fPrimaryTracksOnly;
    bool fRenderFullTrack;

    static const std::string ALL_PARTICLES;
    static const std::string PRIMARY_TRACKS_ONLY;
    static const std::string RENDER_FULL_TRACK;
    static const std::string VIS_MAP;

    /// Map containing the supported particle types.
    std::map< std::string, GUIs::CheckBoxLabel* > fGUIs;
    GUIs::CheckBoxLabel* fFullTrackGUI;

    TrackBuffer fTrackBuffer;
    int fSize;
    ColourPalette* fPreviousPalette;

}; // class DefaultTracks3d

}; // namesapce Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_DefaultTracks3d__
