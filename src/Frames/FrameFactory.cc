#include <Viewer/FrameFactory.hh>
#include <Viewer/Logo.hh>
using namespace Viewer;

#include <iostream>

FrameFactory::FrameFactory()
{
  Register( Frames::Logo::Name(), new Alloc<Frame, Frames::Logo>() );
}
