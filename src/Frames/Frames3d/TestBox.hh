////////////////////////////////////////////////////////////////////////
/// \class TestBox
///
/// \brief   Just for 'fun'
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames3d_TestBox__
#define __Viewer_Frames3d_TestBox__

#include <string>

#include <Viewer/Frame.hh>

namespace Viewer
{
  class RWWrapper;
  class RenderState;
namespace GUIs
{
  class DragArea;
}

namespace Frames
{

class TestBox : public Frame
{
public:
  TestBox( RectPtr rect ) : Frame( rect ) { }
  virtual ~TestBox() { }

  void Initialise();

  virtual void EventLoop();
  
  std::string GetName() { return TestBox::Name(); }
  static std::string Name() { return std::string( "TestBox" ); }

  virtual void Render2d( RWWrapper& renderApp,
			 const RenderState& renderState ) { } ;
  virtual void Render3d( RWWrapper& renderApp,
			 const RenderState& renderState );
private:
  GUIs::DragArea* fDragArea;
  double fRotate;
};

} // ::Frames3d

} // ::Viewer

#endif
