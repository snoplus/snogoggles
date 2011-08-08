#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/GUIImageButton.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIImageButton::GUIImageButton( const sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{

}

void
GUIImageButton::Initialise( EGUIImage image )
{
  GUIImageManager& imageManager = GUIImageManager::GetInstance();
  fButton[0] = imageManager.NewSprite( image, eBase );
  fButton[0].SetBoundingRect( fRect );
  fButton[1] = imageManager.NewSprite( image, eHighlight );
  fButton[1].SetBoundingRect( fRect );
  fButton[2] = imageManager.NewSprite( image, eActive );
  fButton[2].SetBoundingRect( fRect );
}

GUIImageButton::~GUIImageButton()
{
 
}

void 
GUIImageButton::RenderT( sf::RenderWindow& windowApp )
{
  sf::Sprite newObject;
  if( !fPressed )
    newObject = sf::Sprite( fButton[0] );
  else if( fHover )
    newObject = sf::Sprite( fButton[1] );
  else
    newObject = sf::Sprite( fButton[2] );
  
  newObject.SetPosition( fRect.Left, fRect.Top );
  newObject.Resize( fRect.Width, fRect.Height );
  windowApp.Draw( newObject );
}

void 
GUIImageButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    windowApp.Draw( fButton[0] );
  else if( fHover )
    windowApp.Draw( fButton[1] );
  else
    windowApp.Draw( fButton[2] );
}
