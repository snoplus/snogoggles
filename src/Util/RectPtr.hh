////////////////////////////////////////////////////////////////////////
/// \class Viewer::RectPtr
///
/// \brief   Smart(er) pointer to a Rect object
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///
/// \detail  Every drawable object needs a RectPtr to define the draw
///          coordinates. The rect object this class points two should 
///          never change, but the member values of the Rect object can.
///          This is a reference counting smart(er) pointer.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RectPtr__
#define __Viewer_RectPtr__

#include <Viewer/Rect.hh>

namespace Viewer
{

class RectPtr
{
public:
  /// Must contruct with a Rect
  RectPtr( Rect* rect )  { fRect = rect; fReferences =  new int(1); }
  RectPtr( const RectPtr& rhs )  { fRect = rhs.fRect; fReferences = rhs.fReferences; (*fReferences)++; }
  inline RectPtr& operator=( const RectPtr& rhs );

  /// On destruction should delete the Rect, and then only if it is the last reference
  inline ~RectPtr();
  /// Accessor
  Rect& operator*() { return *fRect; }
  /// Accessor
  Rect* operator->() { return fRect; }
private:
  /// Prevent usage
  RectPtr();

  Rect* fRect; /// < A pointer to the rect object
  int* fReferences; /// < For reference counting
};

inline RectPtr&
RectPtr::operator=( const RectPtr& rhs )
{
  if( this != &rhs )    
    {
      if( --(*fReferences) <= 0 )
	{
	  delete fRect;
	  delete fReferences;
	}
      fRect = rhs.fRect;
      fReferences = rhs.fReferences;
      (*fReferences)++;
    }
  return *this;
}

inline
RectPtr::~RectPtr()
{
  if( --(*fReferences) <= 0 )
    {
      delete fRect;
      delete fReferences;
    }
}

} //::Viewer

#endif
