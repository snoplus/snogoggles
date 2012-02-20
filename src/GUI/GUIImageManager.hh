////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUITextureManager
///
/// \brief   Colours the GUI base image to produce the required images.
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail  The GUI base image defines the GUI shape, the colours are
///          decided at run time by this class. This is a singleton class.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUITextureManager__
#define __Viewer_GUITextureManager__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Config.hpp>

#include <map>

#include <Viewer/Sprite.hh>
#include <Viewer/GUIColourPalette.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
  enum EGUITexture { eBarLeft, eBar, eBarRight, eDecrease, eIncrease, ePlus, eCross, eOpenBox, eCrossBox, eNewFrameLeft, eNewFrame, eNewFrameRight };
  typedef std::map< EGUITexture, std::map< EGUITextureState, sf::Texture* > > GUITextureMap;

class GUITextureManager
{
public:
  inline static GUITextureManager& GetInstance();
  inline static void Destruct();

  ~GUITextureManager();

  void Initialise();
  void Clear();

  /// Get a sprite for an image and state
  Sprite NewSprite( const EGUITexture image,
		    const EGUITextureState state );
  /// Change the colour scheme
  void ChangeColourScheme( GUIColourPalette* palette );
private:
  sf::Texture* Colourise( GUIColourPalette* palette,
			EGUITextureState state,
			sf::Rect<int> sourceRect,
			sf::Texture* colouredTexture );

  /// Cannot instantiate this class, is singleton
  GUITextureManager();
  static GUITextureManager* fGUITextureManager;
  static std::map< EGUITexture, sf::Rect<int> > fSubRectMap;

  GUITextureMap fTextures;   /// < Map of GUI images by type then by state
  sf::Uint8* fBasePixels; /// < Pixels of base GUI image
  int fBaseWidth;
  int fBaseHeight;
};

void
GUITextureManager::Destruct()
{
  if( fGUITextureManager != NULL )
    delete fGUITextureManager;
  fGUITextureManager = NULL;
}

GUITextureManager& 
GUITextureManager::GetInstance()
{
  if( fGUITextureManager == NULL )
    fGUITextureManager = new GUITextureManager();
  return *fGUITextureManager;
}

} // ::Viewer

#endif
