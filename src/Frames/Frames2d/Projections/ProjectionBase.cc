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
#include <Viewer/RenderState.hh>
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
  EventData& events = EventData::GetInstance();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
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
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();

  switch( renderState.GetDataSource() )
    {
    case RenderState::eUnCal:
      switch( renderState.GetDataType() )
        {
        case RenderState::eTAC:  
	  for( int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
	    {
	      RAT::DS::PMTUnCal* rPMTUnCal = rEV->GetPMTUnCal( ipmt );
	      const sf::Vector2<double> projPos = fProjectedPMTs[rPMTUnCal->GetID()];
	      double tac = rEV->GetPMTUnCal( ipmt )->GetTime();
	      fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( tac / 4000.0 ) );
	    }
	  break;
	case RenderState::eQHL:
          for( int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
            {
	      RAT::DS::PMTUnCal* rPMTUnCal = rEV->GetPMTUnCal( ipmt );
              const sf::Vector2<double> projPos = fProjectedPMTs[rPMTUnCal->GetID()];
              double qhl = rEV->GetPMTUnCal( ipmt )->GetsQHL();
              fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( qhl / 4500.0 ) );
            }
          break;
	case RenderState::eQHS:
          for( int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
            {
	      RAT::DS::PMTUnCal* rPMTUnCal = rEV->GetPMTUnCal( ipmt );
              const sf::Vector2<double> projPos = fProjectedPMTs[rPMTUnCal->GetID()];
              double qhs = rEV->GetPMTUnCal( ipmt )->GetsQHS();
              fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( qhs / 4500.0 ) );
            }
          break;
	case RenderState::eQLX:
          for( int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
            {
	      RAT::DS::PMTUnCal* rPMTUnCal = rEV->GetPMTUnCal( ipmt );
              const sf::Vector2<double> projPos = fProjectedPMTs[rPMTUnCal->GetID()];
              double qlx = rEV->GetPMTUnCal( ipmt )->GetsQLX();
              fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( qlx / 1400.0 ) );
            }
          break;
	}
      break;
    case RenderState::eCal:
      switch( renderState.GetDataType() )
        {
        case RenderState::eTAC:  
	  for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
	    {
	      RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
	      const sf::Vector2<double> projPos = fProjectedPMTs[rPMTCal->GetID()];
	      double tac = rEV->GetPMTCal( ipmt )->GetTime();
	      fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( tac / 500.0 ) );
	    }
	  break;
	case RenderState::eQHL:
          for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
            {
	      RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
              const sf::Vector2<double> projPos = fProjectedPMTs[rPMTCal->GetID()];
              double qhl = rEV->GetPMTCal( ipmt )->GetsQHL();
              fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( qhl / 4000.0 ) );
            }
          break;
	case RenderState::eQHS:
          for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
            {
	      RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
              const sf::Vector2<double> projPos = fProjectedPMTs[rPMTCal->GetID()];
              double qhs = rEV->GetPMTCal( ipmt )->GetsQHS();
              fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( qhs / 4000.0 ) );
            }
          break;
	case RenderState::eQLX:
          for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
            {
	      RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
              const sf::Vector2<double> projPos = fProjectedPMTs[rPMTCal->GetID()];
              double qlx = rEV->GetPMTCal( ipmt )->GetsQLX();
              fImage->DrawSquare( projPos, ColourPalette::gPalette->GetColour( qlx / 1000.0 ) );
            }
          break;
	}
      break;
    }
}

