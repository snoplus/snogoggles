////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::FrameSelector
///
/// \brief   A set of check boxes with only one selectable at any time.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     21/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Multiple check boxes, only one can be selected at any time.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_FrameSelector__
#define __Viewer_GUIs_FrameSelector__

#include <vector>
#include <string>

#include <Viewer/GUI.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
namespace GUIs
{
  class NewFrameButton;

class FrameSelector : public GUI
{
public:
  FrameSelector( RectPtr rect, 
                 unsigned int guiID );
  virtual ~FrameSelector();
 
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  void Initialise( const std::vector<std::string>& labels );

  const std::string GetFrameName() const;

protected:
  GUIManager fGUIManager;
  std::vector< NewFrameButton* > fFrameButtons; /// < The new frame buttons reference
  unsigned int fLastClicked; /// < Last clicked 'selected' button, defaults to 0
};

} // ::GUIs

} // ::Viewer

#endif
