////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::ProjectionBase
///
/// \brief   Base frame for projections
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     21/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  All projection frame classes should just override the 
///          project function, which converts a 3d point into a 2d point.
///          The project function is pure virtual and hence this is an
///          abstract class
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_ProjectionBase__
#define __Viewer_Frames_ProjectionBase__

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <Viewer/Frame.hh>

namespace Viewer
{
  class ProjectionImage;

namespace Frames
{

class ProjectionBase : public Frame
{
public:
  ProjectionBase( RectPtr rect ) : Frame( rect ) { }
  virtual ~ProjectionBase();

  void Initialise( const sf::Rect<double>& size );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* configTable );
  /// Save the configuration
  void SaveConfiguration( ConfigurationTable* configTable ) { };

  virtual void EventLoop();
  
  virtual std::string GetName() = 0;

  virtual void ProcessData( const RenderState& renderState ) { }

  virtual void Render2d( RWWrapper& renderApp, 
			 const RenderState& renderState );

  void Render3d( RWWrapper& renderApp, 
		 const RenderState& renderState ) { }

  //EFrameType GetFrameType() { return eUtil; }
  virtual void DrawOutline() { };
protected:

  void ProjectGeodesicLine( sf::Vector3<double> v1, 
                            sf::Vector3<double> v2 );
  void DrawHits( const RenderState& renderState );
  void DrawGeodesic();
  void DrawAllPMTs();

  virtual sf::Vector2<double> Project( sf::Vector3<double> pmtPos ) = 0;
  
  std::vector< sf::Vector2<double> > fProjectedPMTs; /// < Vector of projected pmt positions
  std::vector< sf::Vector2<double> > fProjectedGeodesic; /// < Vecotr of projected geodesic positions
  ProjectionImage* fImage;
};

} // ::Frames

} // ::Viewer

#endif
