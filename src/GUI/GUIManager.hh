////////////////////////////////////////////////////////////////////////
/// \class GUIManager
///
/// \brief   Manages the GUI objects in a frame
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Frames should use this to manage GUI objects, unless explicity
///          requied to do something else.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIManager__
#define __Viewer_GUIManager__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

#include <Viewer/GUIReturn.hh>

namespace Viewer
{
  class GUI;
  class FrameCoord;
  class UIEvent;
  class RWWrapper;

class GUIManager
{
public:
  inline GUIManager();
  ~GUIManager();
  /// Handle an event
  GUIReturn NewEvent( UIEvent& event );
  /// Render the GUI objects
  void Render( RWWrapper& windowApp );
  /// Make a GUI object under management, deleted by this class
  template<class T> inline
  T* NewGUI( sf::Rect<double>& rect );
  /// Return a GUI object given the local guiID
  GUI* GetGUI( unsigned int guiID );
  /// Delete all GUI objects
  void Clear();
private:
  /// Find which GUI contains the localCoord point
  int FindGUI( sf::Vector2<double> localCoord );

  std::vector<GUI*> fGUIObjects;
  int fFocus;
};

GUIManager::GUIManager()
{
  fFocus = -1;
}

template<class T>
T* 
GUIManager::NewGUI( sf::Rect<double>& rect )
{
  T* gui = new T( rect, fGUIObjects.size() );
  fGUIObjects.push_back( gui );
  return gui;
}

} // ::Viewer

#endif
