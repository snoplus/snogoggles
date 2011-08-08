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
  CheckBoxLabel( const sf::Rect<double>& rect, unsigned int guiID );
  virtual ~CheckBoxLabel();

  void SetLabel( const std::string& label );

  void RenderT( sf::RenderWindow& windowApp );
  void Render( RWWrapper& windowApp );
protected:
  Sprite fBox[2];
  Text fLabel;
};

} // ::GUIs

} // ::Viewer

#endif
