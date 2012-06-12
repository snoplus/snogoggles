////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Persist
///
/// \brief   Persist GUI objects
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     05/06/12 : P.Jones - Second Revision, No longer base class.\n
///
/// \detail  Persist (release to change state). Saves state.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Persist__
#define __Viewer_GUIs_Persist__

#include <Viewer/GUI.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
namespace GUIs
{

class Persist : public GUI
{
public:
  inline Persist( RectPtr rect, 
                 unsigned int guiID );
  ~Persist();
  void Initialise( unsigned int textureNumber );
  
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  inline void SetState( bool state );
  inline bool GetState() const;
protected:
  sf::Texture* fPersistOff[3]; /// < The button textures, base, highlight, active in off state
  sf::Texture* fPersistOn[3]; /// < The button textures, base, highlight, active in on state

  bool fOn; /// < Is persist on?
  bool fPressed; /// < Is button pressed?
  bool fHover; /// < Is button hovered?
};

Persist::Persist( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fOn = false;
  fPressed = false; 
  fHover = false;
}

void
Persist::SetState( bool state )
{
  fOn = state;
}

bool
Persist::GetState() const
{
  return fOn;
}

} // ::GUIs

} // ::Viewer

#endif
