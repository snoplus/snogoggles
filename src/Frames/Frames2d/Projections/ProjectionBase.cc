#include <RAT/DS/Run.hh>
#include <RAT/DS/PMTProperties.hh>

#include <TVector3.h>

#include <cmath>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/ProjectionBase.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/GeodesicSphere.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/PMTHit.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Polygon.hh>
using namespace Viewer;
using namespace Viewer::Frames;

const double kPSUPRadius = 8500.0;
const double kLocalSize = 137.0 * 0.3 / kPSUPRadius;

ProjectionBase::~ProjectionBase()
{
  
}

void
ProjectionBase::Initialise()
{
  Frame::Initialise();
  sf::Rect<double> imageSize;
  imageSize.Left = 0.0; imageSize.Top = 0.0; imageSize.Width = 1.0; imageSize.Height = 1.0;
  Initialise( imageSize );
}

void
ProjectionBase::Initialise( const sf::Rect<double>& size )
{
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  fImage->SetSquareSize( sf::Vector2<double>( 1.5 * kLocalSize, 1.5 * kLocalSize ) );
  // Firstly make the vector of PMT positions
  DataStore& events = DataStore::GetInstance();
  RAT::DS::PMTProperties* rPMTList = events.GetRun().GetPMTProp();
  for( int ipmt = 0; ipmt < rPMTList->GetPMTCount(); ipmt++ )
    fProjectedPMTs.push_back( Project( Vector3( rPMTList->GetPos( ipmt ) ) ) );
  // Secondly make the vector of geodesic dots
  GeodesicSphere* geodesic = GeodesicSphere::GetInstance();
  const Polyhedron& polyhedron = geodesic->GetPolyhedron();
  for( int iPolygon = 0; iPolygon < polyhedron.GetNoPolygons(); iPolygon++ )
    {
      const Polygon& polygon = polyhedron.GetPolygon( iPolygon );
      Vector3 v1 = polygon.GetVertex(0);
      Vector3 v2 = polygon.GetVertex(1);
      Vector3 v3 = polygon.GetVertex(2);
      ProjectGeodesicLine( v1, v2 );
      ProjectGeodesicLine( v2, v3 );
      ProjectGeodesicLine( v3, v1 );
    }
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
  DrawHits( renderState );

  fImage->Update();
  windowApp.Draw( *fImage );
}

void
ProjectionBase::DrawAllPMTs()
{
  for( vector< sf::Vector2<double> >::iterator iTer = fProjectedPMTs.begin(); iTer != fProjectedPMTs.end(); iTer++ )
    fImage->DrawHollowSquare( *iTer, ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
}

void
ProjectionBase::DrawGeodesic()
{
  for( vector< sf::Vector2<double> >::iterator iTer = fProjectedGeodesic.begin(); iTer != fProjectedGeodesic.end(); iTer++ )
    fImage->DrawDot( *iTer, ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
}

void
ProjectionBase::ProjectGeodesicLine( Vector3 v1, 
				     Vector3 v2 )
{
  Vector3 line = v2 - v1;
  double dist = line.Mag();
  line = line.Unit();
  for( double delta = 0.0; delta < dist; delta += dist / 30.0 )
    {
      Vector3 deltaPos = line * delta + v1;
      fProjectedGeodesic.push_back( Project( deltaPos ) );
    }
}

void
ProjectionBase::DrawHits( const RenderState& renderState )
{
  DataStore& events = DataStore::GetInstance();
  const RIDS::Event& event = events.GetCurrentEvent();
  vector<RIDS::PMTHit> hits = event.GetHitData( renderState.GetDataSource() );
  for( vector<RIDS::PMTHit>::iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      const double data = iTer->GetData( renderState.GetDataType() );
      const sf::Vector2<double> projPos = fProjectedPMTs[iTer->GetLCN()];
      fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( ( data - renderState.GetScalingMin() ) / 
                                                                       ( renderState.GetScalingMax() - renderState.GetScalingMin() ) ) );
    }
}

