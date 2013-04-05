////////////////////////////////////////////////////////////////////////
/// \class ReconBuffer
///
/// \brief  Special VBO to create, store and render vertices for fitted 
///         positions.
///
/// \author  Phil G Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 05/04/13 : P.Jones - First Revision, new file. \n
///
/// \detail  For each position draws a 3d cross.
///          Rendering is done using the parent VBO class. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ReconBuffer__
#define __Viewer_ReconBuffer__

class TVector3;

#include <Viewer/VBO.hh>

namespace Viewer 
{
  class Colour;
  
class ReconBuffer : public VBO 
{
public:
  void AddRecon( const TVector3& pos, 
                 const Colour& colour );
};

} // namespace Viewer

#endif
