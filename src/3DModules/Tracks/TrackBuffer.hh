////////////////////////////////////////////////////////////////////////
/// \class TrackBuffer
///
/// \brief  Stores all of the VBOs containing relevent track information
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.com>
///                          <wasalski@berkely.edu>
///
/// REVISION HISTORY:\n
///     May 23, 2012 : O.Wasalski - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_TrackBuffer__
#define __Viewer_TrackBuffer__

#include <string>
#include <map>
#include <Viewer/VisAttributes.hh>
#include <Viewer/VBO.hh>

namespace Viewer {
    namespace RIDS {
        class Event;
    }; // namespace RIDS

    class ConfigurationTable;

class TrackBuffer {

public:
    struct ParticleType {
        bool fVisible;
        float fColour;
        VBO fAllStepsVBO;
        VBO fSimpleVBO;
    }; // struct ParticleType

    void AddParticleType( const std::string& name, float colour );
    std::vector< std::string > GetNames();
    void LoadVisibility( const ConfigurationTable* configTable );
    void SaveVisibility( ConfigurationTable* configTable );
    void SetAll( const RIDS::Event& event );
    void Render( bool renderAllSteps );

    std::map< std::string, struct ParticleType > fParticleTypes;

private:
    void ClearAll();
    void BindAll();
    void AddLine( VBO& vbo, const TVector3& startPos, const TVector3& endPos, const Colour& colour );
    
};

} // namespace Viewer

#endif
