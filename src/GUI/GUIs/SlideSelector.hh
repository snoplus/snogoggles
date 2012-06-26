////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::SlideSelector
///
/// \brief   SlideSelector GUI object
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     26/06/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Sliding bar with fixed selection points.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_SlideSelector__
#define __Viewer_GUIs_SlideSelector__

#include <vector>

#include <Viewer/GUI.hh>

namespace Viewer
{
  class ProjectionImage;
namespace GUIs
{

class SlideSelector : public GUI
{
public:
  SlideSelector( RectPtr rect, 
                 unsigned int guiID );
  virtual ~SlideSelector();
  void Initialise( std::vector<double> stops );
  
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  inline void SetState( double position );
  inline double GetState() const;
protected:
  std::vector<double> fStops; /// < Pre set stop points
  double fCurrentPos; /// < Current Position
  ProjectionImage* fImage; /// < Bar is projected onto the screen
  bool fSliding; /// < Is the user sliding at the moment?
};

void
SlideSelector::SetState( double position )
{
  fCurrentPos = position;
}

double
SlideSelector::GetState() const
{
  return fCurrentPos;
}

} // ::GUIs

} // ::Viewer

#endif
