////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Histogram
///
/// \brief   Extends the histogram base with a GUI and labels
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     28/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Draws the axis and axis labels onto the histogram.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Histogram__
#define __Viewer_Frames_Histogram__

#include <Viewer/HistogramBase.hh>

namespace Viewer
{
  class Text;
  class renderApp;
  class RenderState;
namespace GUIs
{
  class PersistLabel;
}

namespace Frames
{

class Histogram : public HistogramBase
{
public:
  Histogram( RectPtr rect ) : HistogramBase( rect ) { fLogY = false; }
  ~Histogram();

  virtual std::string GetName() { return Histogram::Name(); }
  static std::string Name() { return string("Histogram"); }

  virtual void PreInitialise( const ConfigurationTable* configTable );

  virtual void EventLoop();

  virtual void Render2d( RWWrapper& renderApp, 
			 const RenderState& renderState );

protected:
  
  GUIs::PersistLabel* fLogYBox;
  Text* fMinX;
  Text* fMaxX;
  Text* fMinY;
  Text* fMaxY;
};

} // ::Frames

} // ::Viewer

#endif
