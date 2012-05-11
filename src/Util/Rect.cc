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
      fLeft = rect.Left;
      fTop = rect.Top;
      fWidth = rect.Width;
      fHeight = rect.Height;
    }
  else
    {
      sf::Rect<double> motherRect = fMother->GetRect( system );
      fLeft = ( rect.Left - motherRect.Left ) / motherRect.Width;
      fWidth = rect.Width / motherRect.Width;
      fTop = ( rect.Top - motherRect.Top ) / motherRect.Height;
      fHeight = rect.Height / motherRect.Height;
    }
}

sf::Rect<double> 
Rect::GetRect( int level )
{
  sf::Rect<double> result;
  if( fMother == NULL || level == 0 )
    {
      result.Left = fLeft;
      result.Top = fTop;
      result.Width = fWidth;
      result.Height = fHeight;
    }
  else
    {
      sf::Rect<double> motherRect = fMother->GetRect( level - 1 );
      result.Left = fLeft * motherRect.Width + motherRect.Left;
      result.Top = fTop * motherRect.Height + motherRect.Top;
      result.Width = fWidth * motherRect.Width;
      result.Height = fHeight* motherRect.Height;
    }
  return result;
}

sf::Rect<double> 
Rect::GetRect( ECoordSystem system )
{
  if( system == eLocal )
    return GetRect( 0 );
  else if( system == eWindow )
    {
      const sf::Rect<double> localToMother = GetRect( -1 );
      sf::Rect<double> result;
      result.Left   = localToMother.Left   * fsWindowWidth;
      result.Top    = localToMother.Top    * fsWindowHeight;
      result.Width  = localToMother.Width  * fsWindowWidth;
      result.Height = localToMother.Height * fsWindowHeight;
      return result;
    }
  else if( system == eGL )
    {
      sf::Rect<double> result = GetRect( eWindow );
      result.Top = fsWindowHeight - ( result.Top + result.Height );
      return result;
    }
  else // eResolution
    {
      const sf::Rect<double> localToMother = GetRect( -1 );
      sf::Rect<double> result;
      result.Left   = localToMother.Left   * fsResolutionWidth;
      result.Top    = localToMother.Top    * fsResolutionHeight;
      result.Width  = localToMother.Width  * fsResolutionWidth;
      result.Height = localToMother.Height * fsResolutionHeight;
      return result;
    }
}

bool 
Rect::ContainsRect( const sf::Rect<double>& testRect,
		    const ECoordSystem system )
{
  sf::Rect<double> thisRes = GetRect( system );
  const double thisRight = thisRes.Left + thisRes.Width;
  const double testRight = testRect.Left + testRect.Width;
  const double thisBottom = thisRes.Top + thisRes.Height;
  const double testBottom = testRect.Top + testRect.Height;
  if( thisRes.Left < testRect.Left && thisRight > testRight && thisRes.Top < testRect.Top && thisBottom > testBottom )
    return true;
  else
    return false;      
}

bool 
Rect::ContainsPoint( const sf::Vector2<double>& testPoint,
		     const ECoordSystem system )
{
  sf::Rect<double> testRect;
  testRect.Left = testPoint.x;
  testRect.Top = testPoint.y;
  testRect.Width = 0.0;
  testRect.Height = 0.0;
  return ContainsRect( testRect, system );
}

void
Rect::SetAsGLViewport()
{
  sf::Rect<double> thisWin = GetRect( eGL );
  glViewport( thisWin.Left, thisWin.Top, thisWin.Width, thisWin.Height );
}
