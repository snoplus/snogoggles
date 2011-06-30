////////////////////////////////////////////////////////////////////////
/// \class Viewer::ImageManager
///
/// \brief   Controls sf::Images, such that each is loaded once
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Multiple instances of the same image wastes memory, do not do
///          it.
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::ImageNotFoundError
///
/// \brief  An exception that is thrown when a user attempts to load an
///         image which fails.
///
/// \author Phil G Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/2011 : P G Jones - New file \n
///
/// \detail As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Example__
#define __Viewer_Example__

#include <stdexcept>
#include <map>

#include <Viewer/Sprite.hh>

namespace sf
{
  class Image;
} // ::sf

namespace Viewer
{

class ImageManager
{
  class ImageNotFoundError : public std::runtime_error
  {
  public:
    /// Just sets up a std::runtime_error
    ImageNotFoundError( const std::string& param ) : std::runtime_error( param ) {}
  };
public:
  inline static ImageManager& GetInstance();

  ~ImageManager();

  sf::Image& GetImage( const std::string& fileName );

  Sprite NewSprite( const std::string& fileName );
private:
  ImageManager() {};

  static ImageManager* fImageManager;
  std::map< std::string, sf::Image* > fImages;
};

ImageManager& 
ImageManager::GetInstance()
{
  if( fImageManager == NULL )
    fImageManager = new ImageManager();
  return *fImageManager;
}

} // ::Viewer

#endif
