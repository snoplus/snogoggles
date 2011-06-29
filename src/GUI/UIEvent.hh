////////////////////////////////////////////////////////////////////////
/// \class UIEvent
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

#ifndef __Viewer_UIEvent__
#define __Viewer_UIEvent__

namespace Viewer
{
class UIEvent
{
public:
  inline UIEvent( unsigned int guiID, unsigned int globalID );
  unsigned int fguiID;
  unsigned int fGlobalID;
};

UIEvent::UIEvent( unsigned int guiID, unsigned int globalID )
  : fguiID( guiID ), fGlobalID( globalID )
{
  
}

} // ::Viewer

#endif
