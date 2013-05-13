////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::About
///
/// \brief   About frame, displays viewer information
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/07/11 : P.Jones - First Revision, new file. \n
///     21/02/12 : P.Jones - Second Revision, uses new Rect structure. \n
///
/// \detail  Displays frame rate and (hard coded) viewer revision.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_About__
#define __Viewer_Frames_About__

#include <deque>

#include <Viewer/Frame2d.hh>

namespace Viewer
{
  class Text;

namespace Frames
{

class About : public Frame2d
{
public:
  About( RectPtr rect ) : Frame2d( rect ) { }
  ~About();

  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable ) { };
 
  virtual void EventLoop();
  
  virtual std::string GetName() { return About::Name(); }
  
  static std::string Name() { return std::string( "About" ); }

  virtual void ProcessEvent( const RenderState& renderState ) { }

  virtual void ProcessRun() { }

  virtual void Render2d( RWWrapper& renderApp,
                         const RenderState& renderState );

  void Render3d( RWWrapper& renderApp,
                 const RenderState& renderState ) { }

private:
  std::deque<double> fFrameRates;
  Text* fInfoText;
};

} // ::Frames

} // ::Viewer

#endif
