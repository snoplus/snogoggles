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
  /// Text scaling options, keep ascpect ratio by width, height or take target aspect ratio
  enum ETextScaling { eNone, eWidth, eHeight };
  /// Constructor, must pass a Rect
  inline Text( RectPtr localRect );
  /// Set the text string
  inline void SetString( const std::string& text );
  /// Set the Aspect ratio scaling
  inline void SetScaling( ETextScaling scaling );
  /// Return the local Rect (by reference)
  inline RectPtr GetRect();
  /// Return the text string
  inline std::string& GetString();
  /// Return the aspect ratio scaling
  inline ETextScaling GetScaling();

  inline void SetColour( const Colour& colour );

  inline Colour GetColour();
protected:
  std::string fString;   /// < The text string
  ETextScaling fScaling; /// < The text aspect ratio scaling
  Colour fColour; /// < The text colour
  RectPtr fLocalRect;    /// < The text local rect
};

inline 
Text::Text( RectPtr localRect )
  : fLocalRect( localRect )
{
  fScaling = eNone;
}

inline void 
Text::SetString( const std::string& text )
{
  fString = text;
}

inline void 
Text::SetScaling( Text::ETextScaling scaling )
{
  fScaling = scaling;
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

inline Text::ETextScaling 
Text::GetScaling()
{
  return fScaling;
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
