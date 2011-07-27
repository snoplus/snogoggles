#include <Viewer/FrameFactory.hh>
#include <Viewer/Logo.hh>
#include <Viewer/TestBox.hh>
#include <Viewer/LambertProjection.hh>
#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/TimeHist.hh>
#include <Viewer/ChargeHist.hh>
#include <Viewer/EventUI.hh>
#include <Viewer/About.hh>
#include <Viewer/Combo3d.hh>
#include <Viewer/HitsFrame3d.hh>
#include <Viewer/TracksFrame3d.hh>
#include <Viewer/RATFrame3d.hh>
using namespace Viewer;

#include <vector>
#include <string>
using namespace std;

FrameFactory::FrameFactory()
{
  Register( Frames::About::Name(), new Alloc<Frame, Frames::About>() );
  Register( Frames::Logo::Name(), new Alloc<Frame, Frames::Logo>() );
  Register( Frames::TestBox::Name(), new Alloc<Frame, Frames::TestBox>() );
  Register( Frames::LambertProjection::Name(), new Alloc<Frame, Frames::LambertProjection>() );
  //Icosahedral Projection KC - 21/07/11
  Register(Frames::IcosahedralProjection::Name(),new Alloc<Frame,Frames::IcosahedralProjection>());
  //Time Histogram KC - 24/07/11
  Register( Frames::TimeHist::Name(),new Alloc<Frame,Frames::TimeHist>() );
  //Charge Histogram KC - 24/07/11
  Register( Frames::ChargeHist::Name(),new Alloc<Frame,Frames::ChargeHist>() );
  Register( Frames::EventUI::Name(), new Alloc<Frame, Frames::EventUI>() );
  
  // 3D Frames
  Register( Frames::Combo3d::Name(), new OptionsAlloc<Frame, Frames::Combo3d>() );
  Register( Frames::HitsFrame3d::Name(), new Alloc<Frame, Frames::HitsFrame3d>() );
  Register( Frames::TracksFrame3d::Name(), new Alloc<Frame, Frames::TracksFrame3d>() );
  Register( Frames::RATFrame3d::Name(), new Alloc<Frame, Frames::RATFrame3d>() );
}

vector<string>
FrameFactory::GetNames()
{
  vector<string> names;
  for( std::map< std::string, AllocBase<Frame>* >::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
    names.push_back( iTer->first );
  return names;
}
