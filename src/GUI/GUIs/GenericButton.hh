////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::GenericButton
///
/// \brief   Generic button
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     11/07/11 : Olivia Wasalski - First Revision, New File. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_GenericButton__
#define __Viewer_GUIs_GenericButton__

#include <Viewer/Button.hh>
#include <Viewer/Sprite.hh>
#include <SFML/Graphics.hpp>
#include <string>

namespace Viewer
{  
namespace GUIs
{

class GenericButton : public Button
{
public:

  GenericButton( sf::Rect<double>& rect, unsigned int guiID );
  
  virtual ~GenericButton() { }

  void RenderT( sf::RenderWindow& windowApp ) { };
  void Render( RWWrapper& windowApp );
  
  virtual void RenderLabel( RWWrapper& windowApp ) { }

protected:

    Sprite fNormalButton;
    Sprite fExcitedButton;

};


} // ::GUIs

} // ::Viewer

#endif
