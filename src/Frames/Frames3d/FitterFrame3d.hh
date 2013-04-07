////////////////////////////////////////////////////////////////////////
/// \class Viewer::FitterFrame3d
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

#ifndef __Viewer_FitterFrame3d__
#define __Viewer_FitterFrame3d__

#include <string>

#include <Viewer/Frame3d.hh>

namespace Viewer
{
namespace Frames
{

class FitterFrame3d : public Frame3d
{
public:
  FitterFrame3d( RectPtr rect );
  virtual ~FitterFrame3d() { }
  std::string GetName() { return FitterFrame3d::Name(); }
  static std::string Name() { return std::string( "Fits" ); }
};

}

} //::Viewer

#endif
