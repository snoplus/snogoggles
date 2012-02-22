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
#include <iostream>
using namespace std;

namespace Viewer
{

class RectPtr
{
public:
  /// Must contruct with a Rect
  explicit RectPtr( Rect* rect )  { fpRect = rect; fReferences =  new int(1); }
  RectPtr( const RectPtr& rhs )  { fpRect = rhs.fpRect; fReferences = rhs.fReferences; (*fReferences)++;}
  inline RectPtr& operator=( const RectPtr& rhs );

  /// On destruction should delete the Rect, and then only if it is the last reference
  inline ~RectPtr();
  /// Accessor
  Rect& operator*() { return *fpRect; }
  /// Accessor
  Rect* operator->() { return fpRect; }
private:
  /// Prevent usage
  RectPtr() : fpRect(NULL), fReferences(NULL) { }

  Rect* fpRect; /// < A pointer to the rect object
  int* fReferences; /// < For reference counting
};

inline RectPtr&
RectPtr::operator=( const RectPtr& rhs )
{
  if( this != &rhs )    
    {
      if( --(*fReferences) <= 0 )
	{
	  delete fpRect;
	  delete fReferences;
	}
      fpRect = rhs.fpRect;
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
      delete fpRect;
      delete fReferences;
    }
}

} //::Viewer

#endif
