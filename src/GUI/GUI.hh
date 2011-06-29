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
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUI__
#define __Viewer_GUI__

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/UIEvent.hh>

namespace sf
{
  class RenderWindow;
  class Event;
}

namespace Viewer
{

class GUI
{
public:
  GUI( sf::Rect<double>& rect, unsigned int guiID );

  inline unsigned int GetGuiID();
  inline unsigned int GetGlobalID();
  inline void SetRect( sf::Rect<double>& rect );

  virtual void Render( sf::RenderWindow& windowApp ) = 0;
  virtual UIEvent NewEvent( sf::Event& event ) = 0;

protected:
  sf::Rect<double> fRect;
  unsigned int fID;
  unsigned int fGlobalID;
  static unsigned int fsNextID;
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
GUI::SetRect( sf::Rect<double>& rect )
{
  fRect = rect;
}

} // ::Viewer

#endif
