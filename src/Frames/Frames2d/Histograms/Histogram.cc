#include <Viewer/Histogram.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;
using namespace Viewer::Frames;
#include <Viewer/RIDS/Event.hh>

void
Histogram::PreInitialise( const ConfigurationTable* configTable )
{
  HistogramBase::PreInitialise( configTable );
  Initialise();
}

void
Histogram::SaveConfiguration( ConfigurationTable* configTable )
{
  HistogramBase::SaveConfiguration( configTable );
}

void
Histogram::EventLoop()
{
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // Nothing to do with this class
          GUIEvent( 0 );
          break;
        }
      fEvents.pop();
    }
}

void 
Histogram::ProcessEvent( const RenderState& renderState )
{
  // Initialise the stacks
  fValues.clear();
  fValues.resize( GetMaxNumberOfBins(), vector<double>( 1, 0.0 ) );
  // Now fill
  fXDomain = pair<double, double>( renderState.GetScalingMin(), renderState.GetScalingMax() );
  double binWidth = 1.0;
  const vector<RIDS::Channel>& hits = DataSelector::GetInstance().GetData( renderState.GetDataSource(), renderState.GetDataType() );
  if( hits.empty() )
    return;
  for( vector<RIDS::Channel>::const_iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      int iBin = 0;
      if( iTer->GetData() <= fXDomain.first )
        iBin = 0;
      else if( iTer->GetData() >= fXDomain.second )
        iBin = GetMaxNumberOfBins() - 1;
      else
        iBin = static_cast<int>( ( iTer->GetData() - fXDomain.first ) / ( fXDomain.second - fXDomain.first ) * ( GetMaxNumberOfBins() - 2 ) ) + 1;
      fValues[iBin][0] += iTer->GetData();
    }
  // Now find the Y domain
  double maxValue = 0.0;
  for( unsigned int iBin = 0; iBin < GetMaxNumberOfBins(); iBin++ )
    {
      double value = fValues[iBin][0];
      maxValue = max( value, maxValue );
    }
  fYRange = pair<double, double>( 0.0, maxValue );
  // Now render to the image
  RenderToImage();
}

Colour 
Histogram::GetRenderColor( const unsigned int,
                           const unsigned int bin,
                           const double )
{
  return GUIProperties::GetInstance().GetColourPalette().GetColour( static_cast<double>( bin ) / static_cast<double>( GetMaxNumberOfBins() ) );
}
