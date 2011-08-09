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

#include <vector>
#include <string>
#include <map>

#include <Viewer/Factory.hh>
#include <Viewer/Frame.hh>

namespace Viewer
{

class FrameFactory : public Factory<Frame>
{
public:   
  FrameFactory();
  void RegisterFrame( const std::string& name, AllocBase<Frame>* allocator, Frame::EFrameType frameType );
  std::map<std::string, Frame::EFrameType> fTypeMap;
};

} // ::Viewer

#endif
