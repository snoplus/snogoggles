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
    fValues[iBin][0] += 1.0;
  if( trigger & 0x01 || trigger & 0x02 || trigger & 0x04 )
    fValues[iBin][1] += 1.0;
  if( trigger & 0x08 || trigger & 0x10 )
    fValues[iBin][2] += 1.0;
  if( trigger & 0x20 || trigger & 0x40 )
    fValues[iBin][3] += 1.0;
  if( trigger & 0x80 || trigger & 0x100 || trigger & 0x200 )
    fValues[iBin][4] += 1.0;
  if( trigger & 0x400 || trigger & 0x800 || trigger & 0x1000 || trigger & 0x2000 || trigger & 0x4000 || trigger & 0x8000 )
    fValues[iBin][5] += 1.0;
}
