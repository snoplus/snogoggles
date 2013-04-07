#include <Viewer/FrameOutline.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/GUITextureManager.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

FrameOutline::FrameOutline( RectPtr rect )
  : fRect( rect )
{

}

FrameOutline::~FrameOutline()
{
  delete fLeft, fBottom, fBottomLeft, fRight;
}

void 
FrameOutline::PreInitialise( const ConfigurationTable* )
{
  fLeft = new Sprite( RectPtr( fRect->NewDaughter() ) );
  fBottomLeft = new Sprite( RectPtr( fRect->NewDaughter() ) );
  fBottom = new Sprite( RectPtr( fRect->NewDaughter() ) );
  fRight = new Sprite( RectPtr( fRect->NewDaughter() ) );
  
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  fLeft->SetTexture( textureManager.GetTexture( 8, eBase ) );
  fBottomLeft->SetTexture( textureManager.GetTexture( 3, eBase ) );
  fBottom->SetTexture( textureManager.GetTexture( 9, eBase ) );
  fRight->SetTexture( textureManager.GetTexture( 10, eBase ) );
}

void 
FrameOutline::RenderGUI( RWWrapper& renderApp )
{
  renderApp.Draw( *fLeft );
  renderApp.Draw( *fBottomLeft );
  renderApp.Draw( *fBottom );
  renderApp.Draw( *fRight );
}

void
FrameOutline::SetRect( const sf::Rect<double>& rect )
{
  sf::Rect<double> size = rect;
  fRect->SetRect( size, Rect::eResolution );
  size.height -= 20.0;
  size.width = 20.0;
  fLeft->GetRect()->SetRect( size, Rect::eResolution );
  size.top = rect.top + rect.height - 20.0;
  size.height = 20.0;
  fBottomLeft->GetRect()->SetRect( size, Rect::eResolution );
  size.left += 20.0;
  size.width = rect.width - 40.0;
  fBottom->GetRect()->SetRect( size, Rect::eResolution );
  size = rect;
  size.left = size.left + size.width - 20.0;
  size.width = 20.0;
  size.height -= 20.0;
  fRight->GetRect()->SetRect( size, Rect::eResolution );
}
