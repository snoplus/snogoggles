#include <Viewer/HistogramBase.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;
using namespace Viewer::Frames;

const double kAxisMargin = 0.1;

HistogramBase::~HistogramBase()
{
  delete fImage;
}

void 
HistogramBase::PreInitialise( const ConfigurationTable* configTable )
{
  if( configTable != NULL )
    fLogY = configTable->GetI( "logY" );
}

void 
HistogramBase::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "logY", fLogY );
}

void
HistogramBase::Render2d( RWWrapper& windowApp,
			 const RenderState& renderState )
{
  windowApp.Draw( *fImage );
}

void
HistogramBase::Initialise( const sf::Rect<double> imageSize )
{
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( imageSize, Rect::eLocal ) ) );
}

unsigned int
HistogramBase::GetMaxNumberOfBins()
{
  return static_cast<unsigned int>( static_cast<double>( fImage->GetWidth() ) * ( 1.0 - kAxisMargin ) );
}

void
HistogramBase::RenderToImage()
{
  fImage->Clear();
  // First the histogram drawing part
  if( !fValues.empty() && fYRange.second > 0.0 ) 
    {
      for( unsigned int iStack = 0; iStack < fValues.size(); iStack++ )
	{
	  const vector<double> values = fValues[iStack];
	  const double barWidth = 1.0 / static_cast<double>( values.size() );
	  for( unsigned int iBin = 0; iBin < values.size(); iBin++ )
	    {
	      const double value = values[iBin];
	      const double binRatio = static_cast<double>( iBin ) / static_cast<double>( values.size() );
	      sf::Vector2<double> pos( binRatio * ( 1.0 - kAxisMargin ) + kAxisMargin, 1.0 - ScaleY( value ) - kAxisMargin );
	      sf::Vector2<double> size( barWidth, ScaleY( value ) );
	      fImage->DrawSquare( pos, size, GetRenderColor( iStack, iBin, value ) );
	    }
	}
    }
  // Now the axis drawing part

  fImage->Update();
}

double
HistogramBase::ScaleY( const double value ) const
{
  if( fLogY && value > 0.0 && fYRange.second > 1.0 )
    return log10( value ) / ( log10( fYRange.second ) - log10( 0.1 ) ) * ( 1.0 - kAxisMargin );
  else
    return ( value / fYRange.second ) * ( 1.0 - kAxisMargin );
}
