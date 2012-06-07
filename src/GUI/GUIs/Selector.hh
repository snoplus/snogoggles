////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Selector
///
/// \brief   Select strings iteratively
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/06/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Allows user to select through a list of strings till the 
///          required one is found.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Selector__
#define __Viewer_GUIs_Selector__

#include <string>

#include <Viewer/GUI.hh>
#include <Viewer/Text.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{ 

namespace GUIs
{

class Selector : public GUI
{
public:
  /// Standard GUI Constructor
  Selector( RectPtr rect, unsigned int guiID );
  /// Desctuctor
  virtual ~Selector();
  /// Initialise with a vector of strings
  void Initialise( const std::vector<std::string>& options );
  /// New GUI Event
  GUIEvent NewEvent( const Event& event );
  /// On render call
  void Render( RWWrapper& windowApp );
  /// Set the current state by position is option list
  inline void SetState( unsigned int state );
  /// Get the current state by position
  inline unsigned int GetState() const;
  /// Get the current state by string value
  inline std::string GetStringState() const;
protected:
  GUIManager fGUIManager; /// < GUI Manager, manages the buttons
  std::vector<std::string> fOptions; /// < The string options
  Text fText; /// < Displays the current option
  unsigned int fState; /// < Current state position
  Sprite fBackground; /// < Draws background to text
};

void
Selector::SetState( unsigned int state )
{
  fState = state;
}

unsigned int
Selector::GetState() const
{
  return fState;
}

std::string
Selector::GetStringState() const
{
  return fOptions[fState];
}

} // ::GUIs

} // ::Viewer

#endif
