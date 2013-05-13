////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::DesktopTab
///
/// \brief   DesktopTab GUI objects
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     13/05/13 : P.Jones - First Revision, new file. \n
///
/// \detail  DesktopTab persist button.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_DesktopTab__
#define __Viewer_GUIs_DesktopTab__

#include <Viewer/GUI.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
namespace GUIs
{

class DesktopTab : public GUI
{
public:
  inline DesktopTab( RectPtr rect, 
		     unsigned int guiID );
  ~DesktopTab();
  void Initialise();
  
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  inline void SetState( bool state );
  inline bool GetState() const;
protected:
  sf::Texture* fLeftOff[3]; /// < The left aspect textures in off state
  sf::Texture* fBaseOff[3]; /// < The base aspect textures in off state
  sf::Texture* fRightOff[3]; /// < The right aspect textures in off state
  sf::Texture* fLeftOn[3]; /// < The left aspect textures in on state
  sf::Texture* fBaseOn[3]; /// < The base aspect textures in on state
  sf::Texture* fRightOn[3]; /// < The right aspect textures in on state

  bool fOn; /// < Is persist on?
  bool fPressed; /// < Is button pressed?
  bool fHover; /// < Is button hovered?
};

DesktopTab::DesktopTab( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fOn = false;
  fPressed = false; 
  fHover = false;
}

void
DesktopTab::SetState( bool state )
{
  fOn = state;
}

bool
DesktopTab::GetState() const
{
  return fOn;
}

} // ::GUIs

} // ::Viewer

#endif
