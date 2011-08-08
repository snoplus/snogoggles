////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::GenericTimer
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

#ifndef __Viewer_GUIs_GenericTimer__
#define __Viewer_GUIs_GenericTimer__

#include <Viewer/Timer.hh>
#include <Viewer/Sprite.hh>
#include <SFML/Graphics.hpp>
#include <string>

namespace Viewer
{  
namespace GUIs
{

class GenericTimer : public Timer
{
public:

  GenericTimer( const sf::Rect<double>& rect, unsigned int guiID );
  
  virtual ~GenericTimer() { }

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
