////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::EventInfo
///
/// \brief   EventInfo frame, displays event information
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/07/11 : P.Jones - First Revision, new file. \n
///     21/02/12 : P.Jones - Refactor for new Rect system. \n
///
/// \detail  Displays gtid, event ID, Number of hits, event data and time
///          trigger word, number of hits by tube type and TUBII (eventually).
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_EventInfo__
#define __Viewer_Frames_EventInfo__

#include <string>

#include <Viewer/Frame.hh>

namespace Viewer
{
  class Text;

namespace Frames
{

class EventInfo : public Frame
{
public:
  EventInfo( RectPtr rect ) : Frame( rect ) { }
  ~EventInfo();

  void Initialise();
 
  virtual void EventLoop();
  
  virtual std::string GetName() { return EventInfo::Name(); }
  
  static std::string Name() { return std::string( "Event Info" ); }

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
