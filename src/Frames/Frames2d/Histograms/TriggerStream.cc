#include <Viewer/TriggerStream.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;
using namespace Viewer::Frames;
#include <Viewer/RIDS/Event.hh>

void
TriggerStream::PreInitialise( const ConfigurationTable* configTable )
{
  HistogramBase::PreInitialise( configTable );
  sf::Rect<double> imageSize( 0.0, 0.0, 1.0, 1.0 );
  Initialise( imageSize );
  SetNumBinsStacks( 200, 6 );
}

void
TriggerStream::SaveConfiguration( ConfigurationTable* configTable )
{
  HistogramBase::SaveConfiguration( configTable );
}

void
TriggerStream::ExtractData( const RIDS::Event& event, 
			    const unsigned int iBin )
{
  const int trigger = event.GetTrigger();
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
