////////////////////////////////////////////////////////////////////////
/// \class Viewer::VisAttributes
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     20/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_VisAttributes__
#define __Viewer_VisAttributes__

#include <Viewer/Colour.hh>

namespace Viewer
{

class VisAttributes
{
public:

    VisAttributes( const Colour& colour, bool visible )
    {
        fColour = colour;
        fVisible = visible;
    }

    inline void SetColour( const Colour& colour ) { fColour = colour; }
    inline Colour GetColour() const { return fColour; }

    inline void SetVisibility( bool visible ) { fVisible = visible; }
    inline bool IsVisible() const { return fVisible; }

    inline void SetOpenGLColour() { fColour.SetOpenGL(); }

private:

    Colour fColour;
    bool fVisible;

}; // class VisAttributes

} // ::Viewer

#endif // __Viewer_VisAttributes
