////////////////////////////////////////////////////////////////////////
/// \class Sprite
///
/// \brief   A drawable texture defined in local coords
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     17/02/12 : P.Jones - Second Revision uses sf::Texture and new
///                Rect system. \n
///
/// \detail  A texture with a position defined locally which can be drawn
///          in global coords by sfml.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Sprite__
#define __Viewer_Sprite__

#include <SFML/Graphics/Texture.hpp>

#include <Viewer/RectPtr.hh>

namespace Viewer
{

class Sprite
{
public:
  /// Destructor
  virtual ~Sprite() { fTexture = NULL; }

  /// Construct the sprite with a Rect reference
  inline Sprite( RectPtr localRect );
  /// Set the texture
  inline void SetTexture( sf::Texture* texture );
  /// Return the Rect by reference
  inline RectPtr GetRect();
  /// Return the texture
  inline sf::Texture& GetTexture();
protected:
  sf::Texture* fTexture; //! < The texture
  RectPtr fLocalRect;    //! < The rect
};

inline 
Sprite::Sprite( RectPtr localRect )
  : fLocalRect( localRect )
{

}
  
inline void 
Sprite::SetTexture( sf::Texture* texture )
{
  fTexture = texture;
}

inline RectPtr
Sprite::GetRect()
{
  return fLocalRect;
}

inline sf::Texture& 
Sprite::GetTexture()
{
  return *fTexture;
}

} // ::Viewer

#endif
