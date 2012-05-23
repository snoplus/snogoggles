#include <Viewer/FrameFactory.hh>
#include <Viewer/About.hh>
#include <Viewer/EventInfo.hh>
#include <Viewer/LambertProjection.hh>
#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/CrateView.hh>
#include <Viewer/Histogram.hh>
#include <Viewer/HitFrame3d.hh>
#include <Viewer/TrackFrame3d.hh>
using namespace Viewer;

#include <string>
using namespace std;

FrameFactory::FrameFactory( RectPtr rect )
{
  RegisterFrame( Frames::About::Name(), new AllocRect<Frame, Frames::About>( rect ), Frame::eUtil );
  RegisterFrame( Frames::EventInfo::Name(), new AllocRect<Frame, Frames::EventInfo>( rect ), Frame::eUtil );

  RegisterFrame( Frames::LambertProjection::Name(), new AllocRect<Frame, Frames::LambertProjection>( rect ), Frame::e2d );
  RegisterFrame( Frames::IcosahedralProjection::Name(),new AllocRect<Frame,Frames::IcosahedralProjection>( rect ), Frame::e2d );
  RegisterFrame( Frames::Histogram::Name(),new AllocRect<Frame,Frames::Histogram>( rect ), Frame::e2d );
  RegisterFrame( Frames::CrateView::Name(),new AllocRect<Frame,Frames::CrateView>( rect ), Frame::e2d );

  RegisterFrame( Frames::HitFrame3d::Name(), new AllocRect<Frame, Frames::HitFrame3d>( rect ), Frame::e3d );
  //RegisterFrame( Frames::TrackFrame3d::Name(), new AllocRect<Frame, Frames::TrackFrame3d>( rect ), Frame::e3d );
}

void
FrameFactory::RegisterFrame( const std::string& name, AllocBase<Frame> *allocator, Frame::EFrameType frameType )
{
  Register( name, allocator );
  fTypeMap[name] = frameType;
}
