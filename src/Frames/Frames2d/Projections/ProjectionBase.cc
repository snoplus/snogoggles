#include <RAT/DS/Run.hh>
#include <RAT/DS/PMTProperties.hh>

#include <cmath>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/ProjectionBase.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/GeodesicSphere.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Polygon.hh>
using namespace Viewer;
using namespace Viewer::Frames;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/ChannelList.hh>

const double kPSUPRadius = 8500.0;
const double kLocalSize = 137.0 * 0.3 / kPSUPRadius;

ProjectionBase::~ProjectionBase()
{
  
}

void
ProjectionBase::PreInitialise( const ConfigurationTable* configTable )
{

}

void
ProjectionBase::PostInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> imageSize;
  imageSize.left = 0.0; imageSize.top = 0.0; imageSize.width = 1.0; imageSize.height = 1.0;
  Initialise( imageSize );
}

void
ProjectionBase::Initialise( const sf::Rect<double>& size )
{
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ), 1000, 600 );
  fImage->SetSquareSize( sf::Vector2<double>( 1.5 * kLocalSize * GetAspectRatio(), 1.5 * kLocalSize ) );

  const VBO& geodesicVBO = GeodesicSphere::GetInstance()->OutlineVBO();
  for( unsigned short i = 0; i < geodesicVBO.fIndices.size(); i+=2 )
    {
      Vertex::Data start = geodesicVBO.fVertices[ geodesicVBO.fIndices[i] ];
      Vertex::Data end = geodesicVBO.fVertices[ geodesicVBO.fIndices[i+1] ];
      ProjectGeodesicLine( sf::Vector3<double>( start.x, start.y, start.z ),
                           sf::Vector3<double>( end.x, end.y, end.z ) );
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
ProjectionBase::ProcessEvent( const RenderState& renderState )
{
  fImage->Clear();

  DrawGeodesic();
  DrawHits( renderState );
  DrawOutline();

  fImage->Update();
}

void
ProjectionBase::ProcessRun()
{
  const RIDS::ChannelList& channelList = DataSelector::GetInstance().GetChannelList();
  for( int ipmt = 0; ipmt < channelList.GetChannelCount(); ipmt++ )
    fProjectedPMTs.push_back( Project( channelList.GetPosition( ipmt ) ) );
}

void
ProjectionBase::Render2d( RWWrapper& windowApp,
			  const RenderState& renderState )
{
  windowApp.Draw( *fImage );
}

void
ProjectionBase::DrawAllPMTs()
{
  for( vector< sf::Vector2<double> >::iterator iTer = fProjectedPMTs.begin(); iTer != fProjectedPMTs.end(); iTer++ )
    fImage->DrawHollowSquare( *iTer, GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eGrey ) );
}

void
ProjectionBase::DrawGeodesic()
{
  for( vector< sf::Vector2<double> >::iterator iTer = fProjectedGeodesic.begin(); iTer != fProjectedGeodesic.end(); iTer++ )
    fImage->DrawDot( *iTer, GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eGrey ) );
}

void
ProjectionBase::ProjectGeodesicLine( sf::Vector3<double> vv1, 
                                     sf::Vector3<double> vv2 )
{
  TVector3 v1( vv1.x, vv1.y, vv1.z );
  TVector3 v2( vv2.x, vv2.y, vv2.z );
  TVector3 line = v2 - v1;
  double dist = line.Mag();
  line = line.Unit();
  for( double delta = 0.0; delta < dist; delta += dist / 30.0 )
    {
      const TVector3 deltaPos = line * delta + v1;
      fProjectedGeodesic.push_back( Project( sf::Vector3<double>( deltaPos.x(), deltaPos.y(), deltaPos.z() ) ) );
    }
}

void
ProjectionBase::DrawHits( const RenderState& renderState )
{
  const vector<RIDS::Channel>& hits = DataSelector::GetInstance().GetData( renderState.GetDataSource(), renderState.GetDataType() );
  for( vector<RIDS::Channel>::const_iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      const sf::Vector2<double> projPos = fProjectedPMTs[iTer->GetID()];
      const double data = iTer->GetData();
      if( data == 0.0 )
        continue;
      fImage->DrawSquare( projPos, renderState.GetDataColour( data ) );
    }
}

