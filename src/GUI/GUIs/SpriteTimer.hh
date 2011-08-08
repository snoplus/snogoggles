////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::SpriteTimer
///
/// \brief   Generic button with a sprite
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

#ifndef __Viewer_GUIs_SpriteTimer__
#define __Viewer_GUIs_SpriteTimer__

#include <Viewer/GenericTimer.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
#include <SFML/Graphics.hpp>
#include <string>

namespace Viewer
{  
namespace GUIs
{

class SpriteTimer : public GenericTimer
{
public:

    SpriteTimer( const sf::Rect<double>& rect, unsigned int guiID );

    virtual ~SpriteTimer();

    void SetSprite( const std::string& filename );

    void RenderLabel( RWWrapper& windowApp );

protected:
    Sprite fSprite;

};


} // ::GUIs

} // ::Viewer

#endif
