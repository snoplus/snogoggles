////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUITextureManager
///
/// \brief   Returns a GUI texture with the appropriate current colour.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///     20/02/12 : P.Jones - Second Revision, refactor the code. \n
///
/// \detail  A GUI base image is loaded and then coloured at run time 
///          to produce the GUI textures (buttons). This class holds the
///          GUI textures, returning a usable reference.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUITextureManager__
#define __Viewer_GUITextureManager__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Config.hpp>

#include <map>

#include <Viewer/GUI.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
  enum EGUITexture { eBarLeft, eBar, eBarRight, eDecrease, eIncrease, ePlus, eCross, eOpenBox, eCrossBox, eNewFrameLeft, eNewFrame, eNewFrameRight };
  typedef std::map< EGUITexture, std::map< EGUIState, sf::Texture* > > GUITextureMap;
  typedef std::map< EGUITexture, sf::Rect<int> > GUIRectMap;

class GUITextureManager
{
public:
  /// Destruct and delete textures
  virtual ~GUITextureManager();
  /// Return the singleton instance
  inline static GUITextureManager& GetInstance();
  /// Initialise and load the pixels
  void Initialise();
  /// Get a pointer to the gui-image-state texture
  sf::Texture* GetTexture( EGUITexture image,
                           EGUIState state );
  /// Notify and change the colour scheme
  void ChangeColourScheme();
  /// Delete and clear the textures
  void ClearTextures();
private:
  GUITextureManager();

  /// Colourise a single texture and add it to the fTextures map
  void Colourise( EGUITexture image,
                  EGUIState state );
  
  GUIRectMap fSubRects; /// < Maps the pixel extent of each GUITexture to an EGUITexture
  GUITextureMap fTextures; /// < Maps the actual texture to an EGUITexture + EGUIState
  
  sf::Uint8* fBasePixels; /// < Base pixels
  unsigned int fBaseWidth; /// < Base pixel width
  unsigned int fBaseHeight; /// < Base pixel height
  
  /// Stop usage of
  GUITextureManager( GUITextureManager const& );
  void operator=( GUITextureManager const& );
};

inline GUITextureManager&
GUITextureManager::GetInstance()
{
  static GUITextureManager instance;
  return instance;
}

} // ::Viewer

#endif
