////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame
///
/// \brief   The base class for all frames
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  All Frames will derive from this, however frames should derive
///          from the 2d or 3d subclass version.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame__
#define __Viewer_Frame__

#include <queue>
#include <string>

#include <Viewer/Rect.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/GUIReturn.hh>
#include <Viewer/RWWrapper.hh>

namespace sf
{
  class RenderWindow;
  class Event;
} //::sf

namespace Viewer
{
  class ConfigurationTable;

class Frame
{
public:   
  enum EFrameType { eUtil, e3d, e2d };

  virtual ~Frame() {};

  virtual void NewEvent( UIEvent& event );
   
  virtual void Initialise() = 0;
  virtual void LoadConfiguration( ConfigurationTable& configTable );

  virtual void SaveConfiguration( ConfigurationTable& configTable );

  virtual void EventLoop() = 0;
  
  virtual std::string GetName() = 0;

  /// Only the GUIManager needs the RenderWindow, if overload RenderGUI then you should know what todo...
  virtual void RenderGUI( sf::RenderWindow& windowApp );
  inline virtual void Render2dT( sf::RenderWindow& windowApp );
  virtual void Render2d( RWWrapper& windowApp ) = 0;
  virtual void Render3d() = 0;

  inline virtual double GetAspectRatio();

  inline void SetRect( const Rect& rect );
  inline Rect GetRect(); 

  inline bool ContainsResolutionPoint( const sf::Vector2<double>& point );
protected:
  Rect fFrameRect;
  GUIManager fGUIManager;
  std::queue<GUIReturn> fEvents;
};

void 
Frame::Render2dT( sf::RenderWindow& windowApp ) 
{ 
  RWWrapper wrapper = RWWrapper( windowApp, fFrameRect );
  Render2d( wrapper ); 
}

double
Frame::GetAspectRatio()
{
  return 1.0;
}

void
Frame::SetRect( const Rect& rect ) 
{
  fFrameRect = rect;
}

Rect 
Frame::GetRect()
{
  return fFrameRect;
}

bool 
Frame::ContainsResolutionPoint(const sf::Vector2<double>& point  )
{
  return fFrameRect.ContainsResolutionPoint( point );
}

} // ::Viewer

#endif
