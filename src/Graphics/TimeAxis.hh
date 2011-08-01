////////////////////////////////////////////////////////////////////////
/// \class Viewer::TimeAxis
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     01/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_TimeAxis__
#define __Viewer_TimeAxis__

#include <Viewer/PixelImage.hh>

namespace Viewer
{

class TimeAxis : public PixelImage
{
public:
  
  static double ScaleTime( double time );

  void Fill();
};

} // ::Viewer

#endif
