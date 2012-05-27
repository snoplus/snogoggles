////////////////////////////////////////////////////////////////////////
/// \class Viewer::TopBar
///
/// \brief   This class draws and controls the top bar of each frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     20/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This is a refactor of the original TopBar to use the new 
///          Rect stucture.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_TopBar__
#define __Viewer_TopBar__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <Viewer/RectPtr.hh>
#include <Viewer/GUITextureManager.hh>
#include <Viewer/FrameEvent.hh>

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class Event;
  class Text;
namespace GUIs
{
  class GUIImageButton;
  class GUIImagePersist;
}

class TopBar
{
public:
  TopBar( RectPtr rect );
  ~TopBar();
  /// Deal with a new UI event
  FrameEvent NewEvent( const Event& event );
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without a configuration
  void Initialise();
  /// Load a configuration
  void LoadConfiguration( const ConfigurationTable* configTable );
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp );
  /// Ask if object contains a point
  inline bool ContainsPoint( const sf::Vector2<double>& point );
  /// Set the top bar position
  void SetRect( const sf::Rect<double>& rect );
  /// Is the pin button active
  bool IsPinned();
private:
  RectPtr fRect; /// < The Top bar location
  GUIs::GUIImageButton* fLeft;
  GUIs::GUIImageButton* fBar;
  GUIs::GUIImageButton* fDecrease;
  GUIs::GUIImageButton* fIncrease;
  GUIs::GUIImageButton* fPin;
  GUIs::GUIImageButton* fClose;
  GUIs::GUIImageButton* fRight;
};

inline bool 
TopBar::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
