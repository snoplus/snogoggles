////////////////////////////////////////////////////////////////////////
/// \class FrameUIReturn
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

#ifndef __Viewer_FrameUIReturn__
#define __Viewer_FrameUIReturn__

namespace Viewer
{
class FrameUIReturn
{
public: 
  enum EventType { eNone, ePinned, eClosed, eStartMove, eStopMove };

  FrameUIReturn() : fType( eNone ) { }

  FrameUIReturn( EventType type ) : fType( type ) { }

  EventType fType;
};

} // ::Viewer

#endif
