#include <Viewer/TriggerStream.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;
using namespace Viewer::Frames;
#include <Viewer/RIDS/Event.hh>

const unsigned int kNumBins = 200;
const unsigned int kNumStacks = 6;

void
TriggerStream::PreInitialise( const ConfigurationTable* configTable )
{
  HistogramBase::PreInitialise( configTable );
  sf::Rect<double> imageSize( 0.0, 0.0, 1.0, 1.0 );
  Initialise( imageSize );
}

void 
TriggerStream::ProcessEvent( const RenderState& renderState )
{
  // Initialise the stacks
  fValues.clear();
  fValues.resize( kNumStacks, vector<double>( kNumBins, 0.0 ) );
  // Now fill
  fXDomain = pair<double, double>( renderState.GetScalingMin(), renderState.GetScalingMax() );
  if( kNumBins > GetMaxNumberOfBins() )
    return; // Some issues here....
  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();
  const RIDS::Time& eventTime = event.GetTime();
  FillStackFromTrigger( event.GetTrigger(), 0 );
  double diffTime = 0.0;
  int peek = -1;
  while( true )
    {
      const RIDS::Event* peekEvent = DataSelector::GetInstance().PeekEvent( peek );
      if( peekEvent == NULL )
	break;
      const RIDS::Time& peekTime = peekEvent->GetTime();
      diffTime = eventTime - peekTime;
      if( diffTime < 0.0 || diffTime > kNumBins )
	break;
      unsigned int iBin = static_cast<unsigned int>( diffTime );
      FillStackFromTrigger( peekEvent->GetTrigger(), iBin );
      peek--;
    }
  // Now find the Y domain
  double maxValue = 0.0;
  for( unsigned int iBin = 0; iBin < kNumBins; iBin++ )
    {
      double value = 0.0;
      for( unsigned int iStack = 0; iStack < kNumStacks; iStack++ )
	value += fValues[iStack][iBin];
      maxValue = max( value, maxValue );
    }
  fYRange = pair<double, double>( 0.0, maxValue );
  // Now render to the image
  RenderToImage();
}

Colour 
TriggerStream::GetRenderColor( const unsigned int stack,
			       const unsigned int,
			       const double )
{
  return GUIProperties::GetInstance().GetColourPalette().GetColour( static_cast<double>( stack ) / static_cast<double>( kNumStacks ) );
}

void
TriggerStream::FillStackFromTrigger( const int trigger, 
				     const unsigned int iBin )
{
  if( trigger == 0x0 )
    fValues[0][iBin] += 1.0;
  if( trigger & 0x01 )
    fValues[1][iBin] += 1.0;
  if( trigger & 0x02 )
    fValues[1][iBin] += 1.0;
  if( trigger & 0x04 )
    fValues[1][iBin] += 1.0;
  if( trigger & 0x08 )
    fValues[2][iBin] += 1.0;
  if( trigger & 0x10 )
    fValues[2][iBin] += 1.0;
  if( trigger & 0x20 )
    fValues[3][iBin] += 1.0;
  if( trigger & 0x40 )
    fValues[3][iBin] += 1.0;
  if( trigger & 0x80 )
    fValues[4][iBin] += 1.0;
  if( trigger & 0x100 )
    fValues[4][iBin] += 1.0;
  if( trigger & 0x200 )
    fValues[4][iBin] += 1.0;
  if( trigger & 0x400 )
    fValues[5][iBin] += 1.0;
  if( trigger & 0x800 )
    fValues[5][iBin] += 1.0;
  if( trigger & 0x1000 )
    fValues[5][iBin] += 1.0;
  if( trigger & 0x2000 )
    fValues[5][iBin] += 1.0;
  if( trigger & 0x4000 )
    fValues[5][iBin] += 1.0;
  if( trigger & 0x8000 )
    fValues[5][iBin] += 1.0;
}
