////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame2d
///
/// \brief   The base class for all 2d frames
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  All 2d Frames will derive from this.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame2d__
#define __Viewer_Frame2d__

#include <Viewer/Frame.hh>

namespace Viewer
{

class Frame2d : public Frame
{
public:
  /// Force 3d Rendering to do nothing
  void Render3d( sf::RenderWindow& windowApp ) {}; 
  virtual ~Frame2d() {}
};

} // ::Viewer

#endif
