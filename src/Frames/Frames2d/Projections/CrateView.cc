#include <vector>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/CrateView.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/HitInfo.hh>
#include <Viewer/MapArea.hh>
#include <Viewer/BitManip.hh>
using namespace Viewer;
using namespace Viewer::Frames;
#include <Viewer/RIDS/Channel.hh>

const int kCrateWidth = 17; // 16 cards + 1 border
const int kCrateHeight = 33; // 32 channels + 1 border
const int kMargin = 2; // 2 Pixel margin
const int kFullWidth = 10 * kCrateWidth + 9 * kMargin + 1;
const int kFullHeight = 2 * kCrateHeight + kMargin + 1;

CrateView::~CrateView()
{
  delete fImage, fHitInfo;
}

void 
CrateView::PreInitialise( const ConfigurationTable* configTable ) 
{
  sf::Rect<double> size;
  size.left = 0.0; size.top = 0.0; size.width = 1.0; size.height = 0.95;
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ),
                                kFullWidth, kFullHeight );
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( size );
  size.left = 0.0; size.top = 0.95; size.width = 1.0; size.height = 0.05;
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
      int xPos = ( iCrate % 10 ) * ( kCrateWidth + kMargin );
      int yPos = ( iCrate / 10 ) * ( kCrateHeight + kMargin );

      fImage->DrawHollowSquare( sf::Vector2<int>( xPos, yPos ),
                                sf::Vector2<int>( kCrateWidth, kCrateHeight ),
                                GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eGrey ),
                                1 );
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
  int crate = BitManip::GetBits(lcn, 9, 5); 
  int card = BitManip::GetBits(lcn, 5, 4);
  int channel = 31 - BitManip::GetBits(lcn, 0, 5);// Inverse the vertical position of the channels
  int xPos = ( crate % 10 ) * ( kCrateWidth + kMargin ) + card + 1; 
  int yPos = ( crate / 10 ) * ( kCrateHeight + kMargin ) + channel + 1;
  fImage->DrawSquare( sf::Vector2<int>( xPos, yPos ),
                      sf::Vector2<int>( 0, 0 ), // Size is just the pixel, no extra
                      colour );
  // Draw the PMT info as well, first calculate the mouse equivalent position of the pixel
  const double mouseXPos = static_cast<double>( xPos ) / static_cast<double>( kFullWidth );
  const double mouseXWidth = 1.0 / static_cast<double>( kFullWidth );
  const double mouseYPos = static_cast<double>( yPos ) / static_cast<double>( kFullHeight );
  const double mouseYHeight = 1.0 / static_cast<double>( kFullHeight );
  if( fMousePos.x > mouseXPos && ( fMousePos.x - mouseXPos ) < mouseXWidth && 
      fMousePos.y > mouseYPos && ( fMousePos.y - mouseYPos ) < mouseYHeight )
    fPMTofInterest = lcn;  
}

void 
CrateView::DrawPMTs( const RenderState& renderState )
{
  const vector<RIDS::Channel> hits = DataStore::GetInstance().GetChannelData( renderState.GetDataSource(), renderState.GetDataType() );
  for( vector<RIDS::Channel>::const_iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      const double data = iTer->GetData();
      if( data == 0.0 )
        continue;
      DrawPMT( iTer->GetID(), renderState.GetDataColour( data ) );
    }
}
