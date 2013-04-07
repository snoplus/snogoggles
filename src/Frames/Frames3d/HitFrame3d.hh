////////////////////////////////////////////////////////////////////////
/// \class Viewer::HitFrame3d
///
/// \brief   The fitter 3d frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Shows fit positions.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_HitFrame3d__
#define __Viewer_HitFrame3d__

#include <string>

#include <Viewer/Frame3d.hh>

namespace Viewer
{
namespace Frames
{

class HitFrame3d : public Frame3d
{
public:
  HitFrame3d( RectPtr rect );
  virtual ~HitFrame3d() { };
  std::string GetName() { return HitFrame3d::Name(); }
  static std::string Name() { return std::string( "Hits" ); }
};

}

} //::Viewer

#endif
