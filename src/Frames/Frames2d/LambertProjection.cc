#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>

#include <SFML/Graphics.hpp>

#include <Viewer/LambertProjection.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
using namespace Viewer;
using namespace Viewer::Frames;

#include <iostream>
using namespace std;

const double kPSUPRadius = 8500.0;

void
LambertProjection::Initialise()
{
  fProjectArea = sf::Rect<double>( 0.1, 0.0, 0.9, 0.9 );
  fFilledPMT = sf::Shape::Circle( 0.0, 0.0, 0.5, sf::Color(255, 255, 255) );
  fFilledPMT.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 137.0 * 0.5 / kPSUPRadius * fProjectArea.Width, 137.0 * 0.5 / kPSUPRadius * fProjectArea.Height ) );
  fFilledPMT.EnableFill( true );


  fOpenPMT= sf::Shape::Circle( 0.0, 0.0, 0.5, sf::Color(255, 255, 255), 0.5, sf::Color(255, 255, 255) );
  fOpenPMT.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 100.0 * 0.5 / kPSUPRadius * fProjectArea.Width, 100.0 * 0.5 / kPSUPRadius * fProjectArea.Height ) );
  fOpenPMT.EnableFill( false );
  fOpenPMT.EnableOutline( true );
  fOpenPMT.SetOutlineThickness( 0.5 );
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
LambertProjection::Project( TVector3 pmtPos )
{
  pmtPos = pmtPos.Unit();
  const double x = sqrt( 2 / ( 1 - pmtPos.Z() ) ) * pmtPos.X() / 4.0 + 0.5; // Projected circle radius is 2 thus diameter 4
  const double y = sqrt( 2 / ( 1 - pmtPos.Z() ) ) * pmtPos.Y() / 4.0 + 0.5; // +0.5 such that x,y E [0, 1)
  return sf::Vector2<double>( fProjectArea.Left + x * fProjectArea.Width, fProjectArea.Top + y * fProjectArea.Height );
}

void
LambertProjection::Render2d( RWWrapper& windowApp )
{
  const double surfaceDist = 137.0 / kPSUPRadius;
  EventData& events = EventData::GetInstance();

  RAT::DS::EV* rEV = events.GetCurrentEV();

  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  
  for( int ipmt = 0; ipmt < rPMTList->GetPMTCount(); ipmt++ )
    {
      TVector3 pmtPos = rPMTList->GetPos( ipmt );
      const sf::Vector2<double> projPos = Project( pmtPos );
      fOpenPMT.SetPosition( projPos );
      fOpenPMT.SetColor( ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
      windowApp.Draw( fOpenPMT );
    }
  for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
    {
      const sf::Vector2<double> projPos = Project( rPMTList->GetPos( rEV->GetPMTCal( ipmt )->GetID() ) );
      fFilledPMT.SetPosition( projPos );
      double pmtHitTime = rEV->GetPMTCal( ipmt )->GetTime();
      if( pmtHitTime < 250.0 )
	fFilledPMT.SetColor( ColourPalette::gPalette->GetPrimaryColour( eWhite ) );
      else
	fFilledPMT.SetColor( ColourPalette::gPalette->GetColour( ( 500.0 - pmtHitTime ) / 250.0 ) );
      windowApp.Draw( fFilledPMT );
    }
}
