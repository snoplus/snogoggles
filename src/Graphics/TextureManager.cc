#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <sstream>
using namespace std;

#include <Viewer/TextureManager.hh>
using namespace Viewer;

TextureManager::~TextureManager()
{
  for( map< string, sf::Texture* >::iterator iTer = fTextures.begin(); iTer != fTextures.end(); iTer++ )
    delete iTer->second;
  fTextures.clear();
}

sf::Texture*
TextureManager::GetTexture(
		       const string& fileName )
{
  sf::Texture* texture = fTextures[fileName];
  if( texture == NULL )
    {
      texture = new sf::Texture();
      // Initialise texture and check success
      stringstream fileLocation;
      fileLocation << getenv( "VIEWERROOT" ) << "/textures/" << fileName;
      if( !texture->LoadFromFile( fileLocation.str().c_str() ) ) // No file with that name & extension
	throw TextureNotFoundError( fileName );
      fTextures[fileName] = texture;
    }
  return texture;
}
