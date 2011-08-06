#include <Viewer/FrameFactory.hh>
#include <Viewer/Logo.hh>
#include <Viewer/TestBox.hh>
#include <Viewer/LambertProjection.hh>
#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/EllipticalProjection.hh>
#include <Viewer/TimeHist.hh>
#include <Viewer/ChargeHist.hh>
#include <Viewer/CrateView.hh>
#include <Viewer/EventUI.hh>
#include <Viewer/About.hh>
#include <Viewer/HitFrame3d.hh>
#include <Viewer/TrackFrame3d.hh>
#include <Viewer/RATGeoFrame3d.hh>
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
  //Elliptical Projection KC - 26/07/11
  Register(Frames::EllipticalProjection::Name(),new Alloc<Frame,Frames::EllipticalProjection>());
  //Crate View KC - 05/08/11
  Register(Frames::CrateView::Name(),new Alloc<Frame,Frames::CrateView>());

  Register( Frames::EventUI::Name(), new Alloc<Frame, Frames::EventUI>() );
  
  // 3D Frames
  Register( Frames::HitFrame3d::Name(), new Alloc<Frame, Frames::HitFrame3d>() );
  Register( Frames::TrackFrame3d::Name(), new Alloc<Frame, Frames::TrackFrame3d>() );
  Register( Frames::RATGeoFrame3d::Name(), new Alloc<Frame, Frames::RATGeoFrame3d>() );
}

vector<string>
FrameFactory::GetNames()
{
  vector<string> names;
  for( std::map< std::string, AllocBase<Frame>* >::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
    names.push_back( iTer->first );
  return names;
}
