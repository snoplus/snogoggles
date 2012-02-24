#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>

#include <TVector3.h>

#include <cmath>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/Histogram.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/RenderState.hh>
using namespace Viewer;
using namespace Viewer::Frames;

void
Histogram::Initialise()
{
  Frame::Initialise();
  sf::Rect<double> imageSize;
  imageSize.Left = 0.0; imageSize.Top = 0.0; imageSize.Width = 1.0; imageSize.Height = 1.0;
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( imageSize, Rect::eLocal ) ) );
}

void
Histogram::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}

void
Histogram::Render2d( RWWrapper& windowApp,
                          const RenderState& renderState )
{
  fImage->Clear();

  CalculateHistogram( renderState );
  DrawHistogram();

  fImage->Update();
  windowApp.Draw( *fImage );
}

void
Histogram::DrawHistogram()
{
  if( fBins.empty() )
    return;
  const double maxValue = *max_element( fBins.begin(), fBins.end() ) + 1;
  int drawnBinWidth = 1.0; // one pixel wide
  int binsPerDrawn = 1.0;
  if( fBins.size() > fImage->GetWidth() )
    binsPerDrawn = fBins.size() / fImage->GetWidth();
  
  drawnBinWidth /= fImage->GetWidth(); // Change to local coords
  const int binWidth = fBins.size() / fImage->GetWidth();
  for( unsigned int iBin = 0; iBin < fBins.size(); iBin += binsPerDrawn )
    {
      double binValue = 0.0;
      for( unsigned int iBin2 = iBin; iBin2 < iBin + binsPerDrawn; iBin2++ )
        binValue += fBins[iBin2];

      const double binRatio = static_cast<double>( iBin ) / static_cast<double>( fBins.size() );
      sf::Vector2<double> pos( binRatio, 1.0 - binValue / maxValue );
      sf::Vector2<double> size( drawnBinWidth, binValue / maxValue );
      fImage->DrawSquare( pos, size, ColourPalette::gPalette->GetColour( iBin / fBins.size() ) );
    }
}

void
Histogram::CalculateHistogram( const RenderState& renderState )
{
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  fBins.clear();
  switch( renderState.GetDataSource() )
    {
    case RenderState::eUnCal:
      switch( renderState.GetDataType() )
	{
	case RenderState::eTAC:
	  fBins.resize( 4000, 0.0 );
	  for( unsigned int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
	    {
	      if( rEV->GetPMTUnCal( ipmt )->GetsPMTt() > 0.0 && rEV->GetPMTUnCal( ipmt )->GetsPMTt() < 4000.0 )
		{
		  int bin = static_cast<int>( rEV->GetPMTUnCal( ipmt )->GetsPMTt() );
		  fBins[ bin ] += 1.0;
		}
	      }
	  break;
	}
      break;
    case RenderState::eCal:
      switch( renderState.GetDataType() )
	{
	case RenderState::eTAC:
	  fBins.resize( 500, 0.0 );
	  for( unsigned int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
	    {
	      if( rEV->GetPMTCal( ipmt )->GetsPMTt() > 0.0 && rEV->GetPMTCal( ipmt )->GetsPMTt() < 500.0 )
		{
		  int bin = static_cast<int>( rEV->GetPMTUnCal( ipmt )->GetsPMTt() );
		  fBins[ bin ] += 1.0;
		}
	    }
	  break;
	}
      break;
    }
}
