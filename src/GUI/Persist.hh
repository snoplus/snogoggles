////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Persist
///
/// \brief   A Base class for persistent GUI objects
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Persist__
#define __Viewer_GUIs_Persist__

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
namespace GUIs
{

class Persist : public GUI
{
public:
  inline Persist( RectPtr rect, unsigned int guiID );
  virtual ~Persist() {};

  virtual void Render( RWWrapper& windowApp ) = 0;
  virtual GUIEvent NewEvent( Event& event );

  inline virtual bool GetState();
  inline virtual void SetState( bool state );
protected:
  bool fPressed;
  bool fHover;
};

Persist::Persist( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fPressed = false;
  fHover = false;
}

bool
Persist::GetState()
{
  return fPressed;
}

void
Persist::SetState( bool state )
{
  fPressed = state;
}

} // ::GUIs

} // ::Viewer

#endif
