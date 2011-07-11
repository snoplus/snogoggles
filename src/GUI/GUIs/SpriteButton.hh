////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::SpriteButton
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

#ifndef __Viewer_GUIs_SpriteButton__
#define __Viewer_GUIs_SpriteButton__

#include <Viewer/GenericButton.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
#include <SFML/Graphics.hpp>
#include <string>

namespace Viewer
{  
namespace GUIs
{

class SpriteButton : public GenericButton
{
public:

    SpriteButton( sf::Rect<double>& rect, unsigned int guiID );

    virtual ~SpriteButton();

    void SetSprite( const std::string& filename );

    void RenderLabel( RWWrapper& windowApp );

protected:
    Sprite fSprite;

};


} // ::GUIs

} // ::Viewer

#endif
