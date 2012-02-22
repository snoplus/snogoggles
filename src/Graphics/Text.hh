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
///
/// \detail  A string (text) with a position defined locally which can 
///          be drawn in global coords by sfml.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Text__
#define __Viewer_Text__

#include <string>

#include <Viewer/RectPtr.hh>
#include <Viewer/Colour.hh>

namespace Viewer
{

class Text
{
public:
  /// Constructor, must pass a Rect
  inline Text( RectPtr localRect );
  /// Set the text string
  inline void SetString( const std::string& text );
  /// Return the local Rect (by reference)
  inline RectPtr GetRect();
  /// Return the text string
  inline std::string& GetString();

  inline void SetColour( const Colour& colour );

  inline Colour GetColour();
protected:
  std::string fString;   /// < The text string
  Colour fColour; /// < The text colour
  RectPtr fLocalRect;    /// < The text local rect
};

inline 
Text::Text( RectPtr localRect )
  : fLocalRect( localRect )
{

}

inline void 
Text::SetString( const std::string& text )
{
  fString = text;
}

inline RectPtr
Text::GetRect()
{
  return fLocalRect;
}

inline std::string& 
Text::GetString()
{
  return fString;
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
