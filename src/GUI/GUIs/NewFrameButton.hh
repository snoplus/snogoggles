////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::NewFrameButton
///
/// \brief   A Text option with left and right selectors
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     22/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  By selecting the left and right buttons the correct option 
///          can be chosen.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_NewFrameButton__
#define __Viewer_GUIs_NewFrameButton__

#include <string>

#include <Viewer/Button.hh>
#include <Viewer/RectPtr.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
  class Text;
  class Sprite;
namespace GUIs
{

class NewFrameButton : public Button
{
public:
  inline NewFrameButton( RectPtr rect, 
			 unsigned int guiID );
  virtual ~NewFrameButton();
 
  void Render( RWWrapper& renderApp );

  void Initialise( const std::string& frameName );

  inline std::string GetFrameName() const;

protected:
  std::string fFrameName; /// < The name of the frame this button creates
  Sprite* fLeftSprite;
  Sprite* fBarSprite;
  Sprite* fRightSprite;
  sf::Texture* fLeft[3]; /// < Left curve textures
  sf::Texture* fBar[3]; /// < Bar textures
  sf::Texture* fRight[3]; /// < Right curve textures
  Text* fText; /// < Text inbetween
};

inline
NewFrameButton::NewFrameButton( RectPtr rect, 
				unsigned int guiID ) 
  : Button( rect, guiID )
{ 

}

inline std::string
NewFrameButton::GetFrameName() const
{
  return fFrameName;
}

} // ::GUIs

} // ::Viewer

#endif
