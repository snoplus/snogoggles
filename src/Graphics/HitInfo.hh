////////////////////////////////////////////////////////////////////////
/// \class Viewer::HitInfo
///
/// \brief   Displays info about a hit PMT.    
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     08/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Standard way to display the hit information.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_HitInfo__
#define __Viewer_HitInfo__

#include <SFML/Graphics/Rect.hpp>

#include <sstream>

namespace RAT
{
namespace DS
{
  class PMTCal;
}
}

namespace Viewer
{
  class RWWrapper;

class HitInfo
{
public:
  
  void AddPMT( RAT::DS::PMTCal* rPMTCal );

  void Render( RWWrapper& windowApp );

  inline void SetRect( sf::Rect<double> localRect );

protected:
  std::stringstream fInfoStream;
  sf::Rect<double> fRect;
};

void
HitInfo::SetRect( sf::Rect<double> localRect )
{
  fRect = localRect;
}

} // ::Viewer

#endif
