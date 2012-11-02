#include <TVector3.h>
#include <TVector2.h>

#include <cmath>
using namespace std;

#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ProjectionImage.hh>
using namespace Viewer;
using namespace Viewer::Frames;

  const double a = 1.0 / 5.5;
  const double b = a * sqrt( 3.0 ) / 2.0;

  const TVector2 A12a = TVector2( a / 2.0, 0.0 );
  const TVector2 A12b = TVector2( 3.0 * a / 2.0, 0.0 );
  const TVector2 A12c = TVector2( 5.0 * a / 2.0, 0.0 );
  const TVector2 A12d = TVector2( 7.0 *a / 2.0, 0.0 );
  const TVector2 A12e = TVector2( 9.0 * a / 2.0, 0.0 );
  const TVector2 A2a = TVector2( 0.0, b );
  const TVector2 A2b = TVector2( 5.0 * a, b );
  const TVector2 A17a = TVector2( a / 2.0 , 2.0 * b );
  const TVector2 A17b = TVector2( 11.0 * a / 2.0 , 2.0 * b );
  const TVector2 A51a = TVector2( a, 3.0 * b );
  const TVector2 A51b = TVector2( 2.0 * a, 3.0 * b );
  const TVector2 A51c = TVector2( 3.0 * a, 3.0 * b );
  const TVector2 A51d = TVector2( 4.0 * a, 3.0 * b );
  const TVector2 A51e = TVector2( 5.0 * a, 3.0 * b );
  const TVector2 A27 = TVector2( 4.0 * a, b );
  const TVector2 A46 = TVector2( 3.0 * a, b );
  const TVector2 A31 = TVector2( 2.0 * a, b );
  const TVector2 A6 = TVector2( a, b );
  const TVector2 A37 = TVector2( 9.0 * a / 2.0 , 2.0 * b );
  const TVector2 A33 = TVector2( 3.0 * a / 2.0 , 2.0 * b );
  const TVector2 A58 = TVector2( 5.0 * a / 2.0 , 2.0 * b );
  const TVector2 A54 = TVector2( 7.0 * a / 2.0 , 2.0 * b );

void
IcosahedralProjection::PostInitialise( const ConfigurationTable* configTable )
{
  ProjectionMapArea::PostInitialise( configTable );
  ProjectOutline( A2a, A12a );
  ProjectOutline( A6, A12a );
  ProjectOutline( A2b, A12e );
  ProjectOutline( A27, A12e );
  ProjectOutline( A27, A12d );
  ProjectOutline( A46, A12d );
  ProjectOutline( A46, A12c );
  ProjectOutline( A31, A12c );
  ProjectOutline( A31, A12b );
  ProjectOutline( A6, A12b );
  ProjectOutline( A51a, A17a );
  ProjectOutline( A2a, A17a );
  ProjectOutline( A2b, A17b );
  ProjectOutline( A51e, A17b );
  ProjectOutline( A51e, A37 );
  ProjectOutline( A51d, A37 );
  ProjectOutline( A51d, A54 );
  ProjectOutline( A51c, A54 );
  ProjectOutline( A51c, A58 );
  ProjectOutline( A51b, A58 );
  ProjectOutline( A51b, A33 );
  ProjectOutline( A33, A51a );
}

void
IcosahedralProjection::ProjectOutline( TVector2 v1,
                                        TVector2 v2 )
{
  TVector2 line = v2 - v1;
  double dist = line.Mod();
  line = line.Unit();
  for( double delta = 0.0; delta < dist; delta += dist / 60.0 )
    {
      TVector2 deltaPos = line * delta + v1;
      fProjectedOutline.push_back( sf::Vector2<double>( deltaPos.X(), 2.0 * deltaPos.Y() ) );
    }
}

void
IcosahedralProjection::DrawOutline()
{
  for( vector< sf::Vector2<double> >::iterator iTer = fProjectedOutline.begin(); iTer != fProjectedOutline.end(); iTer++ )
    fImage->DrawDot( *iTer, GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eGrey ) );
}

TVector2
TransformCoord(
               const TVector3& V1,
               const TVector3& V2,
               const TVector3& V3,
               const TVector2& A1,
               const TVector2& A2,
               const TVector2& A3,
               const TVector3& P )
{
  TVector3 xV = V2 - V1;
  TVector3 yV = ( ( V3 - V1 ) + ( V3 - V2 ) ) * 0.5;
  TVector3 zV = xV.Cross( yV ).Unit();

  double planeD = V1.Dot( zV );

  double t = planeD / P.Dot( zV );

  TVector3 localP = t*P - V1;

  TVector2 xA = A2 - A1;
  TVector2 yA = ( ( A3 - A1 ) +( A3 - A2 ) )  * 0.5;

  double convUnits = xA.Mod() / xV.Mag();

  TVector2 result;
  result = localP.Dot( xV.Unit() ) * xA.Unit() * convUnits;
  result += localP.Dot( yV.Unit() ) * yA.Unit() * convUnits + A1;
  return result;
}

TVector2
ToSpherical(
            const TVector3& P )
{
  double theta = acos( P.z() / P.Mag() );
  double phi = atan2( P.y(), P.x() );
  return TVector2( theta, phi );
}

sf::Vector2<double>
IcosahedralProjection::Project( Vector3 pmtPos )
{
  pmtPos = pmtPos.Unit();
  TVector3 pointOnSphere( pmtPos.x, pmtPos.y, pmtPos.z );
  pointOnSphere.RotateX( -45.0 );
  // From http://www.rwgrayprojects.com/rbfnotes/polyhed/PolyhedraData/Icosahedralsahedron/Icosahedralsahedron.pdf
  const double t = ( 1.0 + sqrt( 5.0 ) ) / 2.0;

  const TVector3 V2 = TVector3( t * t, 0.0, t * t * t ).Unit();
  const TVector3 V6 = TVector3( -t * t, 0.0, t * t * t ).Unit();
  const TVector3 V12 = TVector3( 0.0, t * t * t, t * t ).Unit();
  const TVector3 V17 = TVector3( 0.0, -t * t * t, t * t ).Unit();
  const TVector3 V27 = TVector3( t * t * t, t * t, 0.0 ).Unit();
  const TVector3 V31 = TVector3( -t * t * t, t * t, 0.0 ).Unit();
  const TVector3 V33 = TVector3( -t * t * t, -t * t, 0.0 ).Unit();
  const TVector3 V37 = TVector3( t * t * t, -t * t, 0.0 ).Unit();
  const TVector3 V46 = TVector3( 0.0, t * t * t, -t * t ).Unit();
  const TVector3 V51 = TVector3( 0.0, -t * t * t, -t * t ).Unit();
  const TVector3 V54 = TVector3( t * t, 0.0, -t * t * t ).Unit();
  const TVector3 V58 = TVector3( -t * t, 0.0, -t * t * t ).Unit();
  // Faces {{ 2, 6, 17}, { 2, 12, 6}, { 2, 17, 37}, { 2, 37, 27}, { 2, 27, 12}, {37, 54, 27},
  // {27, 54, 46}, {27, 46, 12}, {12, 46, 31}, {12, 31, 6}, { 6, 31, 33}, { 6, 33, 17},
  // {17, 33, 51}, {17, 51, 37}, {37, 51, 54}, {58, 54, 51}, {58, 46, 54}, {58, 31, 46},
  // {58, 33, 31}, {58, 51, 33}}
  vector<TVector3> IcosahedralCentres;
  IcosahedralCentres.push_back( ( V2 + V6 + V17 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V2 + V12 + V6 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V2 + V17 + V37 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V2 + V37 + V27 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V2 + V27 + V12 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V37 + V54 + V27 ) * ( 1.0 / 3.0 ) );

  IcosahedralCentres.push_back( ( V27 + V54 + V46 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V27 + V46 + V12 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V12 + V46 + V31 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V12 + V31 + V6 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V6 + V31 + V33 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V6 + V33 + V17 ) * ( 1.0 / 3.0 ) );

  IcosahedralCentres.push_back( ( V17 + V33 + V51 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V17 + V51 + V37 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V37 + V51 + V54 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V58 + V54 + V51 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V58 + V46 + V54 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V58 + V31 + V46 ) * ( 1.0 / 3.0 ) );

  IcosahedralCentres.push_back( ( V58 + V33 + V31 ) * ( 1.0 / 3.0 ) );
  IcosahedralCentres.push_back( ( V58 + V51 + V33 ) * ( 1.0 / 3.0 ) );

  vector<double> distFromCentre;
  unsigned int uLoop;
  for( uLoop = 0; uLoop < IcosahedralCentres.size(); uLoop++ )
    distFromCentre.push_back( ( IcosahedralCentres[uLoop] - pointOnSphere ).Mag() );
  const int face = min_element( distFromCentre.begin(), distFromCentre.end() ) - distFromCentre.begin() + 1;

  TVector2 resultPosition;
  switch(face)
    {
    case 1://{ 2, 6, 17}
      resultPosition = TransformCoord( V2, V6, V17, A2a, A6, A17a, pointOnSphere );
      break;
    case 2://{ 2, 12, 6}
      resultPosition = TransformCoord( V2, V12, V6, A2a, A12a, A6, pointOnSphere );
      break;
    case 3://{ 2, 17, 37}
      resultPosition = TransformCoord( V2, V17, V37, A2b, A17b, A37, pointOnSphere );
      break;
    case 4://{ 2, 37, 27}
      resultPosition = TransformCoord( V2, V37, V27, A2b, A37, A27, pointOnSphere );
      break;
    case 5://{ 2, 27, 12}
      resultPosition = TransformCoord( V2, V27, V12, A2b, A27, A12e, pointOnSphere );
      break;
    case 6://{37, 54, 27}
      resultPosition = TransformCoord( V37, V54, V27, A37, A54, A27, pointOnSphere );
      break;
    case 7://{27, 54, 46}
      resultPosition = TransformCoord( V27, V54, V46, A27, A54, A46, pointOnSphere );
      break;
    case 8://{27, 46, 12}
      resultPosition = TransformCoord( V27, V46, V12, A27, A46, A12d, pointOnSphere );
      break;
    case 9://{12, 46, 31}
      resultPosition = TransformCoord( V12, V46, V31, A12c, A46, A31, pointOnSphere );
      break;
    case 10://{12, 31, 6}
      resultPosition = TransformCoord( V12, V31, V6, A12b, A31, A6, pointOnSphere );
      break;
    case 11://{ 6, 31, 33}
      resultPosition = TransformCoord( V6, V31, V33, A6, A31, A33, pointOnSphere );
      break;
    case 12://{ 6, 33, 17}
      resultPosition = TransformCoord( V6, V33, V17, A6, A33, A17a, pointOnSphere );
      break;
    case 13://{17, 33, 51}
      resultPosition = TransformCoord( V17, V33, V51, A17a, A33, A51a, pointOnSphere );
      break;
    case 14://{17, 51, 37}
      resultPosition = TransformCoord( V17, V51, V37, A17b, A51e, A37, pointOnSphere );
      break;
    case 15://{37, 51, 54}
      resultPosition = TransformCoord( V37, V51, V54, A37, A51d, A54, pointOnSphere );
      break;
    case 16://{58, 54, 51}
      resultPosition = TransformCoord( V58, V54, V51, A58, A54, A51c, pointOnSphere );
      break;
    case 17://{58, 46, 54}
      resultPosition = TransformCoord( V58, V46, V54, A58, A46, A54, pointOnSphere );
      break;
    case 18://{58, 31, 46}
      resultPosition = TransformCoord( V58, V31, V46, A58, A31, A46, pointOnSphere );
      break;
    case 19://{58, 33, 31}
      resultPosition = TransformCoord( V58, V33, V31, A58, A33, A31, pointOnSphere );
      break;
    case 20://{58, 51, 33}
      resultPosition = TransformCoord( V58, V51, V33, A58, A51b, A33, pointOnSphere );
      break;
    }
  return sf::Vector2<double>( resultPosition.X(), 2.0 * resultPosition.Y() );
}
