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

void
LambertProjection::Initialise()
{
  fFilledPMT.AddPoint( -1.0, sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );  
  fFilledPMT.AddPoint( 1.0, sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fFilledPMT.AddPoint( 2.0, 0.0, sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fFilledPMT.AddPoint( 1.0, -sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fFilledPMT.AddPoint( -1.0, -sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fFilledPMT.AddPoint( -2.0, 0.0, sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fFilledPMT.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 50 * 0.5 / 8500.0, 50 * 0.5 / 8500.0 ) );
  fFilledPMT.EnableFill( true );


  fOpenPMT.AddPoint( -1.0, sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );  
  fOpenPMT.AddPoint( 1.0, sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fOpenPMT.AddPoint( 2.0, 0.0, sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fOpenPMT.AddPoint( 1.0, -sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fOpenPMT.AddPoint( -1.0, -sqrt(2.0), sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fOpenPMT.AddPoint( -2.0, 0.0, sf::Color(255, 255, 255), sf::Color(255, 255, 255) );
  fOpenPMT.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 50 * 0.5 / 8500.0, 50 * 0.5 / 8500.0 ) );
  fOpenPMT.EnableFill( false );
  fOpenPMT.EnableOutline( true );
  fOpenPMT.SetOutlineThickness( 0.5 );
}

void 
LambertProjection::Initialise( ConfigurationTable& configTable )
{
  Initialise();
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
  return sf::Vector2<double>( x, y );
}

void
LambertProjection::Render2d( RWWrapper& windowApp )
{
  EventData& events = EventData::GetInstance();

  RAT::DS::EV* rEV = events.GetCurrentEV();

  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  
  for( int ipmt = 0; ipmt < rPMTList->GetCorrPMTsNumber(); ipmt++ )
    {
      const sf::Vector2<double> projPos = Project( rPMTList->GetPos( ipmt ) );
      fOpenPMT.SetPosition( projPos );
      fOpenPMT.SetColor( ColourPalette::gPalette->GetPrimaryColour( eBlack ) );
      windowApp.Draw( fOpenPMT );
    }
  for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
    {
      const sf::Vector2<double> projPos = Project( rEV->GetPMTCal( ipmt )->GetPos( rPMTList ) );
      fFilledPMT.SetPosition( projPos );
      double pmtHitTime = rEV->GetPMTCal( ipmt )->GetTime();
      if( pmtHitTime < 250.0 )
	fFilledPMT.SetColor( ColourPalette::gPalette->GetPrimaryColour( eWhite ) );
      else
	fFilledPMT.SetColor( ColourPalette::gPalette->GetColour( ( pmtHitTime - 250.0 ) / 250.0 ) );
      windowApp.Draw( fFilledPMT );
    }
}
