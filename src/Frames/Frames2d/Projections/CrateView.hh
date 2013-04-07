////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::CrateView
///
/// \brief   Displays information in crates from events
///
/// \author  Ken Clark <k.clark1@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     5/07/11 : K. Clark - added \n
///    21/02/12 : P.Jones - Refactor to use new Rect system.
///
/// \detail  Display the crate hit information, crates are ordered by 
///          crate id, then by card horizontally and channel vertically.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_CrateView__
#define __Viewer_CrateView__

#include <SFML/System/Vector2.hpp>

#include <Viewer/Frame2d.hh>

namespace Viewer 
{
  class ProjectionImage;
  class HitInfo;
  class Colour;
namespace GUIs
{
  class MapArea;
}

namespace Frames 
{

class CrateView : public Frame2d
{
public:
  CrateView( RectPtr rect ) : Frame2d( rect ) { }
  ~CrateView();
  
  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable ) { };
  
  virtual void EventLoop();
  
  virtual std::string GetName() { return CrateView::Name(); }
  
  static std::string Name() { return std::string( "Crate View" ); }

  virtual void ProcessData( const RenderState& renderState ) { }

  virtual void Render2d( RWWrapper& renderApp,
			 const RenderState& renderState );
  
  void Render3d( RWWrapper& renderApp,
		 const RenderState& renderState ) { }

  double GetAspectRatio() const { return 0.5; }
private:
  void DrawPMT( const int lcn,
		const Colour& colour );
  void DrawPMTs( const RenderState& renderState );

  sf::Vector2<double> fMousePos; /// < The mouse position (-1, -1) if not in frame
  int fPMTofInterest; /// < The PMT which is hoverred over
  GUIs::MapArea* fMapArea; /// < The map area gui
  ProjectionImage* fImage; /// < Image of the crates
  HitInfo* fHitInfo; /// < Hit info
};

}//Frames namespace

}//Viewer namespace

#endif
