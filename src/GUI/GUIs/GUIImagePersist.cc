#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/GUIImagePersist.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIImagePersist::GUIImagePersist( const sf::Rect<double>& rect, unsigned int guiID )
  : Persist( rect, guiID )
{

}

void
GUIImagePersist::Initialise( EGUIImage image )
{
  GUIImageManager& imageManager = GUIImageManager::GetInstance();
  fPersist[0] = imageManager.NewSprite( image, eBase );
  fPersist[0].SetBoundingRect( fRect );
  fPersist[1] = imageManager.NewSprite( image, eHighlight );
  fPersist[1].SetBoundingRect( fRect );
  fPersist[2] = imageManager.NewSprite( image, eActive );
  fPersist[2].SetBoundingRect( fRect );
}

GUIImagePersist::~GUIImagePersist()
{
 
}

void 
GUIImagePersist::RenderT( sf::RenderWindow& windowApp )
{
  sf::Sprite newObject;
  if( !fPressed )
    newObject = sf::Sprite( fPersist[0] );
  else if( fHover )
    newObject = sf::Sprite( fPersist[1] );
  else
    newObject = sf::Sprite( fPersist[2] );
  
  newObject.SetPosition( fRect.Left, fRect.Top );
  newObject.Resize( fRect.Width, fRect.Height );
  windowApp.Draw( newObject );
}

void 
GUIImagePersist::Render( RWWrapper& windowApp )
{
  if( !fPressed && !fHover )
    windowApp.Draw( fPersist[0] );
  else if( fHover )
    windowApp.Draw( fPersist[1] );
  else
    windowApp.Draw( fPersist[2] );
}
