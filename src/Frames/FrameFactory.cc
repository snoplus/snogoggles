#include <Viewer/FrameFactory.hh>
// Utility Frames
#include <Viewer/EventUI.hh>
#include <Viewer/About.hh>
#include <Viewer/EventInfo.hh>
#include <Viewer/ColourPicker.hh>
// Test (Not built by default)
#include <Viewer/Logo.hh>
#include <Viewer/TestBox.hh>
// 2d Projections
#include <Viewer/LambertProjection.hh>
#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/EllipticalProjection.hh>
#include <Viewer/CrateView.hh>
// 2d histograms
#include <Viewer/TimeHist.hh>
#include <Viewer/ChargeHist.hh>
// 3d Views
#include <Viewer/HitFrame3d.hh>
#include <Viewer/TrackFrame3d.hh>
#include <Viewer/RATGeoFrame3d.hh>
using namespace Viewer;

#include <string>
using namespace std;

FrameFactory::FrameFactory()
{
  RegisterFrame( Frames::About::Name(), new Alloc<Frame, Frames::About>(), Frame::eUtil );
  RegisterFrame( Frames::EventUI::Name(), new Alloc<Frame, Frames::EventUI>(), Frame::eUtil );
  RegisterFrame( Frames::EventInfo::Name(), new Alloc<Frame, Frames::EventInfo>(), Frame::eUtil );
  RegisterFrame( Frames::ColourPicker::Name(), new Alloc<Frame, Frames::ColourPicker>(), Frame::eUtil );
  //RegisterFrame( Frames::Logo::Name(), new Alloc<Frame, Frames::Logo>(), Frame::eUtil );
  //RegisterFrame( Frames::TestBox::Name(), new Alloc<Frame, Frames::TestBox>(), Frame::eUtil );
  RegisterFrame( Frames::LambertProjection::Name(), new Alloc<Frame, Frames::LambertProjection>(), Frame::e2d );
  //Icosahedral Projection KC - 21/07/11
  RegisterFrame(Frames::IcosahedralProjection::Name(),new Alloc<Frame,Frames::IcosahedralProjection>(), Frame::e2d );
  //Time Histogram KC - 24/07/11
  RegisterFrame( Frames::TimeHist::Name(),new Alloc<Frame,Frames::TimeHist>(), Frame::e2d );
  //Charge Histogram KC - 24/07/11
  RegisterFrame( Frames::ChargeHist::Name(),new Alloc<Frame,Frames::ChargeHist>(), Frame::e2d );
  //Elliptical Projection KC - 26/07/11
  RegisterFrame(Frames::EllipticalProjection::Name(),new Alloc<Frame,Frames::EllipticalProjection>(), Frame::e2d );
  //Crate View KC - 05/08/11
  RegisterFrame(Frames::CrateView::Name(),new Alloc<Frame,Frames::CrateView>(), Frame::e2d );

  // 3D Frames
  RegisterFrame( Frames::HitFrame3d::Name(), new Alloc<Frame, Frames::HitFrame3d>(), Frame::e3d );
  RegisterFrame( Frames::TrackFrame3d::Name(), new Alloc<Frame, Frames::TrackFrame3d>(), Frame::e3d );
  RegisterFrame( Frames::RATGeoFrame3d::Name(), new Alloc<Frame, Frames::RATGeoFrame3d>(), Frame::e3d );
}

void 
FrameFactory::RegisterFrame( const std::string& name, AllocBase<Frame> *allocator, Frame::EFrameType frameType )
{
  Register( name, allocator );
  fTypeMap[name] = frameType;
}
