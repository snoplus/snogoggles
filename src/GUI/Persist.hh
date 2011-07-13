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

namespace Viewer
{
namespace GUIs
{

class Persist : public GUI
{
public:
  inline Persist( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~Persist() {};

  virtual void RenderT( sf::RenderWindow& windowApp ) = 0;
  virtual void Render( RWWrapper& windowApp ) = 0;
  virtual GUIReturn NewEvent( UIEvent& event );

  inline virtual bool GetState();
  inline virtual void SetState( bool state );
protected:
  bool fActive;
};

Persist::Persist( sf::Rect<double>& rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fActive = false; 
}

bool
Persist::GetState()
{
  return fActive;
}

void
Persist::SetState( bool state )
{
  fActive = state;
}

} // ::GUIs

} // ::Viewer

#endif
