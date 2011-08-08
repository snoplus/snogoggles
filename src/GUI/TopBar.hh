////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::TopBar
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_TopBar__
#define __Viewer_GUIs_TopBar__

#include <Viewer/Text.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/GUIImagePersist.hh>
#include <Viewer/FrameUIReturn.hh>

namespace Viewer
{  
  class ConfigurationTable;

class TopBar
{
public:
  TopBar();
  virtual ~TopBar();

  void LoadConfiguration( ConfigurationTable& configTable );
  void SaveConfiguration( ConfigurationTable& configTable );

  /// Set the position rect
  void SetRect( const sf::Rect<double>& rect );
  /// Check if resolution coord point lies within the GUI object
  bool ContainsPoint( const sf::Vector2<double>& resolutionCoord );

  /// Event handler
  FrameUIReturn NewEvent( UIEvent& event );
  void SetTitle( const std::string& title );
  void RenderT( sf::RenderWindow& windowApp );
  inline bool IsPinned();
protected:
  sf::Rect<double> fRect; /// < Position rect
  Text fTitle;
  GUIs::GUIImageButton fLeft;
  GUIs::GUIImageButton fBar;
  GUIs::GUIImageButton fDecrease;
  GUIs::GUIImageButton fIncrease;
  GUIs::GUIImagePersist fPin;
  GUIs::GUIImageButton fClose;
  GUIs::GUIImageButton fRight;  
};

bool
TopBar::IsPinned()
{
  return fPin.GetState();
}

} // ::Viewer

#endif
