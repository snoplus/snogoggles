#include <Viewer/GUI.hh>
using namespace Viewer;

unsigned int GUI::fsNextID = 0;

GUI::GUI( const sf::Rect<double>& rect, unsigned int guiID )
  : fRect( rect ), fID( guiID )
{
  fHidden = false;
  fGlobalID = fsNextID++;
}

bool 
GUI::ContainsPoint( const sf::Vector2<double>& localCoord )
{
  const double localX = localCoord.x - fRect.Left;
  const double localY = localCoord.y - fRect.Top;
  if( localX > 0 && localX < fRect.Width && localY > 0 && localY < fRect.Height )
    return true;
  else
    return false;
}
