////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::CheckBoxLabel
///
/// \brief   Label with a check box next to it
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     30/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_CheckBoxLabel__
#define __Viewer_GUIs_CheckBoxLabel__

#include <string>

#include <Viewer/Persist.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Text.hh>

namespace Viewer
{ 
namespace GUIs
{

class CheckBoxLabel : public Persist
{
public:
  CheckBoxLabel( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~CheckBoxLabel();

  void SetLabel( const std::string& label );

  void Render( RWWrapper& windowApp );
  inline double PreferedRatio();
protected:
  Sprite fBox;
  Text fLabel;
};

double
CheckBoxLabel::PreferedRatio()
{
  return 1.0;
}

} // ::GUIs

} // ::Viewer

#endif
