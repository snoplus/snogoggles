#include <Viewer/FrameFactory.hh>
#include <Viewer/Logo.hh>
#include <Viewer/Hist.hh>
#include <Viewer/Manager3d.hh>
#include <Viewer/TestBox.hh>
#include <Viewer/LambertProjection.hh>
#include <Viewer/EventUI.hh>
using namespace Viewer;

#include <vector>
#include <string>
using namespace std;

FrameFactory::FrameFactory()
{
    Register( Frames::Logo::Name(), new Alloc<Frame, Frames::Logo>() );
    Register( Frames::Hist::Name(),new Alloc<Frame,Frames::Hist>() );
    Register( Frames::TestBox::Name(), new Alloc<Frame, Frames::TestBox>() );
    Register( Frames::LambertProjection::Name(), new Alloc<Frame, Frames::LambertProjection>() );
    Register( Frames::EventUI::Name(), new Alloc<Frame, Frames::EventUI>() );

    // Combo 3D frame added by Olivia Wasalski 05/07/11
    Register( Frames::Manager3d::Name(), new OptionsAlloc<Frame, Frames::Manager3d>() );
}

vector<string>
FrameFactory::GetNames()
{
  vector<string> names;
  for( std::map< std::string, AllocBase<Frame>* >::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
    names.push_back( iTer->first );
  return names;
}
