////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::RadioSelector
///
/// \brief   A set of PersistLables with only one selectable at any time.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/06/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Multiple PersistLabels, only one can be selected at any time.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_RadioSelector__
#define __Viewer_GUIs_RadioSelector__

#include <vector>
#include <string>

#include <Viewer/GUI.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
namespace GUIs
{
  class PersistLabel;

class RadioSelector : public GUI
{
public:
  RadioSelector( RectPtr rect, 
                 unsigned int guiID );
  virtual ~RadioSelector();
 
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  void Initialise( const std::vector<std::string>& labels );

  void SetState( unsigned int state );
  /// Return the state as an unsigned int
  unsigned int GetState() const;
  /// Return the state casted to the appropriate enum
  template < typename T > inline T GetEnumState() const;
protected:
  GUIManager fGUIManager;
  std::vector< PersistLabel* > fPersistLabels; /// < The persist label buttons
};

template < typename T >
inline T
RadioSelector::GetEnumState() const
{
  return static_cast< T >( GetState() );
}

} // ::GUIs

} // ::Viewer

#endif
