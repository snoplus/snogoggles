////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Selector
///
/// \brief   A Text option with left and right selectors
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     22/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  By selecting the left and right buttons the correct option 
///          can be chosen.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Selector__
#define __Viewer_GUIs_Selector__

#include <vector>
#include <string>

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
  class Text;
namespace GUIs
{
  class GUIImageButton;

class Selector : public GUI
{
public:
  inline Selector( RectPtr rect, 
		   unsigned int guiID );
  virtual ~Selector();
 
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  void Initialise( const std::vector<std::string>& labels );
  void SetState( unsigned int state );
  /// Return the state as an unsigned int
  unsigned int GetState() const;

  inline std::string GetStringState() const;

protected:
  std::vector<std::string> fOptions; /// < The selectable options
  GUIs::GUIImageButton* fNext; /// < Right next option button
  GUIs::GUIImageButton* fPrev; /// < Left previous option button 
  Text* fText; /// < Text inbetween
  unsigned int fCurrentOption; // The current selected option
};

inline
Selector::Selector( RectPtr rect, 
		    unsigned int guiID ) 
  : GUI( rect, guiID )
{ 

}

inline std::string
Selector::GetStringState() const
{
  return fOptions[fCurrentOption];
}

} // ::GUIs

} // ::Viewer

#endif
