#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>

#include <cmath>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/HistogramBase.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/RenderState.hh>
using namespace Viewer;
using namespace Viewer::Frames;

HistogramBase::~HistogramBase()
{

}

void
HistogramBase::Initialise()
{
  sf::Rect<double> imageSize;
  imageSize.Left = 0.0; imageSize.Top = 0.0; imageSize.Width = 1.0; imageSize.Height = 1.0;
  Initialise( imageSize );
}

void
HistogramBase::Initialise( sf::Rect<double> imageSize )
{
  Frame::Initialise();
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( imageSize, Rect::eLocal ) ) );
}

void
HistogramBase::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}

void
HistogramBase::Render2d( RWWrapper& windowApp,
                          const RenderState& renderState )
{
  fImage->Clear();

  CalculateHistogram( renderState );
  DrawHistogram( renderState );
  DrawTicks();

  fImage->Update();
  windowApp.Draw( *fImage );
}

void
HistogramBase::DrawHistogram( const RenderState& renderState )
{
  if( fBins.empty() )
    return;
  // Must convert data bins, to drawable bins. This is because the projection
  // image has a limited number of pixels and hence thus will have a limit to 
  // the granularity it can display or conversly can give more pixels to each
  // bin.
  double pixelBinWidth = 1.0 / (double)fImage->GetWidth(); // In local coords
  int binsPerPixel = 1.0; // Default guess
  if( fBins.size() < fImage->GetWidth() ) 
    // Can increase the number of pixels per bin
    pixelBinWidth = (double)fImage->GetWidth() / (double)fBins.size();
  else if( fBins.size() > fImage->GetWidth() )
    // Must include more bins per pixel
    binsPerPixel = fBins.size() / fImage->GetWidth();
  // Choose a safe fMaxValue to scall to
  fMaxValue = 0.0;
  for( unsigned int iBin = 0; iBin < fBins.size(); iBin += binsPerPixel )
    {
      double binValue = 0.0;
      for( unsigned int iBin2 = iBin; iBin2 < iBin + binsPerPixel; iBin2++ )
        binValue += fBins[iBin2];
      fMaxValue = max( fMaxValue, binValue );
    }
  // Histogram of zeros....
  if( fMaxValue == 0.0 )
    return;
  // Now the histogram can be drawn 
  for( unsigned int iBin = 0; iBin < fBins.size(); iBin += binsPerPixel )
    {
      double binValue = 0.0;
      for( unsigned int iBin2 = iBin; iBin2 < iBin + binsPerPixel; iBin2++ )
        binValue += fBins[iBin2];

      const double binRatio = static_cast<double>( iBin ) / static_cast<double>( fBins.size() );
      double binHeight = binValue / fMaxValue;
      if( fLogY && binValue > 0.0 && fMaxValue > 1.0 )
        binHeight = log10( binValue ) / ( log10( fMaxValue ) - log10( 0.1 ) );
      sf::Vector2<double> pos( binRatio, 1.0 - binHeight );
      sf::Vector2<double> size( pixelBinWidth, binHeight );
      if( static_cast<double>( iBin ) > renderState.GetScalingMin() && static_cast<double>( iBin ) < renderState.GetScalingMax() )
        fImage->DrawSquare( pos, size, ColourPalette::gPalette->GetColour( ( (double)( iBin ) - renderState.GetScalingMin() ) / ( renderState.GetScalingMax() - renderState.GetScalingMin() ) ) );
    }
}

void
HistogramBase::DrawTicks()
{
  const double ticSize = 0.05;
  for( int iTic = 0.0; iTic <= 10; iTic++ )
    {
      double xPos =  (double)iTic / 10.0;
      sf::Vector2<double> pos( xPos, 1.0 - ticSize );
      sf::Vector2<double> size( 1.0 / fImage->GetWidth(), ticSize );
      fImage->DrawSquare( pos, size, ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
      double yPos = (double)iTic / 10.0 * fMaxValue;
      if( fLogY && yPos != 0.0 )
	yPos = log10( yPos ) / ( log10( fMaxValue ) - log10( 0.1 ) );
      else
	yPos /= fMaxValue;
      pos = sf::Vector2<double>( 0.0, yPos );
      size = sf::Vector2<double>( ticSize, 1.0 / fImage->GetWidth() );
      fImage->DrawSquare( pos, size, ColourPalette::gPalette->GetPrimaryColour( eGrey ) );
    }
}

void
HistogramBase::CalculateHistogram( const RenderState& renderState )
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
	      const double tac = rEV->GetPMTUnCal( ipmt )->GetsPMTt(); 
	      if( tac > 0.0 && tac < fBins.size() )
		{
		  int bin = static_cast<int>( tac );
		  fBins[ bin ] += 1.0;
		}
	      }
	  break;
	case RenderState::eQHL:
	  fBins.resize( 4500, 0.0 );
          for( unsigned int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
            {
	      const double qhl = rEV->GetPMTUnCal( ipmt )->GetsQHL();
              if( qhl > 0.0 && qhl < fBins.size() )
		{
                  int bin = static_cast<int>( qhl );
                  fBins[ bin ] += 1.0;
		}
	    }
	  break;
	case RenderState::eQHS:
          fBins.resize( 4500, 0.0 );
          for( unsigned int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
            {
              const double qhs = rEV->GetPMTUnCal( ipmt )->GetsQHS();
              if( qhs > 0.0 && qhs < fBins.size() )
                {
                  int bin = static_cast<int>( qhs );
                  fBins[ bin ] += 1.0;
		}
            }
          break;
	case RenderState::eQLX:
          fBins.resize( 1400, 0.0 );
          for( unsigned int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
            {
              const double qlx = rEV->GetPMTUnCal( ipmt )->GetsQLX();
              if( qlx > 0.0 && qlx < fBins.size() )
		{
                  int bin = static_cast<int>( qlx );
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
	      const double tac = rEV->GetPMTCal( ipmt )->GetsPMTt();
	      if( tac > 0.0 && tac < 500.0 )
		{
		  int bin = static_cast<int>( tac );
		  fBins[ bin ] += 1.0;
		}
	    }
	  break;
	case RenderState::eQHL:
          fBins.resize( 4000, 0.0 );
          for( unsigned int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
            {
              const double qhl = rEV->GetPMTCal( ipmt )->GetsQHL();
              if( qhl > 0.0 && qhl < fBins.size() )
                {
                  int bin = static_cast<int>( qhl );
                  fBins[ bin ] += 1.0;
                }
            }
          break;
        case RenderState::eQHS:
          fBins.resize( 4000, 0.0 );
          for( unsigned int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
            {
              const double qhs = rEV->GetPMTCal( ipmt )->GetsQHS();
              if( qhs > 0.0 && qhs < fBins.size() )
                {
                  int bin = static_cast<int>( qhs );
                  fBins[ bin ] += 1.0;
                }
            }
          break;
	case RenderState::eQLX:
          fBins.resize( 1000, 0.0 );
          for( unsigned int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
            {
              const double qlx = rEV->GetPMTCal( ipmt )->GetsQLX();
              if( qlx > 0.0 && qlx < fBins.size() )
                {
                  int bin = static_cast<int>( qlx );
                  fBins[ bin ] += 1.0;
                }
            }
          break;
	}
      break;
    }
}
