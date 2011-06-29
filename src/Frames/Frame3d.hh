////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame3d
///
/// \brief   The base class for all 3d frames
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  All 3d Frames will derive from this.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame3d__
#define __Viewer_Frame3d__

#include <Viewer/Frame.hh>

namespace Viewer
{

class Frame3d : public Frame
{
public:
  /// Force 2d Rendering to do nothing
  void Render2d( sf::RenderWindow& windowApp ) {}; 
  virtual ~Frame3d() {}
};

} // ::Viewer

#endif
