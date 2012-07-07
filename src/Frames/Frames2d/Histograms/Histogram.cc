#include <cmath>
#include <sstream>
using namespace std;

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/Histogram.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/PMTHit.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/MapArea.hh>
using namespace Viewer;
using namespace Viewer::Frames;

const double kAxisMargin = 0.1; // Size of the axis margin on the histogram

Histogram::~Histogram()
{

}

void
Histogram::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> imageSize( 0.0, 0.0, 1.0, 1.0 );
  fImage = new ProjectionImage( RectPtr( fRect->NewDaughter( imageSize, Rect::eLocal ) ) );
  sf::Rect<double> buttonSize( 0.8, 0.0, 0.2, 0.05 );
  GUIs::PersistLabel* logY = fGUIManager.NewGUI<GUIs::PersistLabel>( buttonSize, Rect::eLocal );
  logY->Initialise( 14, "Log_10 Y?" );
  sf::Rect<double> infoSize( 0.0, 1.0 - kAxisMargin / 2.0, 1.0, kAxisMargin / 2.0 );
  fInfoText = new Text( RectPtr( fRect->NewDaughter( infoSize, Rect::eLocal ) ) );
  imageSize.Left = kAxisMargin;
  imageSize.Width = 1.0 - kAxisMargin;
  imageSize.Height = 1.0 - kAxisMargin;
  fGUIManager.NewGUI<GUIs::MapArea>( imageSize, Rect::eLocal );
}


void
Histogram::EventLoop()
{
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0:
          fLogY = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.GetGUI( 0 ) )->GetState();
          break;
        case 1:
          fMousePos = dynamic_cast<GUIs::MapArea*>( fGUIManager.GetGUI( 1 ) )->GetPosition();
          break;
        }
      fEvents.pop();
    }
}

void
Histogram::Render2d( RWWrapper& windowApp,
                     const RenderState& renderState )
{
  fImage->Clear();
  fAxisText.clear();

  CalculateHistogram( renderState );
  DrawHistogram();
  DrawAxis();

  fImage->Update();
  windowApp.Draw( *fImage );
  for( vector<Text>::iterator iTer = fAxisText.begin(); iTer != fAxisText.end(); iTer++ )
    {
      iTer->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      windowApp.Draw( *iTer );
    }
  if( fMousePos.x > 0.0 && fMousePos.x < 1.0 )
    {
      const int bin = static_cast<int>( fMousePos.x * fValues.size() );
      stringstream info;
      info << "(" << fMousePos.x * ( fXDomain.second - fXDomain.first ) + fXDomain.first;
      info << ", " << fValues[bin] << ")";
      fInfoText->SetString( info.str() );
      fInfoText->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      windowApp.Draw( *fInfoText );
    }
}

void
Histogram::DrawHistogram()
{
  // No data, return
  if( fValues.empty() || fYRange.second <= 0.0 )
    return;
  // Now the histogram can be drawn 
  for( unsigned int iBin = 0; iBin < fValues.size(); iBin++ )
    {
      double binValue = fValues[iBin];

      const double binRatio = static_cast<double>( iBin ) / static_cast<double>( fValues.size() );
      //if( fLogY && binValue > 0.0 && fMaxValue > 1.0 )
      //  binHeight = log10( binValue ) / ( log10( fMaxValue ) - log10( 0.1 ) );
      sf::Vector2<double> pos( binRatio * ( 1.0 - kAxisMargin ) + kAxisMargin, 1.0 - ScaleY( binValue ) - kAxisMargin );
      sf::Vector2<double> size( fBarWidth, ScaleY( binValue ) );
      fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetColourPalette().GetColour( binRatio ) );
    }
}

void
Histogram::DrawAxis()
{
  // First the axis lines, x then y
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
        DrawTickLabel( xValue, true );
      const double yValue = yBase * iTick;
      if( yValue >= fYRange.first && yValue <= fYRange.second )
        DrawTickLabel( yValue, false );
    }
}

void
Histogram::DrawTickLabel( double value,
                      bool xAxis )
{
  sf::Vector2<double> pos, size;
  sf::Rect<double> textSize;
  if( xAxis )
    {
      pos = sf::Vector2<double>( (double)CalculateBin( value ) / (double) fValues.size() * ( 1.0 - kAxisMargin ) + kAxisMargin, 1.0 - kAxisMargin );
      size = sf::Vector2<double>( 1.0 / fImage->GetWidth(), kAxisMargin / 6.0 );
      textSize = sf::Rect<double>( pos.x, pos.y, ( 1.0 - kAxisMargin ) / 10.0, kAxisMargin / 2.0 );
      if( pos.x > 0.9 )
        textSize.Left = pos.x - ( 1.0 - kAxisMargin ) / 15.0;
    }
  else
    {
      pos = sf::Vector2<double>( kAxisMargin - kAxisMargin / 6.0, 1.0 - kAxisMargin - ScaleY( value ) );
      size = sf::Vector2<double>( kAxisMargin / 6.0, 1.0 / fImage->GetHeight() );
      textSize = sf::Rect<double>( kAxisMargin / 6.0, pos.y - kAxisMargin / 2.0, kAxisMargin - kAxisMargin / 6.0, kAxisMargin / 2.0 );
    }
  fImage->DrawSquare( pos, size, GUIProperties::GetInstance().GetGUIColourPalette().GetAspect() );
  Text label( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  stringstream temp; temp << value;
  label.SetString( temp.str() );
  fAxisText.push_back( label );
}

void
Histogram::CalculateHistogram( const RenderState& renderState )
{
  fXDomain = pair<double, double>( renderState.GetScalingMin(), renderState.GetScalingMax() );
  const unsigned int numberOfValues = ( renderState.GetScalingMax() - renderState.GetScalingMin() ) + 4; // Two overflows + 2 margins
  const unsigned int numberOfPixels = static_cast<unsigned int>( (double)fImage->GetWidth() * ( 1.0 - kAxisMargin ) );
  int binWidth = 1;

  if( numberOfValues < numberOfPixels ) // More than enough pixels to display all data
    {
      binWidth = 1;
      fBarWidth = 1.0 / (double) numberOfValues;
    }
  else // Not enough pixels, must compress data
    {
      binWidth = static_cast<int>( (double)numberOfValues / (double)numberOfPixels ); 
      fBarWidth = 1.0 / (double)numberOfPixels;
    }
  fValues.clear();
  fValues.resize( ( numberOfValues - 4 ) / binWidth + 4, 0.0 ); // Overflows and margins don't compress
  vector<RIDS::PMTHit> hits = DataStore::GetInstance().GetHitData( renderState.GetDataSource() );
  for( vector<RIDS::PMTHit>::const_iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      const double data = iTer->GetData( renderState.GetDataType() );
      int bin = CalculateBin( data );
      fValues[ bin ] += 1.0;
    }
  if( fLogY )
    fYRange = pair<double, double>( 0.1, *max_element( fValues.begin(), fValues.end() ) );
  else
    fYRange = pair<double, double>( 0.0, *max_element( fValues.begin(), fValues.end() ) );
}

int
Histogram::CalculateBin( double value )
{
  if( value <= fXDomain.first )
    return 0;
  else if( value >= fXDomain.second )
    return fValues.size() - 1;
  else
    return static_cast<int>( ( value - fXDomain.first ) / ( fXDomain.second - fXDomain.first ) * ( fValues.size() - 4 ) ) + 2;
}

double
Histogram::ScaleY( double value )
{
  if( fLogY && value > 0.0 && fYRange.second > 1.0 )
    return log10( value ) / ( log10( fYRange.second ) - log10( 0.1 ) ) * ( 1.0 - kAxisMargin );
  else
    return ( value / fYRange.second ) * ( 1.0 - kAxisMargin );
}
