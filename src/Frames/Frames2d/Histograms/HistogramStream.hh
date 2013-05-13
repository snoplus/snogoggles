////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::HistogramStream
///
/// \brief   HistogramStream drawing frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     13/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Draws the last fNumBins in seconds of data to the screen
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_HistogramStream__
#define __Viewer_Frames_HistogramStream__

#include <Viewer/HistogramBase.hh>

namespace Viewer
{
namespace RIDS
{
  class Event;
}

namespace Frames
{

class HistogramStream : public HistogramBase
{
public:
  HistogramStream( RectPtr rect ) : HistogramBase( rect ) { }
  virtual ~HistogramStream() { };

  virtual void ProcessEvent( const RenderState& renderState );

  virtual void ProcessRun() { };
protected:
  /// Return the render colour given the stack, bin and value
  Colour GetRenderColor( const unsigned int stack,
			 const unsigned int bin,
			 const double value );
  /// Called to extract the data and place it into the appropriate stack
  virtual void ExtractData( const RIDS::Event& event,
                            const unsigned int iBin ) = 0;
  /// Set the number of bins and stacks
  void SetNumBinsStacks( const int numBins,
                         const int numStacks );
private:
  int fNumBins; /// < Number of bins
  int fNumStacks; /// < Number of stacks
};

} // ::Frames

} // ::Viewer

#endif
