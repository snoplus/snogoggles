////////////////////////////////////////////////////////////////////////
/// \class Viewer::LineStrip
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     25/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_LineStrip__
#define __Viewer_LineStrip__

#include <Viewer/Vector3.hh>
#include <Viewer/Serializable.hh>
#include <vector>

namespace RAT {
    namespace DS {
        class MCTrack;
    };
};

namespace Viewer
{
    class ConfigurationTable;
    class VisAttributes;

class LineStrip : public Serializable
{
public:

    LineStrip() { }
    LineStrip( RAT::DS::MCTrack* tr );

    inline void AddVector3( const Vector3& vertex );
    inline const int GetNoVertices() const;
    inline const Vector3& GetVector3( const int i ) const;

    void RenderFull() const;
    void RenderSymbolic() const;

    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

    inline void SetVisAttributes( const VisAttributes* visAttributes );
    inline const VisAttributes* GetVisAttributes() const;

private:

    std::vector< Vector3 > fVertices;
    const VisAttributes* fVisAttributes;

}; // class LineStrip

////////////////////////////////////////////////////////////////////////
// inline methods
////////////////////////////////////////////////////////////////////////

void LineStrip::AddVector3( const Vector3& vertex ) 
{ 
    fVertices.push_back( vertex ); 
}

const int LineStrip::GetNoVertices() const 
{ 
    return fVertices.size(); 
}

const Vector3& LineStrip::GetVector3( const int i ) const 
{
    return fVertices.at(i); 
}

void LineStrip::SetVisAttributes( const VisAttributes* visAttributes )
{
    fVisAttributes = visAttributes;
}

const VisAttributes* LineStrip::GetVisAttributes() const
{
    return fVisAttributes;
}

} // ::Viewer

#endif // __Viewer_LineStrip
