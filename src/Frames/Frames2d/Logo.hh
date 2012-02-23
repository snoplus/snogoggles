////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Logo
///
/// \brief   Simple Frame, just displays the logo
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Logo__
#define __Viewer_Frames_Logo__

#include <Viewer/Frame.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
  class Sprite;
  class Text;
  class RenderState;

namespace Frames
{

class Logo : public Frame
{
public:
  Logo( RectPtr rect ) : Frame( rect ) { }
  ~Logo();

  void Initialise();
  void LoadConfiguration( ConfigurationTable& configTable );

  void SaveConfiguration( ConfigurationTable& configTable );

  virtual void EventLoop();
  
  virtual std::string GetName() { return Logo::Name(); }
  
  static std::string Name() { return std::string( "Logo" ); }

  virtual void Render2d( RWWrapper& renderApp, 
			 const RenderState& renderState );

  void Render3d( RWWrapper& renderApp, 
		 const RenderState& renderState ) { }

  EFrameType GetFrameType() { return eUtil; }
private:
  sf::Texture* fTextures[2]; /// < The two logo textures
  Sprite* fLogo; /// < The sprite
  Text* fMessage; /// < The message
  bool fState; /// < Which logo to display
};

} // ::Frames

} // ::Viewer

#endif
