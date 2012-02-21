////////////////////////////////////////////////////////////////////////
/// \class Viewer::TextureManager
///
/// \brief   Controls sf::Textures, such that each is loaded once
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     18/02/12 : P.Jones - Second Revision, now uses Textures instead. \n
///
/// \detail  Multiple instances of the same image wastes memory, do not do
///          it.
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::TextureNotFoundError
///
/// \brief  An exception that is thrown when a user attempts to load an
///         image which fails.
///
/// \author Phil G Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/2011 : P G Jones - New file \n
///     18/02/12 : P.Jones - Second Revision, now uses Textures instead. \n
///
/// \detail As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_TextureManager__
#define __Viewer_TextureManager__

#include <stdexcept>
#include <map>

#include <Viewer/Sprite.hh>

namespace sf
{
  class Texture;
} // ::sf

namespace Viewer
{

class TextureManager
{
  class TextureNotFoundError : public std::runtime_error
  {
  public:
    /// Just sets up a std::runtime_error
    TextureNotFoundError( const std::string& param ) : std::runtime_error( param ) {}
  };
public:
  /// Return the singleton instance
  inline static TextureManager& GetInstance();
  /// Destruct the Image Manager, delete the textures
  ~TextureManager();
  /// Return a texture given a filename
  sf::Texture* GetTexture( const std::string& fileName );
private:
  std::map< std::string, sf::Texture* > fTextures;

  // Stop the usage of:
  TextureManager() {};
  TextureManager( TextureManager& );
  void operator=( TextureManager& );
};

inline TextureManager& 
TextureManager::GetInstance()
{
  static TextureManager textureManager;
  return textureManager;
}

} // ::Viewer

#endif
