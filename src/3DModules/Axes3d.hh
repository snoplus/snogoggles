////////////////////////////////////////////////////////////////////////
/// \class Viewer::Axes3d
///
/// \brief   The base class for all 3d modules
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original Axes3d class to take account
///          of codebase changes.
///          Draws the x, y, z axes into the viewport area
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Axes3d__
#define __Viewer_Axes3d__

#include <SFML/System/Vector3.hpp>

#include <Viewer/Module3d.hh>

namespace Viewer
{
  class Colour;

class Axes3d : public Module3d
{
public:
  Axes3d( RectPtr rect ) : Module3d( rect ), fDisplay( true ) { }
  virtual ~Axes3d() { }
  /// The event loop
  virtual void EventLoop();
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access, Nothing to do here
  virtual void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Process data into renderable format, Nothing to do here
  virtual void ProcessData( const RenderState& renderState ) { };
  /// Render all 3d objects
  virtual void Render3d();
  /// Return the module name
  virtual std::string GetName() { return Axes3d::Name(); }
  static std::string Name() { return std::string( "Axes3d" ); }
protected:
  /// Render a single axis
  void RenderAxis( const sf::Vector3<double>& point,
                   Colour colour );
  bool fDisplay; /// < Show the axes?
};

} //::Viewer

#endif
