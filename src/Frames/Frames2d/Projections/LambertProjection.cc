#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>

#include <TVector3.h>

#include <SFML/Graphics.hpp>

#include <Viewer/LambertProjection.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/MapArea.hh>
#include <Viewer/GeodesicSphere.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Polygon.hh>
#include <Viewer/TimeAxis.hh>
using namespace Viewer;
using namespace Viewer::Frames;

#include <iostream>
using namespace std;

const double kPSUPRadius = 8500.0;
const double kLocalSize = 137.0 * 0.3 / kPSUPRadius;

void
LambertProjection::Initialise()
{
  fProjectArea = sf::Rect<double>( 0.0, 0.0, 0.8, 0.9 );
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( fProjectArea );
  fHitInfo.SetRect( sf::Rect<double>( 0.8, 0.0, 0.2, 0.2 ) );
}

void 
LambertProjection::LoadConfiguration( ConfigurationTable& configTable )
{
 
}

void
LambertProjection::SaveConfiguration( ConfigurationTable& configTable )
{

}

void 
LambertProjection::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}

sf::Vector2<double>
LambertProjection::Project( Vector3 pmtPos )
{
  pmtPos = pmtPos.Unit();
  const double x = sqrt( 2 / ( 1 - pmtPos.z ) ) * pmtPos.x / 4.0 + 0.5; // Projected circle radius is 2 thus diameter 4
  const double y = sqrt( 2 / ( 1 - pmtPos.z ) ) * pmtPos.y / 4.0 + 0.5; // +0.5 such that x,y E [0, 1)
  return sf::Vector2<double>( x, y );
}

void
LambertProjection::Render2d( RWWrapper& windowApp )
{
  Rect localRect;
  localRect.SetFromLocalRect( fProjectArea, fFrameRect );
  fImage.Clear( localRect );
  fImage.SetSquareSize( sf::Vector2<double>( 1.5 * kLocalSize, 1.5 * kLocalSize ) );
  localRect.SetFromLocalRect( fAxisArea, fFrameRect );

  
  DrawGeodesic();
  DrawHits();

  fHitInfo.Render( windowApp );
  windowApp.Draw( &fImage );
}

void
LambertProjection::DrawHits()
{
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  sf::Vector2<double> mapPosition = fMapArea->GetPosition();

  for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
    {
      RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
      const sf::Vector2<double> projPos = Project( Vector3( rPMTList->GetPos( rPMTCal->GetID() ) ) );
      double pmtHitTime = rPMTCal->GetTime();
      fImage.DrawSquare( projPos, 
			 ColourPalette::gPalette->GetColour( TimeAxis::ScaleTime( pmtHitTime ) ) );
      
      const double distToMouse2 = ( projPos.x - mapPosition.x ) * ( projPos.x - mapPosition.x ) + 
	( projPos.y - mapPosition.y ) * ( projPos.y - mapPosition.y );
      if( distToMouse2 < kLocalSize * kLocalSize )
	fHitInfo.AddPMT( rPMTCal );
    }
}

void
LambertProjection::DrawAllPMTs()
{
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  for( int ipmt = 0; ipmt < rPMTList->GetPMTCount(); ipmt++ )
    {
      TVector3 pmtPos = rPMTList->GetPos( ipmt );
      const sf::Vector2<double> projPos = Project( Vector3( pmtPos ) );
      fImage.DrawHollowSquare( projPos, 
			       ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
    }    
}

void
LambertProjection::DrawGeodesic()
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
LambertProjection::DrawLine( Vector3 v1, Vector3 v2 )
{
  Vector3 line = v2 - v1;
  double dist = line.Mag();
  line = line.Unit();
  for( double delta = 0.0; delta < dist; delta += dist / 30.0 )
    {
      Vector3 deltaPos = line * delta + v1;
      fImage.DrawDot( Project( deltaPos ), ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
    }
}
