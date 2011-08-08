////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIImageManager
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

#ifndef __Viewer_GUIImageManager__
#define __Viewer_GUIImageManager__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Config.hpp>

#include <map>

#include <Viewer/Sprite.hh>
#include <Viewer/GUIColourPalette.hh>

namespace sf
{
  class Image;
}

namespace Viewer
{
  enum EGUIImage { eBarLeft, eBar, eBarRight, eDecrease, eIncrease, ePlus, eCross, eOpenBox, eCrossBox };
  typedef std::map< EGUIImage, std::map< EGUIImageState, sf::Image* > > GUIImageMap;

class GUIImageManager
{
public:
  inline static GUIImageManager& GetInstance();
  inline static void Destruct();

  ~GUIImageManager();

  void Initialise();
  void Clear();

  /// Get a sprite for an image and state
  Sprite NewSprite( const EGUIImage image,
		    const EGUIImageState state );
  /// Change the colour scheme
  void ChangeColourScheme( GUIColourPalette* palette );
private:
  sf::Image* Colourise( GUIColourPalette* palette,
			EGUIImageState state,
			sf::Rect<int> sourceRect,
			sf::Image* colouredImage );

  /// Cannot instantiate this class, is singleton
  GUIImageManager();
  static GUIImageManager* fGUIImageManager;
  static std::map< EGUIImage, sf::Rect<int> > fSubRectMap;

  GUIImageMap fImages;   /// < Map of GUI images by type then by state
  sf::Uint8* fBasePixels; /// < Pixels of base GUI image
  int fBaseWidth;
  int fBaseHeight;
};

void
GUIImageManager::Destruct()
{
  if( fGUIImageManager != NULL )
    delete fGUIImageManager;
  fGUIImageManager = NULL;
}

GUIImageManager& 
GUIImageManager::GetInstance()
{
  if( fGUIImageManager == NULL )
    fGUIImageManager = new GUIImageManager();
  return *fGUIImageManager;
}

} // ::Viewer

#endif
