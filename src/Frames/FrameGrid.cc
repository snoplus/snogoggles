#include <SFML/Graphics/Rect.hpp>

#include <algorithm>
using namespace std;

#include <Viewer/FrameGrid.hh>
#include <Viewer/Rect.hh>
using namespace Viewer;

const double kMinFrameWidth = 140.0;

FrameGrid::FrameGrid( RectPtr rect )
  : fRect( rect )
{
  sf::Rect<double> gridSpace = fRect->GetRect( Rect::eResolution );
  fCols = static_cast<unsigned int>( gridSpace.Width / kMinFrameWidth ); 
  double colWidth = gridSpace.Width / static_cast<double>( fCols );
  fRows = static_cast<unsigned int>( gridSpace.Height / colWidth );
  fGrid.resize( fCols, vector<int>( fRows, -2 ) );
}

bool
FrameGrid::NewFrame( unsigned int id,
		     sf::Rect<double>& rect )
{
  for( unsigned int iCol = 0; iCol < fCols; iCol++ )
    for( unsigned int iRow = 0; iRow < fRows; iRow++ )
      if( CheckEmptySquare( id, iCol, iRow ) ) // Found a free square so return the answer
	{
	  rect = GridToRect( iCol, iRow );
	  return true;
	}
  // Failed to find space, thus return NULL
  return false;
}

void 
FrameGrid::RemoveFrame( unsigned int id, 
			unsigned int numFrames )
{
  RemoveFrame( id );// Remove the frame first
  // Now correct the other frame ids (lower them by 1)
  for( unsigned int iFrame = id + 1; iFrame < numFrames; iFrame++ )
    for( unsigned int iCol = 0; iCol < fCols; iCol++ )
      for( unsigned int iRow = 0; iRow < fRows; iRow++ )
	if( fGrid[iCol][iRow] == iFrame )
	  fGrid[iCol][iRow] = iFrame - 1;
}

bool
FrameGrid::ResizeFrame( unsigned int id, 
			ESize size,
			sf::Rect<double>& rect )
{
  unsigned int col, row, cols, rows;
  switch( size )
    {
    case eSmallest:
      {
	if( GetExtent( id, col, row, cols, rows ) )
	  {
	    while( DecreaseFrame( id, col, row, cols, rows ) );
	    rect = GridToRect( col, row );
	    return true;
	  }
	else // Something went wrong, return false
	  return false;
      }
      break;
    case eLargest:
      {
	if( GetExtent( id, col, row, cols, rows ) )
	  {
	    while( IncreaseFrame( id, col, row, cols, rows ) );
	    rect = GridToRect( col, row );
            return true;
	  }
	else // Something went wrong, return false
	  return false;
      }
      break;
    case eLarger:
      {
	if( GetExtent( id, col, row, cols, rows ) )
          {
            IncreaseFrame( id, col, row, cols, rows );
            rect = GridToRect( col, row );
            return true;
          }
        else // Something went wrong, return false
          return false;
      }
      break;
    case eSmaller:
      {
        if( GetExtent( id, col, row, cols, rows ) )
          {
            DecreaseFrame( id, col, row, cols, rows );
            rect = GridToRect( col, row );
            return true;
          }
        else // Something went wrong, return false
          return false;
      }
      break;	
    }
}

bool
FrameGrid::MoveFrame( unsigned int id, 
		      sf::Vector2<double> position,
		      sf::Rect<double>& rect )
{
  // Always minimises the frame size
  sf::Rect<double> gridSpace = fRect->GetRect( Rect::eResolution );
  unsigned int testCol = static_cast<unsigned int>( position.x / gridSpace.Width );
  unsigned int testRow = static_cast<unsigned int>( position.y / gridSpace.Height );
  if( CheckEmptySquare( id, testCol, testRow ) ) // Can move square
    { 
      RemoveFrame( id );
      fGrid[testCol][testRow] = id;
      rect = GridToRect( testCol, testRow );
      return true;
    }
  return false;
}

bool
FrameGrid::IncreaseFrame( unsigned int id,
			  unsigned int& col,
			  unsigned int& row,
			  unsigned int& cols,
			  unsigned int& rows )
{
  // Check one larger
  bool success = true;
  for( unsigned int iCol = col + cols; col + cols + 1; iCol++ )
    for( unsigned int iRow = row + rows; row + rows + 1; iRow++ )
      success = success && CheckEmptySquare( id, iCol, iRow );
  if( success )
    {
      for( unsigned int iCol = col + cols; col + cols + 1; iCol++ )
	for( unsigned int iRow = row + rows; row + rows + 1; iRow++ )
	  fGrid[iCol][iRow] = id;
      cols += 1;
      rows += 1;
    }
  return success;
}

bool
FrameGrid::DecreaseFrame( unsigned int id,
                          unsigned int& col,
                          unsigned int& row,
                          unsigned int& cols,
                          unsigned int& rows )
{
  if( cols == 1 || rows == 1 )
    return false;
  // Always possible here
  for( unsigned int iCol = col + cols - 1; col + cols; iCol++ )
    for( unsigned int iRow = row + rows - 1; row + rows; iRow++ )
      fGrid[iCol][iRow] = -1;
  cols += 1;
  rows += 1;
  return true;
}

void
FrameGrid::RemoveFrame( unsigned int id )
{
  for( unsigned int iCol = 0; iCol < fCols; iCol++ )
    for( unsigned int iRow = 0; iRow < fRows; iRow++ )
      if( fGrid[iCol][iRow] == id )
        fGrid[iCol][iRow] = -1;
}

bool 
FrameGrid::CheckEmptySquare( unsigned int id, 
			     unsigned int col, 
			     unsigned int row )
{
  if( col >= fCols || row >= fRows )
    return false;
  if( fGrid[col][row] == -1 || fGrid[col][row] == id )
    return true;
  return false;
}

bool
FrameGrid::GetExtent( unsigned int id, 
		      unsigned int& col,
		      unsigned int& row,
		      unsigned int& cols,
		      unsigned int& rows )
{
  bool found = false;
  // Initialise vars
  col = -1; row = -1; cols = -1; rows = -1;
  for( unsigned int iCol = 0; iCol < fCols; iCol++ )
    for( unsigned int iRow = 0; iRow < fRows; iRow++ )
      {
	if( fGrid[iCol][iRow] == id && found == false )
	  {
	    col = iCol;
	    row = iRow;
	    cols = 0;
	    rows = 0;
	    found = true;
	  }
	else if( fGrid[iCol][iRow] == id && found == true )
	  {
	    cols = max( cols, iCol );
	    rows = max( rows, iRow );
	  }
      }
  cols -= col;
  rows -= row;
  return found;
}

sf::Rect<double>
FrameGrid::GridToRect( unsigned int col, 
		       unsigned int row,
		       unsigned int cols,
		       unsigned int rows )
{
  sf::Rect<double> space; // In local coords
  space.Left   = (double) col / (double) fCols;
  space.Top    = (double) row / (double) fRows;
  space.Width  = (double) rows / (double) fRows;
  space.Height = (double) cols / (double) fCols;
  return space;
}
