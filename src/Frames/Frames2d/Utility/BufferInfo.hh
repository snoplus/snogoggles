////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::BufferInfo
///
/// \brief   BufferInfo frame, displays buffer information
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     27/10/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Displays information about the buffers.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_BufferInfo__
#define __Viewer_Frames_BufferInfo__

#include <string>

#include <Viewer/Frame2d.hh>

namespace Viewer
{
  class Text;

namespace Frames
{

class BufferInfo : public Frame2d
{
public:
  BufferInfo( RectPtr rect ) : Frame2d( rect ) { }
  ~BufferInfo();

  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable ) { };
 
  virtual void EventLoop();
  
  virtual std::string GetName() { return BufferInfo::Name(); }
  
  static std::string Name() { return std::string( "Buffer Info" ); }

  virtual void ProcessEvent( const RenderState& renderState ) { }

  virtual void ProcessRun() { } 

  virtual void Render2d( RWWrapper& windowApp,
                         const RenderState& renderState );
  
  void Render3d( RWWrapper& windowApp,
                 const RenderState& renderState ) { }
  
  static std::string ToByteString( int number );
  static std::string ToHexString( int number );
private:
  Text* fInfoText;
};

} // ::Frames

} // ::Viewer

#endif
