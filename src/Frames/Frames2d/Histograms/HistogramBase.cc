#include <Viewer/HistogramBase.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/GUIProperties.hh>
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
  for( vector<Text>::iterator iTer = fAxisText.begin(); iTer != fAxisText.end(); iTer++ )
    {
      iTer->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      windowApp.Draw( *iTer );
    }
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
  fAxisText.clear();
  fImage->Clear();
  // First the histogram drawing part
  if( !fValues.empty() && fYRange.second > 0.0 ) 
    {
      for( unsigned int iStack = 0; iStack < fValues.size(); iStack++ )
        {
          const vector<double> values = fValues[iStack];
          for( unsigned int iBin = 0; iBin < values.size(); iBin++ )
            {
              const double value = values[iBin];
              const double binWidth = 1.0 / static_cast<double>( values.size() );
              sf::Vector2<double> pos( static_cast<double>( iBin ) * binWidth + kAxisMargin, 1.0 - ScaleY( value ) - kAxisMargin );
              sf::Vector2<double> size( binWidth, ScaleY( value ) );
              fImage->DrawSquare( pos, size, GetRenderColor( iStack, iBin, value ) );
            }
        }
    }
  // Now the axis drawing part, First the axis lines, x then y
  sf::Vector2<double> pos( kAxisMargin, 1.0 - kAxisMargin );
  sf::Vector2<double> size( 1.0 - kAxisMargin, 1.0 / fImage->GetHeight() );
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  pos = sf::Vector2<double>( kAxisMargin, 0.0 );
  size = sf::Vector2<double>( 1.0 / fImage->GetWidth(), 1.0 - kAxisMargin );
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  // Now the ticks and indeed labels (max of 10)
  const int xOrdinal = log10( fXDomain.second );
  const double xBase = pow( 10.0, xOrdinal );
  const int yOrdinal = log10( fYRange.second );
  const double yBase = pow( 10.0, yOrdinal );
  for( int iTick = 0; iTick < 10; iTick++ )
    {
      const double xValue = xBase * iTick;
      if( xValue >= fXDomain.first && xValue <= fXDomain.second )
        DrawTickLabel( xValue, xOrdinal, true );
      const double yValue = yBase * iTick;
      if( yValue >= fYRange.first && yValue <= fYRange.second )
        DrawTickLabel( yValue, yOrdinal, false );
    }
  fImage->Update();
}

void
HistogramBase::DrawTickLabel( double value,
                              int ordinal,
                              bool xAxis )
{
  sf::Vector2<double> pos, size;
  sf::Rect<double> textSize;
  if( xAxis )
    {
      pos = sf::Vector2<double>( ( value - fXDomain.first ) / ( fXDomain.second - fXDomain.first ) * ( 1.0 - kAxisMargin ) + kAxisMargin, 1.0 - kAxisMargin );
      size = sf::Vector2<double>( 1.0 / fImage->GetWidth(), kAxisMargin / 6.0 );
      textSize = sf::Rect<double>( pos.x, pos.y, kAxisMargin, kAxisMargin );
      if( textSize.left > 1.0 - textSize.width )
        textSize.left = 1.0 - textSize.width;
    }
  else
    {
      pos = sf::Vector2<double>( kAxisMargin - kAxisMargin / 6.0, 1.0 - kAxisMargin - ScaleY( value ) );
      size = sf::Vector2<double>( kAxisMargin / 6.0, 1.0 / fImage->GetHeight() );
      textSize = sf::Rect<double>( kAxisMargin / 6.0, pos.y - kAxisMargin / 2.0, kAxisMargin, kAxisMargin );
    }
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  Text label( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  stringstream temp; 
  if( value == 0.0 )
    { 
      for( int iSpaces = 0; iSpaces < ordinal; iSpaces++ )
        temp << ' ';
    }
  temp << value;
  label.SetString( temp.str() );
  fAxisText.push_back( label );
}

double
HistogramBase::ScaleY( const double value ) const
{
  if( fLogY && value > 0.0 && fYRange.second > 1.0 )
    return log10( value ) / ( log10( fYRange.second ) - log10( 0.1 ) ) * ( 1.0 - kAxisMargin );
  else
    return ( value / fYRange.second ) * ( 1.0 - kAxisMargin );
}
