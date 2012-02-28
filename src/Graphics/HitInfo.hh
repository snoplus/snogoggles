////////////////////////////////////////////////////////////////////////
/// \class HitInfo
///
/// \brief   A string that displays the selected PMTs info
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     28/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Writes a string to the screen containing details about the
///          selected pmt.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_HitInfo__
#define __Viewer_HitInfo__

#include <string>

#include <Viewer/RectPtr.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
  class RWWrapper;
  class RenderState;

class HitInfo
{
public:
  /// Constructor, must pass a Rect
  inline HitInfo( RectPtr localRect,
		  bool horizontal );

  void Render( RWWrapper& renderApp,
	       const RenderState& renderState, 
	       const unsigned int pmtID );
protected:
  RectPtr fLocalRect; /// < The rect
  Text fInfoText; /// < The actual text
  bool fHorizontal; /// < Horizontal or vertical info
};

inline 
HitInfo::HitInfo( RectPtr localRect,
		  bool horizontal )
  : fLocalRect( localRect ), fInfoText( localRect ), fHorizontal( horizontal )
{

}

} // ::Viewer

#endif
