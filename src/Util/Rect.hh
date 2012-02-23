////////////////////////////////////////////////////////////////////////
/// \class Viewer::Rect
///
/// \brief   A Rectangle coordinate.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     14/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  All coordinates are rects, these are heirarchical allowing
///          both local and global values to be calculated at different
///          levels. Also allows all overlaps to be tested at the global
///          scale for simplicity.
///          Only the ViewerWindow class may have the global Mother.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Rect__
#define __Viewer_Rect__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <utility>

namespace Viewer
{

class Rect
{
public:
  enum ECoordSystem { eLocal, eWindow, eResolution };
  /// Creat the global mother rect
  static Rect& NewMother();
  /// Create a new Daughter rect for usage
  Rect* NewDaughter(); 
  /// Create a new Daughter pre defining the rect
  Rect* NewDaughter( const sf::Rect<double>& rect,
		     ECoordSystem system );
  /// Destructor (must notify daughters)
  ~Rect();
  /// Set the rect in the stated coordinate system
  void SetRect( const sf::Rect<double>& rect, 
		ECoordSystem system );
  /// Get the local rect coordinates in terms of the 'level' mother, 
  /// default to local to this class's mother i.e. level 0.
  /// Call with level < 0  to get a local coordinate in the mothers system
  sf::Rect<double> GetRect( int level = 0 );
  /// Get the rect in a particular coordinate system
  sf::Rect<double> GetRect( ECoordSystem system );
  /// Returns true if testRect is fully contained in this rect
  /// Always tests in global values for simplicity
  bool ContainsRect( const sf::Rect<double>& testRect,
		     const ECoordSystem system );
  /// Returns true if the window coordinate is within this rect
  bool ContainsPoint( const sf::Vector2<double>& testPoint,
		      const ECoordSystem system );
protected:
  /// Unlink a daughter
  void DeleteDaughter( Rect* daughter );
  /// Can only construct with a mother rectangle
  inline Rect( Rect* mother );

  Rect* fMother; //! < Pointer to the mother rect
  std::vector<Rect*> fDaughters; //! < Pointer to the daughter rects

  double fLeft;   //! < Always Local to the mother
  double fTop;    //! < Always Local to the mother
  double fWidth;  //! < Always Local to the mother
  double fHeight; //! < Always Local to the mother

private:
  /// Do not allow construction without a mother
  Rect(); 
  /// Also block copying
  Rect( Rect const& );
  void operator=( Rect const& );

///////////////////////////////////////////////////////////////////////
// Static global values below
///////////////////////////////////////////////////////////////////////
public:
  static inline void SetWindowSize( double width, double height );
  static inline void SetWindowResolution( double width, double height );
  static inline sf::Vector2<double> GetWindowSize();
  static inline sf::Vector2<double> GetWindowResolution();

protected:
  static double fsWindowHeight;
  static double fsWindowWidth;
  static double fsResolutionHeight;
  static double fsResolutionWidth;
};

inline 
Rect::Rect( Rect* mother )
  : fMother( mother )
{

}

inline void 
Rect::SetWindowSize( double width, 
		     double height )
{
  fsWindowWidth = width;
  fsWindowHeight = height;
}

inline void
Rect::SetWindowResolution( double width,
			   double height )
{
  fsResolutionWidth = width;
  fsResolutionHeight = height;
}

inline sf::Vector2<double>
Rect::GetWindowSize()
{
  return sf::Vector2<double>( fsWindowWidth, fsWindowHeight );
}

inline sf::Vector2<double>
Rect::GetWindowResolution()
{
  return sf::Vector2<double>( fsResolutionWidth, fsResolutionHeight );
}

} // ::Viewer

#endif
