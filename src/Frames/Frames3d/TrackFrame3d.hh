////////////////////////////////////////////////////////////////////////
/// \class Viewer::TrackFrame3d
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

#ifndef __Viewer_TrackFrame3d__
#define __Viewer_TrackFrame3d__

#include <string>

#include <Viewer/Frame3d.hh>

namespace Viewer
{
namespace Frames
{

class TrackFrame3d : public Frame3d
{
public:
  TrackFrame3d( RectPtr rect );
  virtual ~TrackFrame3d() { }
  std::string GetName() { return TrackFrame3d::Name(); }
  static std::string Name() { return std::string( "Tracks" ); }
};

}

} //::Viewer

#endif
