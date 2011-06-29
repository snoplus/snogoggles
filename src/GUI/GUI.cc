#include <Viewer/GUI.hh>
using namespace Viewer;

unsigned int GUI::fsNextID = 0;

GUI::GUI( sf::Rect<double>& rect, unsigned int guiID )
  : fRect( rect ), fID( guiID )
{
  fGlobalID = fsNextID++;
}
