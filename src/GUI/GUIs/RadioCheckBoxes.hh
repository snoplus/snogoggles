////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::RadioCheckBoxes
///
/// \brief   A set of check boxes with only one selectable at any time.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     21/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Multiple check boxes, only one can be selected at any time.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_RadioCheckBoxes__
#define __Viewer_GUIs_RadioCheckBoxes__

#include <vector>
#include <string>

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
namespace GUIs
{
  class CheckBoxLabel;

class RadioCheckBoxes : public GUI
{
public:
  inline RadioCheckBoxes( RectPtr rect, 
			  unsigned int guiID );
  virtual ~RadioCheckBoxes();
 
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  void Initialise( const std::vector<std::string>& labels );
  void SetState( unsigned int state );
  /// Return the state as an unsigned int
  unsigned int GetState() const;
  /// Return the state casted to the appropriate enum
  template < typename T > inline T GetEnumState() const;

protected:
  std::vector< CheckBoxLabel* > fRadioCheckBoxes; /// < The actual check boxes
};

inline
RadioCheckBoxes::RadioCheckBoxes( RectPtr rect, 
				  unsigned int guiID ) 
  : GUI( rect, guiID )
{ 

}

template < typename T > 
inline T
RadioCheckBoxes::GetEnumState() const
{
  return static_cast< T >( GetState() );
}

} // ::GUIs

} // ::Viewer

#endif
