#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>

#include <TVector3.h>

#include <cmath>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/ProjectionBase.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/GeodesicSphere.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Polygon.hh>
using namespace Viewer;
using namespace Viewer::Frames;

const double kPSUPRadius = 8500.0;
const double kLocalSize = 137.0 * 0.3 / kPSUPRadius;

void
ProjectionBase::Initialise()
{
  Frame::Initialise();
  sf::Rect<double> imageSize;
  imageSize.Left = 0.0; imageSize.Top = 0.0; imageSize.Width = 1.0; imageSize.Height = 1.0;
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( imageSize, Rect::eLocal ) ) );
  fImage->SetSquareSize( sf::Vector2<double>( 1.5 * kLocalSize, 1.5 * kLocalSize ) );
}

void 
ProjectionBase::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}

void
ProjectionBase::Render2d( RWWrapper& windowApp,
			  const RenderState& renderState )
{
  fImage->Clear();

  DrawGeodesic();
  DrawHits();

  fImage->Update();
  windowApp.Draw( *fImage );
}

void
ProjectionBase::DrawHits()
{
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();

  for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
    {
      RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
      const sf::Vector2<double> projPos = Project( Vector3( rPMTList->GetPos( rPMTCal->GetID() ) ) );
      double pmtHitTime = rPMTCal->GetTime();
      fImage->DrawSquare( projPos, 
			 ColourPalette::gPalette->GetPrimaryColour( eRed ) );
    }
}

void
ProjectionBase::DrawAllPMTs()
{
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  for( int ipmt = 0; ipmt < rPMTList->GetPMTCount(); ipmt++ )
    {
      TVector3 pmtPos = rPMTList->GetPos( ipmt );
      const sf::Vector2<double> projPos = Project( Vector3( pmtPos ) );
      fImage->DrawHollowSquare( projPos, 
			       ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
    }    
}

void
ProjectionBase::DrawGeodesic()
{
  GeodesicSphere* geodesic = GeodesicSphere::GetInstance();
  Polyhedron polyhedron = geodesic->GetPolyhedron();
  for( int iPolygon = 0; iPolygon < polyhedron.GetNoPolygons(); iPolygon++ )
    {
      Polygon polygon = polyhedron.GetPolygon( iPolygon );
      Vector3 v1 = polygon.GetVertex(0);
      Vector3 v2 = polygon.GetVertex(1);
      Vector3 v3 = polygon.GetVertex(2);
      DrawLine( v1, v2 );
      DrawLine( v2, v3 );
      DrawLine( v3, v1 );
    }
}

void
ProjectionBase::DrawLine( Vector3 v1, 
			  Vector3 v2 )
{
  Vector3 line = v2 - v1;
  double dist = line.Mag();
  line = line.Unit();
  for( double delta = 0.0; delta < dist; delta += dist / 30.0 )
    {
      Vector3 deltaPos = line * delta + v1;
      fImage->DrawDot( Project( deltaPos ), ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
    }
}
