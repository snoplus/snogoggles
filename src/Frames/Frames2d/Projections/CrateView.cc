#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
#include <RAT/BitManip.hh>

using namespace std;

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <Viewer/CrateView.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::Frames;


const double kLocalSize = 1.0;

void 
CrateView::Initialise() 
{
  Frame::Initialise();
  sf::Rect<double> imageSize;
  imageSize.Left = 0.0; imageSize.Top = 0.0; imageSize.Width = 1.0; imageSize.Height = 1.0;
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( imageSize, Rect::eLocal ) ) );
}

void 
CrateView::Render2d( RWWrapper& renderApp,
		     const RenderState& renderState )
{
  fImage->Clear();
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
      fImage->DrawHollowSquare( sf::Vector2<double>( xPos, yPos ),
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
      int crate = RAT::BitManip::GetBits(lcn, 9, 5);
      int card = RAT::BitManip::GetBits(lcn, 5, 4);
      int channel = RAT::BitManip::GetBits(lcn, 0, 5);
      double xPos = ( crate % 10 ) * ( kCrateWidth + kXMargin ) + card * kHitWidth;
      double yPos = ( crate / 10 ) * ( kCrateHeight + kYMargin ) + channel * kHitHeight;
      fImage->DrawSquare( sf::Vector2<double>( xPos, yPos ),
			  sf::Vector2<double>( kHitWidth, kHitHeight ),
			  ColourPalette::gPalette->GetPrimaryColour( eRed ) );
    }
  fImage->Update();
  renderApp.Draw( *fImage );
}

void 
CrateView::EventLoop()
{
  while(!fEvents.empty()){
    fEvents.pop();
  }
}
