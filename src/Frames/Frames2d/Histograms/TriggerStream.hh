////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::TriggerStream
///
/// \brief   TriggerStream drawing frame
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     13/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Draws the last 200 seconds of triggers to the screen
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_TriggerStream__
#define __Viewer_Frames_TriggerStream__

#include <Viewer/HistogramStream.hh>

namespace Viewer
{

namespace Frames
{

class TriggerStream : public HistogramStream
{
public:
  TriggerStream( RectPtr rect ) : HistogramStream( rect ) { }
  virtual ~TriggerStream() { };

  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable );

  virtual void EventLoop();
  
  virtual std::string GetName() { return TriggerStream::Name(); }
  
  static std::string Name() { return std::string( "Triggers" ); }
protected:
  void ExtractData( const RIDS::Event& event,
                    const unsigned int iBin );
};

} // ::Frames

} // ::Viewer

#endif
