////////////////////////////////////////////////////////////////////////
/// \class Shape
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

#ifndef __Viewer_Shape__
#define __Viewer_Shape__

#include <SFML/Graphics/Shape.hpp>

namespace Viewer
{

class Shape : public sf::Shape
{
public:
  Shape() : sf::Shape() { }
  Shape( sf::Shape shape ) : sf::Shape( shape ) { }

  void SetBoundingRect( const sf::Rect<double>& rect ) { fRect = rect; }
  sf::Rect<double> GetBoundingRect() { return fRect; }
  void SetWidth( double width ) { fRect.Width = width; }
  void SetHeight( double height ) { fRect.Height = height; }

  void SetPosition( float x, float y ) { fRect.Left = x; fRect.Top = y; }
  void SetPosition( const sf::Vector2<double>& position ) { fRect.Left = position.x; fRect.Top = position.y; }

  void SetScale(float factorX, float factorY) { fRect.Width = fRect.Width * factorX, fRect.Height = fRect.Height * factorY; };
protected:
  sf::Rect<double> fRect;
private:
  /// Should not be called
// Functions to overload, or maybe blocked??
  void SetX( float x ) { fRect.Left = x; }
  void SetY( float y ) { fRect.Top = y; }
  void SetOrigin( float x, float y ) { fRect.Left = x + fRect.Width / 2.0; fRect.Top = y + fRect.Height / 2.0; }
  void SetOrigin( const sf::Vector2f& origin ) { fRect.Left = origin.x + fRect.Width / 2.0; fRect.Top = origin.y + fRect.Height / 2.0; }

  void SetScaleX(float factor);
  void SetScaleY(float factor);
  const sf::Vector2f& GetScale() const;
  const sf::Vector2f& GetPosition() const;
  const sf::Vector2f& GetOrigin() const;
};

} // ::Viewer

#endif
