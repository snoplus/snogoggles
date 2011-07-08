////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::DefaultTracks3d
///
/// \brief   Responsible for filtering and rendering tracks.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
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
#include <Viewer/GUIReturn.hh>

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

    class ConfigurationTable;
    class GUIManager;

namespace Frames {

    class FrontChecker3d;

class Track {
public:
    Track( RAT::DS::MCTrack* tr, sf::Color* colour ) {
        fTrack = tr;
        fColour = colour;
    }
    RAT::DS::MCTrack* fTrack;
    sf::Color* fColour;
};

class ParticleType {
public:
    ParticleType() { }
    ParticleType( const std::string& name, const sf::Color& colour ) {
        fName = name;
        fDisplay = false;
        fColour = colour;
    }
    std::string fName;
    bool fDisplay;
    sf::Color fColour;
};

class DefaultTracks3d : public TrackManager3d {

public:

    DefaultTracks3d();

    virtual ~DefaultTracks3d() { }

    static std::string Name() { return "DefaultTracks"; }
    virtual std::string GetName() { return Name(); }

    /// Creates all the GUI objects for the module.
    virtual void CreateGUIObjects( GUIManager* g, const sf::Rect<double>& optionsArea );

    /// Loads configuration
    virtual void LoadConfiguration( ConfigurationTable* configTable );

    /// Saves configuration
    virtual void SaveConfiguration( ConfigurationTable* configTable );

    /// Event loop for the camera manager.
    virtual void EventLoop( const GUIReturn& g );

    /// Renders tracks.
    virtual void RenderTracks( RAT::DS::MC* mc );


private:

    void FilterTracks( RAT::DS::MC* mc );

    void FilterByPrimaryTrack( RAT::DS::MCTrack* tr );

    void FilterByParticleType( RAT::DS::MCTrack* tr );

    inline void AddToFilteredTracks( const Track& tr ) { fFilteredTracks.push_back( tr ); }

    inline void AddParticleType( const std::string& name, const sf::Color& colour )
    { fParticleTypes[ name ] = ParticleType( name, colour ); }

    inline void RenderFullTrack( Track& track ) { }

    inline void RenderSymbolicTrack( Track& track ) { }

    static std::string AllParticlesTag() { return "AllParticles"; }
    bool fAllParticles;
    static std::string RenderFullTrackTag() { return "RenderFullTrack"; }
    bool fRenderFullTrack;

    static sf::Color fUnkownParticleColour;             ///< Colour of an unknown particle.

    RAT::DS::MC* fCurrentMC;                            ///< Pointer to the current MC.
    std::map<std::string, ParticleType> fParticleTypes; ///< Map containing the supported particle types.
    std::vector<Track> fFilteredTracks;                 ///< Vector containing the tracks flagged for rendering.
    bool fReFilter;                                     ///< Whether to refilter the tracks.


}; // class DefaultTracks3d

}; // namesapce Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_DefaultTracks3d__
