////////////////////////////////////////////////////////////////////////
/// \class Text
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Required to allow local coordinates only
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Text__
#define __Viewer_Text__

#include <SFML/Graphics/Text.hpp>


namespace Viewer
{

class Text : public sf::Text
{
public:
  Text () : sf::Text() { }
  Text (const sf::String &string, const sf::Font &font=sf::Font::GetDefaultFont(), unsigned int characterSize=30)
    : sf::Text( string, font, characterSize ) 
  { }

  void SetBoundingRect( const sf::Rect<double>& rect ) { fRect = rect; }
  sf::Rect<double> GetBoundingRect() { return fRect; }
  void SetWidth( double width ) { fRect.Width = width; }
  void SetHeight( double height ) { fRect.Height = height; }

protected:
  sf::Rect<double> fRect;
private:
  /// Should not be called
// Functions to overload, or maybe blocked??
  void SetPosition( float x, float y ) { fRect.Left = x; fRect.Top = y; }
  void SetPosition( const sf::Vector2f& position ) { fRect.Left = position.x; fRect.Top = position.y; }
  void SetX( float x ) { fRect.Left = x; }
  void SetY( float y ) { fRect.Top = y; }
  void SetOrigin( float x, float y ) { fRect.Left = x + fRect.Width / 2.0; fRect.Top = y + fRect.Height / 2.0; }
  void SetOrigin( const sf::Vector2f& origin ) { fRect.Left = origin.x + fRect.Width / 2.0; fRect.Top = origin.y + fRect.Height / 2.0; }

  void SetScale(float factorX, float factorY);
  void SetScaleX(float factor);
  void SetScaleY(float factor);
  const sf::Vector2f& GetScale() const;
  const sf::Vector2f& GetPosition() const;
  const sf::Vector2f& GetOrigin() const;
  void Move (float offsetX, float offsetY);
  void Move (const sf::Vector2f &offset);
  sf::FloatRect GetRect () const;
};

} // ::Viewer

#endif
