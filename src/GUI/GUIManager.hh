////////////////////////////////////////////////////////////////////////
/// \class GUIManager
///
/// \brief   Manages the GUI objects in a frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     20/02/12 : P.Jones - Second Revision, refactor to use new rect.
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

#include <Viewer/GUIEvent.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class GUI;
  class Event;
  class RWWrapper;

class GUIManager
{
public:
  /// Construct the GUIManager, pass the parent frames rect
  inline GUIManager( RectPtr rect );
  ~GUIManager();
  /// Handle an event
  GUIEvent NewEvent( const Event& event );
  /// Render the GUI objects
  void Render( RWWrapper& windowApp );
  /// Make a GUI object under management, deleted by this class
  template<class T> inline
  T* NewGUI( const sf::Rect<double>& rect,
	     Rect::ECoordSystem system = Rect::eLocal );
  /// Return a GUI object given the local guiID
  GUI* GetGUI( unsigned int guiID );
  /// Delete all GUI objects
  void Clear();
  /// Delete a gui object by ID
  void DeleteGUI( unsigned int guiID );
  /// Change the rect to take account of a new mother
  inline void NewMother( RectPtr mother );
private:
  /// Find which GUI contains the point (resolution ALWAYS)
  int FindGUI( sf::Vector2<double> point );

  RectPtr fRect; /// < GUI Manager rect (should match the frames').
  std::vector<GUI*> fGUIObjects;
  int fFocus;
};

inline 
GUIManager::GUIManager( RectPtr rect )
  : fRect( rect )
{
  fFocus = -1;
}

template<class T>
T* 
GUIManager::NewGUI( const sf::Rect<double>& rect,
		    Rect::ECoordSystem system )
{
  RectPtr rectPtr( fRect->NewDaughter( rect, system ) );
  T* gui = new T( rectPtr, fGUIObjects.size() );
  fGUIObjects.push_back( gui );
  return gui;
}

inline void
GUIManager::NewMother( RectPtr mother )
{
  fRect = mother;
}

} // ::Viewer

#endif
