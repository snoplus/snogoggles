////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::HistogramBase
///
/// \brief   Simple histogram drawing frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     24/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Draws histograms onto the screen. No fancy gui etc...
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_HistogramBase__
#define __Viewer_Frames_HistogramBase__

#include <SFML/System/Vector2.hpp>

#include <vector>

#include <Viewer/Frame.hh>

namespace Viewer
{
  class ProjectionImage;

namespace Frames
{

class HistogramBase : public Frame
{
public:
  HistogramBase( RectPtr rect ) : Frame( rect ), fLogY( true ) { }
  ~HistogramBase();

  virtual void Initialise();
  void Initialise( sf::Rect<double> imageSize );

  void LoadConfiguration( ConfigurationTable& configTable ) { }

  void SaveConfiguration( ConfigurationTable& configTable ) { }

  virtual void EventLoop();
  
  virtual std::string GetName() { return HistogramBase::Name(); }
  
  static std::string Name() { return std::string( "HistogramBase" ); }

  virtual void Render2d( RWWrapper& renderApp, 
			 const RenderState& renderState );

  void Render3d( RWWrapper& renderApp, 
		 const RenderState& renderState ) { }

  //EFrameType GetFrameType() { return eUtil; }
protected:
  virtual void CalculateHistogram( const RenderState& renderState );
  virtual void DrawHistogram();
  virtual void DrawTicks();

  std::vector<double> fBins; /// < The histogram bin values
  ProjectionImage* fImage;
  bool fLogY; /// < Display the y axis as log
  double fMaxValue; /// < Current Max value
};

} // ::Frames

} // ::Viewer

#endif
