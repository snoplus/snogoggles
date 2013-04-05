////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::DefaultFitter3d
///
/// \brief   Responsible for filtering and rendering reconstructed vertices.
///
/// \author Phil G Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 05/04/13 : P. Jones - New File \n
///
/// \details    
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_DefaultFitter3d__
#define __Viewer_Frames_DefaultFitter3d__

#include <Viewer/FitterManager3d.hh>
#include <Viewer/ReconBuffer.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/Colour.hh>
#include <TVector3.h>

#include <string>
#include <vector>

namespace Viewer 
{
namespace GUIs 
{
  class PersistLabel;
};
  
class ColourPalette;
class RenderState;
class ConfigurationTable;
class GUIManager;

namespace Frames 
{

class DefaultFitter3d : public FitterManager3d 
{
public:
  DefaultFitter3d();

  static std::string Name() { return "DefaultFitter"; }
  std::string GetName() { return Name(); }
  void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );
  void LoadConfiguration( const ConfigurationTable* configTable );
  void SaveConfiguration( ConfigurationTable* configTable );
  void EventLoop( );
  void ProcessData( const RenderState& renderState );
  void Render( const RenderState& renderState );
  
private:
  ReconBuffer fBuffer;

}; // class DefaultFitter3d

}; // namespace Frames 
}; // namespace Viewer

#endif // Viewer_Frames_DefaultFitter3d_hh
