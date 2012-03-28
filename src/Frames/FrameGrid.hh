////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameGrid
///
/// \brief   Controls the frame grid area.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     18/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class defines the frame grid, i.e. where the frames can
///          be and indeed are. Only the frame ids within the FrameManager
///          are used in this class.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameGrid__
#define __Viewer_FrameGrid__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class ConfigurationTable;

class FrameGrid
{
public:
  enum ESize { eSmallest, eLargest, eSmaller, eLarger };
  /// Construct the frame grid, requires a rect
  FrameGrid( RectPtr rect );
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable& configTable );
  /// Initialise without a configuration
  void Initialise();
  /// Load a configuration
  void LoadConfiguration( ConfigurationTable& configTable );
  /// Find space for a new frame, with id, returns false if no space is available
  bool NewFrame( unsigned int id,
                 sf::Rect<double>& rect );
  /// Remove the frame with id and correct other frames
  void RemoveFrame( unsigned int id,
                    unsigned int numFrames ); /// < Number of frames PRE removal
  /// Change the size of the frame, returns false if not possible
  bool ResizeFrame( unsigned int id, 
                    ESize size,
                    sf::Rect<double>& rect );
  /// Move the frame, returns false if not possible. position in resolution coords
  bool MoveFrame( unsigned int id, 
                  sf::Vector2<double> position,
                  sf::Rect<double>& rect ); 
  /// Check where the frame is, return false if not found
  bool CheckFrame( unsigned int id,
                   sf::Rect<double>& rect );
private:
  /// Increase the frame size, return false if failed.
  bool IncreaseFrame( unsigned int id,
                      unsigned int& col,
                      unsigned int& row,
                      unsigned int& cols,
                      unsigned int& rows );
  /// Increase the frame size, return false if failed.
  bool DecreaseFrame( unsigned int id,
                      unsigned int& col,
                      unsigned int& row,
                      unsigned int& cols,
                      unsigned int& rows );
  /// Remove the frame with id, do not alter other frames
  void RemoveFrame( unsigned int id );
  /// Check if grid square is available
  bool CheckEmptySquare( unsigned int id, 
                         unsigned int col, 
                         unsigned int row );
  /// Get extent of existing, return true if found
  bool GetExtent( unsigned int id,
                  unsigned int& col,
                  unsigned int& row,
                  unsigned int& cols,
                  unsigned int& rows );
  /// Convert grid positions to a rect object (rect in local coords)
  sf::Rect<double> GridToRect( unsigned int iCol, 
                               unsigned int iRow, 
                               unsigned int cols = 1,
                               unsigned int rows = 1 );
  
  std::vector< std::vector<int> > fGrid; /// < NxN grid of frame ids
  RectPtr fRect; /// < Grid rect area
  unsigned int fCols; /// < Number of columns
  unsigned int fRows; /// < Number of rows
};

} //::Viewer

#endif
