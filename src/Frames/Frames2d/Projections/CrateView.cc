//C++ includes
#include <iostream>
//RAT includes
#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
//SFML includes
#include <SFML/Graphics.hpp>
//Viewer includes
#include <Viewer/CrateView.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/TimeAxis.hh>
#include <Viewer/MapArea.hh>

using namespace Viewer;
using namespace Viewer::Frames;
using namespace std;

const double kLocalSize = 1.0;

// Required as the BitManip file is hard to include, TODO fix the BitManip file
int GetBitsTemp(int arg, int loc, int n)
{
  int shifted = arg >> loc;
  // Select the first (least significant) n of those bits
  int mask = ((ULong64_t)1 << n) - 1;
  int value = shifted & mask;
  return value;
}

void CrateView::Initialise() {
  fProjectArea = sf::Rect<double>(0.1,0.0,0.8,0.9);
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( fProjectArea );
  fInfoText.SetBoundingRect( sf::Rect<double>( 0.0, 0.9, 1.0, 0.1 ) );
  fInfoText.SetColor( ColourPalette::gPalette->GetPrimaryColour( eBlack ) );
}

void CrateView::Render2d(RWWrapper& windowApp){

  Rect projection;
  projection.SetFromLocalRect(fProjectArea,fFrameRect);
  fImage.Clear(projection);
  const double kXMargin     = 0.01;
  const double kYMargin     = 0.01;
  const double kCrateWidth  = 1.0 / 10.0 - kXMargin; // 10 Columns
  const double kCrateHeight = 1.0 / 2.0 - kYMargin; // 2 Rows
  const double kHitWidth    = kCrateWidth  / 16.0; // There are 16 cards
  const double kHitHeight   = kCrateHeight / 32.0; // There are 32 channels

  // Draw the crate outlines first
  for( int iCrate = 0; iCrate < 20; iCrate++ ) // 20 Crates
    {
      double xPos = ( iCrate % 10 ) * ( kCrateWidth + kXMargin );
      double yPos = ( iCrate / 10 ) * ( kCrateHeight + kYMargin );
      fImage.DrawHollowSquare( sf::Vector2<double>( xPos, yPos ),
			       sf::Vector2<double>( kCrateWidth, kCrateHeight ),
			       ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
    }
  // Now draw the hits
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  for( int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
    {
      double pmtHitTime = rEV->GetPMTCal(ipmt)->GetTime();
      int lcn = rEV->GetPMTCal(ipmt)->GetID();
      int crate = GetBitsTemp(lcn, 9, 5);
      int card = GetBitsTemp(lcn, 5, 4);
      int channel = GetBitsTemp(lcn, 0, 5);
      double xPos = ( crate % 10 ) * ( kCrateWidth + kXMargin ) + card * kHitWidth;
      double yPos = ( crate / 10 ) * ( kCrateHeight + kYMargin ) + channel * kHitHeight;
      fImage.DrawSquare( sf::Vector2<double>( xPos, yPos ),
			 sf::Vector2<double>( kHitWidth, kHitHeight ),
			 ColourPalette::gPalette->GetColour( TimeAxis::ScaleTime( pmtHitTime ) ) );
    }
  windowApp.Draw(&fImage);
}

void CrateView::Render3d(){
}

void CrateView::EventLoop(){
  while(!fEvents.empty()){
    fEvents.pop();
  }
}

void CrateView::SaveConfiguration(ConfigurationTable& configTable){
  // I think nothing goes in here...
}

