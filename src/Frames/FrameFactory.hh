////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameFactory
///
/// \brief   The base class for all frames
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameFactory__
#define __Viewer_FrameFactory__

#include <Viewer/Factory.hh>
#include <Viewer/Frame.hh>

namespace Viewer
{

class FrameFactory : public Factory<Frame>
{
public:   
  FrameFactory();
};

} // ::Viewer

#endif
