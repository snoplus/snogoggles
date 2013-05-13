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
  /// Standard gui constructor
  RadioSelector( RectPtr rect, 
                 unsigned int guiID );
  /// Destructor
  virtual ~RadioSelector();
  /// Render the objects
  void Render( RWWrapper& renderApp );
  /// Event handler
  GUIEvent NewEvent( const Event& event );
  /// Initialise with a list of string options
  void Initialise( const std::vector<std::string>& options,
		   bool fixed ); /// < Fixed/Max 20 pixel height?
  /// Set the current state
  void SetState( unsigned int state );
  /// Return the state as an unsigned int
  unsigned int GetState() const;
  /// Return the state casted to the appropriate enum
  template < typename T > inline T GetEnumState() const;
protected:
  GUIManager fGUIManager; /// < Manage the persist labels
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
