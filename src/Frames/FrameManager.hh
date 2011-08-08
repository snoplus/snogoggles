////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameManager
///
/// \brief   Manages the Frames' existance, position and size
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  All viewer frames are managed by this class.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameManager__
#define __Viewer_FrameManager__

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <string>

#include <Viewer/FrameUIReturn.hh>

namespace sf
{
  class RenderWindow;
}

namespace Viewer
{
  class UIEvent;
  class Configuration;
  class FrameContainer;
  class Frame;

class FrameManager
{
public:
  /// Initialise without any configuration
  void Initialise();
  /// Initialise with a configuration
  void LoadConfiguration( Configuration& config );
  
  void EventLoop();
  void RenderGUI( sf::RenderWindow& windowApp );
  void Render2d( sf::RenderWindow& windowApp );
  void Render3d();

  void NewEvent( UIEvent& event ); 
  void SaveConfiguration( Configuration& config );

  void NewFrame( const std::string& type );
private:
  FrameUIReturn DispatchEvent( UIEvent& event, int iFrame );
  void EventHandler( FrameUIReturn& retEvent, UIEvent& event );
  int FindFrame( const sf::Vector2<double>& resolutionCoord );

  void DeleteFrame( const int iFrame );
  void PositionFrame( int iFrame, const sf::Vector2<double>& position );
  enum ESize { eMinimal, eLargest, eSmaller, eLarger, eToGrid };
  void ResizeFrame( int iFrame, ESize size, bool calcGrid = true );

  bool CheckPosition( int iFrame, int row, int col, int rowSize, int colSize );
  void CalculateGrid();
  void DrawGrid( sf::RenderWindow& windowApp );  

  std::vector< std::vector<int> > fFrameGrid;
  int fCols;
  int fRows;
  double fColSize;
  double fRowSize;

  std::vector<FrameContainer*> fFrameContainers;
  Frame* fMasterUI;
  int fFocus;
  bool fMoving;
  sf::Vector2<double> fMoveOffset;
  sf::Vector2<double> fMoveStart;
};

} // ::Viewer

#endif
