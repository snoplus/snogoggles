#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>

#include <SFML/Graphics.hpp>

#include <Viewer/LambertProjection.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/MapArea.hh>
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
  fAxisArea = sf::Rect<double>( 0.85, 0.0, 0.1, 0.9 );
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( fProjectArea );
  fInfoText.SetBoundingRect( sf::Rect<double>( 0.0, 0.9, 1.0, 0.1 ) );
  fInfoText.SetColor( ColourPalette::gPalette->GetPrimaryColour( eBlack ) );
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
  fTimeAxis.Clear( localRect );

  sf::Vector2<double> mapPosition = fMapArea->GetPosition();

  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  
  for( int ipmt = 0; ipmt < rPMTList->GetPMTCount(); ipmt++ )
    {
      TVector3 pmtPos = rPMTList->GetPos( ipmt );
      const sf::Vector2<double> projPos = Project( pmtPos );
      fImage.DrawHollowSquare( projPos, 
			       ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
    }
  stringstream infoText;
  for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
    {
      RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
      const sf::Vector2<double> projPos = Project( rPMTList->GetPos( rPMTCal->GetID() ) );
      double pmtHitTime = rPMTCal->GetTime();
      fImage.DrawSquare( projPos, 
			 ColourPalette::gPalette->GetColour( TimeAxis::ScaleTime( pmtHitTime ) ) );
      const double distToMouse2 = ( projPos.x - mapPosition.x ) * ( projPos.x - mapPosition.x ) + 
	( projPos.y - mapPosition.y ) * ( projPos.y - mapPosition.y );
      if( distToMouse2 < kLocalSize * kLocalSize )
	infoText << rPMTCal->GetID() << " Time: " << rPMTCal->GetTime() << " Charge: " << rPMTCal->GetCharge() << endl;
    }
  fTimeAxis.Fill();
  fInfoText.SetString( infoText.str() );

  windowApp.Draw( fInfoText );
  windowApp.Draw( &fTimeAxis );
  windowApp.Draw( &fImage );
}
