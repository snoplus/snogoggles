#include <Viewer/FrameFactory.hh>
#include <Viewer/Logo.hh>
#include <Viewer/Manager3d.hh>
using namespace Viewer;

#include <iostream>

FrameFactory::FrameFactory()
{
    Register( Frames::Logo::Name(), new Alloc<Frame, Frames::Logo>() );

    // Combo 3D frame added by Olivia Wasalski 05/07/11
    Register( Frames3d::Manager3d::Name(), new OptionsAlloc<Frame, Frames3d::Manager3d>() );
}
