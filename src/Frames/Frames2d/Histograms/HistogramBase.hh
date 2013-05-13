////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::HistogramBase
///
/// \brief   HistogramBase drawing frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Draws histograms onto the screen. 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_HistogramBase__
#define __Viewer_Frames_HistogramBase__

#include <vector>

#include <Viewer/Frame2d.hh>
#include <Viewer/Colour.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
  class ProjectionImage;

namespace Frames
{

class HistogramBase : public Frame2d
{
public:
  HistogramBase( RectPtr rect ) : Frame2d( rect ), fLogY( false ) { }
  virtual ~HistogramBase();

  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable );
  
  virtual void Render2d( RWWrapper& renderApp, 
                         const RenderState& renderState );

protected:
  /// Initialise the histogram
  void Initialise( const sf::Rect<double> imageSize );
  /// Return the bin render colour, based on the stack, bin or value (as appropriate)
  virtual Colour GetRenderColor( const unsigned int stack,
				 const unsigned int bin,
				 const double value ) = 0;
  /// Return the max number of bins
  unsigned int GetMaxNumberOfBins();
  /// Render the histogram to the image
  void RenderToImage();

  std::vector< std::vector<double> > fValues; /// < The stack of histogram bin values
  std::pair<double, double> fXDomain; /// < Domain in x that corresponds to the bins, from low to high
  std::pair<double, double> fYRange; /// < Range in y to draw, from low to high
private:
  /// Draw a tick on the image and save a text
  void DrawTickLabel( double value,
                      bool xAxis );
  /// Scale the value into a y relative coord
  double ScaleY( const double value ) const;

  std::vector<Text> fAxisText; /// < The axis labels
  ProjectionImage* fImage; /// < The actual image
  bool fLogY; /// < Display Y in log scale
};

} // ::Frames

} // ::Viewer

#endif
