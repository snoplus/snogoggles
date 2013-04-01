////////////////////////////////////////////////////////////////////////
/// \class EventSummary
///
/// \brief   A string that displays the events info
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     10/04/13 : P.Jones - First Revision, new file. \n
///
/// \detail  Writes a string to the screen with information about the
///          current event.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_EventSummary__
#define __Viewer_EventSummary__

#include <string>

#include <Viewer/RectPtr.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
  class RWWrapper;
  class RenderState;

class EventSummary
{
public:
  /// Constructor, must pass a Rect
  inline EventSummary( RectPtr localRect );

  void Render( RWWrapper& renderApp,
               const RenderState& renderState );
protected:
  RectPtr fLocalRect; /// < The rect
  Text fInfoText; /// < The actual text
};

inline 
EventSummary::EventSummary( RectPtr localRect )
  : fLocalRect( localRect ), fInfoText( localRect )
{

}

} // ::Viewer

#endif
