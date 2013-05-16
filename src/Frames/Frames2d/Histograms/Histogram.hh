////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Histogram
///
/// \brief   Histogram drawing frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     16/05/12 : P.Jones - First Revision, new file (refactored version). \n
///
/// \detail  Draws a histogram of the current selected data.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Histogram__
#define __Viewer_Frames_Histogram__

#include <Viewer/HistogramBase.hh>

namespace Viewer
{
namespace RIDS
{
  class Event;
}

namespace Frames
{

class Histogram : public HistogramBase
{
public:
  Histogram( RectPtr rect ) : HistogramBase( rect ) { }
  virtual ~Histogram() { };

  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable );

  virtual void EventLoop();

  virtual std::string GetName() { return Histogram::Name(); }

  static std::string Name() { return std::string( "Histogram" ); }

  virtual void ProcessEvent( const RenderState& renderState );

  virtual void ProcessRun() { };
protected:
  /// Return the render colour given the stack, bin and value
  Colour GetRenderColor( const unsigned int stack,
                         const unsigned int bin,
                         const double value );
};

} // ::Frames

} // ::Viewer

#endif
