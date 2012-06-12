#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

#include <Viewer/Histogram.hh>
#include <Viewer/Text.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;
using namespace Viewer::Frames;

Histogram::~Histogram()
{
  delete fMinX, fMinY, fMaxX, fMaxY;
}

void 
Histogram::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> size;
  size.Left = 0.1; size.Top = 0.0; size.Width = 0.9; size.Height = 0.9;
  HistogramBase::Initialise( size );
  size.Left = 0.0; size.Width = 0.1; size.Height = 0.05;
  fMaxY = new Text( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  size.Top = 0.85;
  fMinY = new Text( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  size.Left = 0.1; size.Top = 0.9; 
  fMinX = new Text( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  size.Left = 0.9;
  fMaxX = new Text( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  size.Left = 0.9; size.Top = 0.0; size.Width = 0.1; size.Height = 0.025;
  fLogYBox = fGUIManager.NewGUI<GUIs::PersistLabel>( size, Rect::eLocal );
  fLogYBox->SetLabel( "Log_10 Y?" );
}

void 
Histogram::EventLoop()
{
  while( !fEvents.empty() )
    {
      fLogY = fLogYBox->GetState();
      fEvents.pop();
    }
}

void 
Histogram::Render2d( RWWrapper& renderApp,
                     const RenderState& renderState )
{
  HistogramBase::Render2d( renderApp, renderState );
  if( fLogY )
    {
      stringstream value;
      value << scientific << setprecision(1) << log10( fMaxValue );
      fMaxY->SetString( value.str() );
      value.str(""); value << log10( 0.1 );
      fMinY->SetString( value.str() );
    }
  else
    {
      stringstream value;
      value << fMaxValue;
      fMaxY->SetString( value.str() );
      value.str(""); value << 0.0;
      fMinY->SetString( value.str() );
    }
  stringstream value;
  value << fBins.size();
  fMaxX->SetString( value.str() );
  value.str(""); value << 0.0;
  fMinX->SetString( value.str() );

  fMinX->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetB( eBase ) );
  fMinY->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetB( eBase ) );
  fMaxX->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetB( eBase ) );
  fMaxY->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetB( eBase ) );
  
  renderApp.Draw( *fMinX );
  renderApp.Draw( *fMaxX );
  renderApp.Draw( *fMinY );
  renderApp.Draw( *fMaxY );
}
