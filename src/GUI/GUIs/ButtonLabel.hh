////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::ButtonLabel
///
/// \brief   ButtonLabel GUI objects
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/06/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Button object with a label.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_ButtonLabel__
#define __Viewer_GUIs_ButtonLabel__

#include <string>

#include <Viewer/Button.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
namespace GUIs
{

class ButtonLabel : public Button
{
public:
  inline ButtonLabel( RectPtr rect, 
                      unsigned int guiID );
  ~ButtonLabel() { };
  void Initialise( unsigned int textureNumber,
                   const std::string& label );
  
  void Render( RWWrapper& renderApp );
protected:
  Text fText;
};

ButtonLabel::ButtonLabel( RectPtr rect, unsigned int guiID ) 
  : Button( rect, guiID ), fText( rect )
{ 

}

} // ::GUIs

} // ::Viewer

#endif
