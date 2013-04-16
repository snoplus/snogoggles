////////////////////////////////////////////////////////////////////////
/// \class Viewer::Fibre3d
///
/// \brief   Responsible for rendering fibres.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 15/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Displays a triangle for a fibre with a direction.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Fibre3d__
#define __Viewer_Fibre3d__

#include <SFML/System/Vector3.hpp>

#include <Viewer/Module3d.hh>
#include <Viewer/VBO.hh>

namespace Viewer
{

class Fibre3d : public Module3d
{
public:
  Fibre3d( RectPtr rect ) : Module3d( rect ) { }
  virtual ~Fibre3d() { }
  /// The event loop
  virtual void EventLoop();
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access, Nothing to do here
  virtual void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Process data into renderable format, Nothing to do here
  virtual void ProcessData( const RenderState& renderState );
  /// Render all 3d objects
  virtual void Render3d();
  /// Return the module name
  virtual std::string GetName() { return Fibre3d::Name(); }
  static std::string Name() { return std::string( "Fibre3d" ); }

protected:
  void AddPosVertices( VBO& vbo,
                       const sf::Vector3<double>& pos,
                       const Colour& colour );

  void AddDirVertices( VBO& vbo,
                       const sf::Vector3<double>& pos,
                       const sf::Vector3<double>& dir,
                       const Colour& colour );

  VBO fAMELLIEPos;
  VBO fAMELLIEDir;
  VBO fSMELLIEPos;
  VBO fSMELLIEDir;
  VBO fTELLIEPos;
  VBO fTELLIEDir;

  bool fDisplayAMELLIE;
  bool fDisplaySMELLIE;
  bool fDisplayTELLIE;
};

} //::Viewer

#endif
