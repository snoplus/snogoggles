#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <sstream>
using namespace std;

#include <Viewer/ImageManager.hh>
using namespace Viewer;

ImageManager* ImageManager::fImageManager = NULL;

ImageManager::~ImageManager()
{
  for( map< string, sf::Image* >::iterator iTer = fImages.begin(); iTer != fImages.end(); iTer++ )
    delete iTer->second;
  fImages.clear();
}

sf::Image&
ImageManager::GetImage(
		       const string& fileName )
{
  sf::Image* image = fImages[fileName];
  if( image == NULL )
    {
      image = new sf::Image();
      // Initialise image and check success
      stringstream fileLocation;
      fileLocation << getenv( "VIEWERROOT" ) << "/images/" << fileName;
      if( !image->LoadFromFile( fileLocation.str().c_str() ) ) // No file with that name & extension
	throw ImageNotFoundError( fileName );
      fImages[fileName] = image;
    }
  return *image;
}

Sprite
ImageManager::NewSprite(
			const string& fileName )
{
  // sf::Images are resource safe, i.e. Sprites will know when Image is deleted
  Sprite sprite;
  sprite.SetImage( GetImage( fileName ) );
  return sprite;
}
