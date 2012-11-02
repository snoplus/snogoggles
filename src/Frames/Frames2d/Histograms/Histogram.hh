////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Histogram
///
/// \brief   Histogram drawing frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Draws histograms onto the screen. 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Histogram__
#define __Viewer_Frames_Histogram__

#include <SFML/System/Vector2.hpp>

#include <vector>

#include <Viewer/Frame.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
  class ProjectionImage;

namespace Frames
{

class Histogram : public Frame
{
public:
  Histogram( RectPtr rect ) : Frame( rect ), fLogY( false ) { }
  ~Histogram();

  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable );

  virtual void EventLoop();
  
  virtual std::string GetName() { return Histogram::Name(); }
  
  static std::string Name() { return std::string( "Histogram" ); }

  virtual void ProcessData( const RenderState& renderState ) { }

  virtual void Render2d( RWWrapper& renderApp, 
                         const RenderState& renderState );

  void Render3d( RWWrapper& renderApp, 
                 const RenderState& renderState ) { }

protected:
  void CalculateHistogram( const RenderState& renderState );
  void DrawHistogram();
  void DrawAxis();

  void DrawTickLabel( double value,
                      bool xAxis );
  int CalculateBin( double value );
  double ScaleY( double value );

  std::vector<Text> fAxisText;
  std::vector<double> fValues; /// < The histogram values, by bin (always binned by 1)
  std::pair<double, double> fXDomain; /// < Domain in x, from low to high
  std::pair<double, double> fYRange; /// < Range in y, from low to high
  sf::Vector2<double> fMousePos; /// < The mouse position (-1, -1) if not in frame
  Text* fInfoText; /// < Displays info about the selected bin
  ProjectionImage* fImage; /// < The histogram image to display
  double fBarWidth; /// < Amount of pixels per drawn bin
  bool fLogY; /// < LogY?
  bool fOverflow; /// < Plot the overflow bins?
};

} // ::Frames

} // ::Viewer

#endif
