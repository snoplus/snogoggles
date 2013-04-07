////////////////////////////////////////////////////////////////////////
/// \class Text
///
/// \brief   A drawable string (text) defined in local coords
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     17/02/12 : P.Jones - Second Revision uses new Rect system. \n
///     20/04/12 : P.Jones - Third Revision, must now add lines separetly. \n
///
/// \detail  A string (text) with a position defined locally which can 
///          be drawn in global coords by sfml.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Text__
#define __Viewer_Text__

#include <string>
#include <vector>

#include <Viewer/RectPtr.hh>
#include <Viewer/Colour.hh>

namespace Viewer
{

class Text
{
public:
  /// Constructor, must pass a Rect
  inline Text( RectPtr localRect );
  /// Set the whole string (will clear first)
  void SetString( const std::string& text );
  /// Add a line of text
  void AddLine( const std::string& text );
  /// Clear the text
  inline void Clear();
  /// Get the number of lines
  inline unsigned int GetNumLines();
  /// Get the max line length
  inline unsigned int GetMaxLineLength();
  /// Return the local Rect (by reference)
  inline RectPtr GetRect();
  /// Return the text string
  std::string GetString() const;

  inline void SetColour( const Colour& colour );

  inline Colour GetColour();
protected:
  std::vector< std::string > fTextLines; /// < The lines of text string
  Colour fColour; /// < The text colour
  RectPtr fLocalRect; /// < The text local rect
  unsigned int fMaxLineLength;
};

inline 
Text::Text( RectPtr localRect )
  : fLocalRect( localRect )
{
  Clear();
}
  
inline void 
Text::Clear()
{
  fMaxLineLength = 0;
  fTextLines.clear();
}

inline unsigned int 
Text::GetNumLines()
{
  return fTextLines.size();
}

inline unsigned int 
Text::GetMaxLineLength()
{
  return fMaxLineLength;
}

inline RectPtr
Text::GetRect()
{
  return fLocalRect;
}

inline void
Text::SetColour( const Colour& colour )
{
  fColour = colour;
}

inline Colour
Text::GetColour()
{
  return fColour;
}

} // ::Viewer

#endif
