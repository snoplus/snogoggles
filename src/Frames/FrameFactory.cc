#include <Viewer/FrameFactory.hh>
#include <Viewer/About.hh>
#include <Viewer/EventInfo.hh>
#include <Viewer/BufferInfo.hh>
#include <Viewer/LambertProjection.hh>
#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/CrateView.hh>
#include <Viewer/Histogram.hh>
#include <Viewer/HitFrame3d.hh>
#include <Viewer/TrackFrame3d.hh>
#include <Viewer/FitterFrame3d.hh>
using namespace Viewer;

#include <string>
using namespace std;

FrameFactory::FrameFactory()
{
  Register( Frames::About::Name(), new FrameAlloc<Frames::About>() );
  Register( Frames::EventInfo::Name(), new FrameAlloc<Frames::EventInfo>() );
  Register( Frames::BufferInfo::Name(), new FrameAlloc<Frames::BufferInfo>() );

  Register( Frames::LambertProjection::Name(), new FrameAlloc<Frames::LambertProjection>() );
  Register( Frames::IcosahedralProjection::Name(),new FrameAlloc<Frames::IcosahedralProjection>() );
  Register( Frames::Histogram::Name(),new FrameAlloc<Frames::Histogram>() );
  Register( Frames::CrateView::Name(),new FrameAlloc<Frames::CrateView>() );

  Register( Frames::HitFrame3d::Name(), new FrameAlloc<Frames::HitFrame3d>() );
  Register( Frames::TrackFrame3d::Name(), new FrameAlloc<Frames::TrackFrame3d>() );
  Register( Frames::FitterFrame3d::Name(), new FrameAlloc<Frames::FitterFrame3d>() );
}
