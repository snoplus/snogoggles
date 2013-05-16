#include <Viewer/HistogramStream.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;
using namespace Viewer::Frames;
#include <Viewer/RIDS/Event.hh>

void 
HistogramStream::SetNumBinsStacks( const int numBins,
                                   const int numStacks )
{
  fNumBins = min( static_cast<int>( GetMaxNumberOfBins() ), numBins );
  fNumStacks = numStacks;
}

void 
HistogramStream::ProcessEvent( const RenderState& renderState )
{
  // Initialise the stacks
  fValues.clear();
  fValues.resize( fNumBins, vector<double>( fNumStacks, 0.0 ) );
  // Now fill
  fXDomain = pair<double, double>( 0.0, fNumBins );
  if( fNumBins > GetMaxNumberOfBins() )
    return; // Some issues here....
  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();
  const RIDS::Time& eventTime = event.GetTime();
  ExtractData( event, 0 );
  double diffTime = 0.0;
  int peek = -1;
  while( true )
    {
      const RIDS::Event* peekEvent = DataSelector::GetInstance().PeekEvent( peek );
      if( peekEvent == NULL )
        break;
      const RIDS::Time& peekTime = peekEvent->GetTime();
      diffTime = eventTime - peekTime;
      if( diffTime < 0.0 || diffTime > fNumBins )
        break;
      unsigned int iBin = static_cast<unsigned int>( diffTime );
      ExtractData( *peekEvent, iBin );
      peek--;
    }
  // Now find the Y domain
  double maxValue = 0.0;
  for( unsigned int iBin = 0; iBin < fNumBins; iBin++ )
    {
      double value = 0.0;
      for( unsigned int iStack = 0; iStack < fNumStacks; iStack++ )
        value += fValues[iBin][iStack];
      maxValue = max( value, maxValue );
    }
  fYRange = pair<double, double>( 0.0, maxValue );
  // Now render to the image
  RenderToImage();
}

Colour 
HistogramStream::GetRenderColor( const unsigned int stack,
                                 const unsigned int,
                                 const double )
{
  return GUIProperties::GetInstance().GetColourPalette().GetColour( static_cast<double>( stack ) / static_cast<double>( fNumStacks ) );
}
