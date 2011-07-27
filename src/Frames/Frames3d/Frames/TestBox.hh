////////////////////////////////////////////////////////////////////////
/// \class TestBox
///
/// \brief   
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
namespace GUIs
{
  class DragArea;
}

namespace Frames
{

class TestBox : public Frame
{
public:
  TestBox() { }
  virtual ~TestBox() { }

  void Initialise();
  void Initialise( ConfigurationTable& configTable );

  virtual void EventLoop();
  
  std::string GetName() { return TestBox::Name(); }
  static std::string Name() { return std::string( "TestBox" ); }

  virtual void Render2d( RWWrapper& windowApp ) { } ;
  virtual void Render3d();
private:
  GUIs::DragArea* fDragArea;
  double fRotate;
};

} // ::Frames3d

} // ::Viewer

#endif
