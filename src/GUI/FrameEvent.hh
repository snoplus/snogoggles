////////////////////////////////////////////////////////////////////////
/// \class FrameEvent
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameEvent__
#define __Viewer_FrameEvent__

namespace Viewer
{
class FrameEvent
{
public: 
  enum EventType { eNone, ePinned, eClosed, eStartMove, eStopMove };

  FrameEvent() : fType( eNone ) { }

  FrameEvent( EventType type ) : fType( type ) { }

  EventType fType;
};

} // ::Viewer

#endif
