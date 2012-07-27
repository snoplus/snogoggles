#include <SFML/OpenGL.hpp>

#include <iostream>
using namespace std;

#include <Viewer/Rect.hh>
#include <Viewer/RectPtr.hh>
using namespace Viewer;

double Rect::fsWindowHeight = 0.0;
double Rect::fsWindowWidth = 0.0;
double Rect::fsResolutionHeight = 0.0;
double Rect::fsResolutionWidth = 0.0;

Rect&
Rect::NewMother()
{
  // Only the global mother has a mother pointer to a NULL
  return *(new Rect( NULL )); 
}

Rect*
Rect::NewDaughter()
{
  Rect* daughter = new Rect( this );
  fDaughters.push_back( daughter );
  return daughter;
}

Rect*
Rect::NewDaughter( const sf::Rect<double>& rect,
                   ECoordSystem system = eLocal )
{
  Rect* daughter = NewDaughter();
  daughter->SetRect( rect, system );
  return daughter;
}

Rect::~Rect()
{
  // Unlink from mother's list
  if( fMother != NULL )
    fMother->RemoveDaughter( this );
  // Deleting should cascade down from this mother rect (or the global one)
  for( vector<Rect*>::iterator iTer = fDaughters.begin(); iTer != fDaughters.end(); iTer++ )
    {
      (*iTer)->fMother = NULL;
    }
  fDaughters.clear();
}

void
Rect::RemoveDaughter( Rect* daughter )
{
  for( vector<Rect*>::iterator iTer = fDaughters.begin(); iTer != fDaughters.end(); )
    if( *iTer == daughter ) // Found daughter
      iTer = fDaughters.erase( iTer );
    else
      ++iTer;
}

void 
Rect::SetRect( const sf::Rect<double>& rect,
	       ECoordSystem system )
{
  if( system == eLocal )
    {
      fLeft = rect.left;
      fTop = rect.top;
      fWidth = rect.width;
      fHeight = rect.height;
    }
  else
    {
      sf::Rect<double> motherRect = fMother->GetRect( system );
      fLeft = ( rect.left - motherRect.left ) / motherRect.width;
      fWidth = rect.width / motherRect.width;
      fTop = ( rect.top - motherRect.top ) / motherRect.height;
      fHeight = rect.height / motherRect.height;
    }
}

sf::Rect<double> 
Rect::GetRect( int level )
{
  sf::Rect<double> result;
  if( fMother == NULL || level == 0 )
    {
      result.left = fLeft;
      result.top = fTop;
      result.width = fWidth;
      result.height = fHeight;
    }
  else
    {
      sf::Rect<double> motherRect = fMother->GetRect( level - 1 );
      result.left = fLeft * motherRect.width + motherRect.left;
      result.top = fTop * motherRect.height + motherRect.top;
      result.width = fWidth * motherRect.width;
      result.height = fHeight* motherRect.height;
    }
  return result;
}

sf::Rect<double> 
Rect::GetRect( const ECoordSystem& system )
{
  if( system == eLocal )
    return GetRect( 0 );
  else if( system == eWindow )
    {
      const sf::Rect<double> localToMother = GetRect( -1 );
      sf::Rect<double> result;
      result.left   = localToMother.left   * fsWindowWidth;
      result.top    = localToMother.top    * fsWindowHeight;
      result.width  = localToMother.width  * fsWindowWidth;
      result.height = localToMother.height * fsWindowHeight;
      return result;
    }
  else if( system == eGL )
    {
      sf::Rect<double> result = GetRect( eWindow );
      result.top = fsWindowHeight - ( result.top + result.height );
      return result;
    }
  else // eResolution
    {
      const sf::Rect<double> localToMother = GetRect( -1 );
      sf::Rect<double> result;
      result.left   = localToMother.left   * fsResolutionWidth;
      result.top    = localToMother.top    * fsResolutionHeight;
      result.width  = localToMother.width  * fsResolutionWidth;
      result.height = localToMother.height * fsResolutionHeight;
      return result;
    }
}

bool
Rect::OverlapsRect( const sf::Rect<double>& testRect )
{
  if( this->ContainsPoint( sf::Vector2<double>( testRect.left, testRect.top ), eResolution ) ) return true;
  if( this->ContainsPoint( sf::Vector2<double>( testRect.left + testRect.width, testRect.top ), eResolution ) ) return true;
  if( this->ContainsPoint( sf::Vector2<double>( testRect.left, testRect.top + testRect.height ), eResolution ) ) return true;
  if( this->ContainsPoint( sf::Vector2<double>( testRect.left + testRect.width, testRect.top + testRect.height), eResolution ) ) return true;
  sf::Rect<double> thisRect = this->GetRect( eResolution );
  RectPtr testTemp( fMother->NewDaughter( testRect, eResolution ) ); // Will be deleted on loss of scope
  if( testTemp->ContainsPoint( sf::Vector2<double>( thisRect.left, thisRect.top ), eResolution ) ) return true;
  if( testTemp->ContainsPoint( sf::Vector2<double>( thisRect.left + thisRect.width, thisRect.top ), eResolution ) ) return true;
  if( testTemp->ContainsPoint( sf::Vector2<double>( thisRect.left, thisRect.top + thisRect.height ), eResolution ) ) return true;
  if( testTemp->ContainsPoint( sf::Vector2<double>( thisRect.left + thisRect.width, thisRect.top + thisRect.height), eResolution ) ) return true;
  return false;
}

bool 
Rect::ContainsRect( const sf::Rect<double>& testRect,
                    const ECoordSystem system )
{
  sf::Rect<double> thisRes = GetRect( system );
  const double thisRight = thisRes.left + thisRes.width;
  const double testRight = testRect.left + testRect.width;
  const double thisBottom = thisRes.top + thisRes.height;
  const double testBottom = testRect.top + testRect.height;
  if( thisRes.left <= testRect.left && thisRight >= testRight && thisRes.top <= testRect.top && thisBottom >= testBottom )
    return true;
  else
    return false;      
}

bool 
Rect::ContainsPoint( const sf::Vector2<double>& testPoint,
                     const ECoordSystem system )
{
  sf::Rect<double> testRect;
  testRect.left = testPoint.x;
  testRect.top = testPoint.y;
  testRect.width = 0.0;
  testRect.height = 0.0;
  return ContainsRect( testRect, system );
}

void
Rect::SetAsGLViewport()
{
  sf::Rect<double> thisWin = GetRect( eGL );
  glViewport( thisWin.left, thisWin.top, thisWin.width, thisWin.height );
}

sf::Vector2<double>
Rect::GetOpenGLCoords( const sf::Vector2<double>& windowCoords )
{
    sf::Vector2<double> result = windowCoords;
    result.x = result.x * fsWindowWidth / fsResolutionWidth;
    result.y = fsWindowHeight - result.y * fsWindowHeight / fsResolutionHeight;
    return result;
}
