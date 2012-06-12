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
///     03/06/12 : P.Jones - Third Revision, no longer a singleton.\n
///
/// \detail  A GUI base image is loaded and then coloured at run time 
///          to produce the GUI textures (buttons). This class holds the
///          GUI textures, returning a usable reference. Textures are
///          now indexed by number with the texture position being the
///          (number/10, number%10)*20 pixels.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUITextureManager__
#define __Viewer_GUITextureManager__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Config.hpp>

#include <map>
#include <vector>

#include <Viewer/Colour.hh>
#include <Viewer/GUI.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{

class GUITextureManager
{
public:
  GUITextureManager();
  /// Destruct and delete textures
  ~GUITextureManager();
  /// Initialise and load the pixels
  void Initialise();
  /// Delete and clear the textures
  void ClearTextures();
  /// Get a pointer to the gui-image-state texture
  sf::Texture* GetTexture( unsigned int textureNumber,
                           EGUIState state ) const;
  /// Notify on change of the colour scheme
  void Update();
private:
  void FillPixels( sf::Uint8* pixels, 
                   sf::Rect<int> sourceRect,
                   EGUIState state );

  /// Produce the Pixel colour from the shape colours
  Colour Colourise( Colour shapeA, 
                    Colour shapeB,
                    EGUIState state );
  
  std::map< EGUIState, std::vector< sf::Texture*> > fTextures;
  
  sf::Uint8* fBasePixelsA; /// < Base pixels from image A
  sf::Uint8* fBasePixelsB; /// < Base pixels from image B
  unsigned int fBaseWidth; /// < Base pixel width
  unsigned int fBaseHeight; /// < Base pixel height
};

} // ::Viewer

#endif
