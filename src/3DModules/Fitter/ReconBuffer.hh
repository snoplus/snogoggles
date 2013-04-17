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

#include <map>
#include <string>

#include <Viewer/VBO.hh>

namespace Viewer 
{
  class Colour;
namespace RIDS
{
  class Vertex;
}

class ReconBuffer
{
public:
  void Clear();
  void Render();

  void AddVertex( const RIDS::Vertex& vertex, 
                  const Colour& colour );
private:
  std::map< std::string, VBO > fVertices;
};

} // namespace Viewer

#endif
