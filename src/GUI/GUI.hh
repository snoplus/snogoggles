////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUI
///
/// \brief   All GUI object derive from this
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail Base class for GUI objects, handles visibility and ID aspects.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUI__
#define __Viewer_GUI__

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/GUIReturn.hh>

namespace sf
{
  class RenderWindow;
}

namespace Viewer
{
  class FrameCoord;
  class UIEvent;
  class RWWrapper;

class GUI
{
public:
  /// Constructor, must pass GUI position rect and an ID
  GUI( const sf::Rect<double>& rect, unsigned int guiID );
  /// Get the unique GUI ID within the frame (not globally unique)
  inline unsigned int GetGuiID();
  /// Get the globally unique GUI ID
  inline unsigned int GetGlobalID();
  /// Set the position rect
  inline void SetRect( const sf::Rect<double>& rect );
  /// Set the GUI as hidden or not
  inline void SetHidden( bool hidden = true );
  /// Query if GUI is hidden
  inline bool Hidden();
  /// Check if local coord point lies within the GUI object
  bool ContainsPoint( const sf::Vector2<double>& localCoord );

  /// Pure virtual render call, global render window
  virtual void RenderT( sf::RenderWindow& windowApp ) = 0;
  /// Pure virtual render call, local render window
  virtual void Render( RWWrapper& windowApp ) = 0;
  /// Event handler
  virtual GUIReturn NewEvent( UIEvent& event ) = 0;  
protected:
  sf::Rect<double> fRect; /// < Position rect
  unsigned int fID;       /// < Local ID
  unsigned int fGlobalID; /// < Global ID
  bool fHidden;           /// < Is GUI hidden
private:
  static unsigned int fsNextID; /// < Global GUI counter
};

unsigned int 
GUI::GetGuiID()
{
  return fID;
}

unsigned int 
GUI::GetGlobalID()
{
  return fGlobalID;
}

void 
GUI::SetRect( const sf::Rect<double>& rect )
{
  fRect = rect;
}

void
GUI::SetHidden( bool hidden )
{
  fHidden = hidden;
}

bool
GUI::Hidden()
{
  return fHidden;
}

} // ::Viewer

#endif
