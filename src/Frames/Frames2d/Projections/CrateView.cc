#include <RAT/BitManip.hh>

#include <vector>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/CrateView.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/PMTHit.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/HitInfo.hh>
#include <Viewer/MapArea.hh>
using namespace Viewer;
using namespace Viewer::Frames;


const double kLocalSize = 1.0;
const double kXMargin     = 0.01;
const double kYMargin     = 0.01;
const double kCrateWidth  = 1.0 / 10.0 - kXMargin; // 10 Columns
const double kCrateHeight = 1.0 / 2.0 - kYMargin; // 2 Rows
const double kHitWidth    = kCrateWidth  / 16.0; // There are 16 cards
const double kHitHeight   = kCrateHeight / 32.0; // There are 32 channels

CrateView::~CrateView()
{
  delete fImage, fHitInfo;
}

void 
CrateView::PreInitialise( const ConfigurationTable* configTable ) 
{
  sf::Rect<double> size;
  size.Left = 0.0; size.Top = 0.0; size.Width = 1.0; size.Height = 0.95;
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( size );
  size.Left = 0.0; size.Top = 0.95; size.Width = 0.9; size.Height = 0.05;
  fHitInfo = new HitInfo( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ), true );
  fPMTofInterest = -1;
}

void 
CrateView::Render2d( RWWrapper& renderApp,
		     const RenderState& renderState )
{
  fImage->Clear();
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
  fPMTofInterest = -1;
  DrawPMTs( renderState );
  fImage->Update();
  renderApp.Draw( *fImage );

  if( fPMTofInterest != -1 )
    fHitInfo->Render( renderApp, renderState, fPMTofInterest );
}

void 
CrateView::EventLoop()
{
  while( !fEvents.empty() )
    {
      // Only one event type is likely
      fMousePos = fMapArea->GetPosition();
      fEvents.pop();
    }
}

void
CrateView::DrawPMT( const int lcn,
		    const Colour& colour )
{
  int crate = RAT::BitManip::GetBits(lcn, 9, 5);
  int card = RAT::BitManip::GetBits(lcn, 5, 4);
  int channel = RAT::BitManip::GetBits(lcn, 0, 5);
  double xPos = ( crate % 10 ) * ( kCrateWidth + kXMargin ) + card * kHitWidth;
  double yPos = ( crate / 10 ) * ( kCrateHeight + kYMargin ) + channel * kHitHeight;
  fImage->DrawSquare( sf::Vector2<double>( xPos, yPos ),
                      sf::Vector2<double>( kHitWidth, kHitHeight ),
                      colour );
  // Draw the PMT info as well?
  const double closeRadius = 0.005;
  if( fabs( xPos - fMousePos.x ) < closeRadius && fabs( yPos - fMousePos.y ) < closeRadius )
    fPMTofInterest = lcn;
  
}

void 
CrateView::DrawPMTs( const RenderState& renderState )
{
  vector<RIDS::PMTHit> hits = DataStore::GetInstance().GetHitData( renderState.GetDataSource() );
  for( vector<RIDS::PMTHit>::iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      const double data = iTer->GetData( renderState.GetDataType() );
      DrawPMT( iTer->GetLCN(), ColourPalette::gPalette->GetColour( ( data - renderState.GetScalingMin() ) /
                                                                   ( renderState.GetScalingMax() - renderState.GetScalingMin() ) ) );
    }
}
