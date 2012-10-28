////////////////////////////////////////////////////////////////////////
/// \class EventSelectionScript
///
/// \brief   Controls the event selection scripts
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     27/10/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Holds the python api pointers to the script.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_EventSelectionScript__
#define __Viewer_EventSelectionScript__

// Special Python object forward declaration
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif

#include <string>

namespace Viewer
{
namespace RIDS
{
  class Event;
}

class EventSelectionScript
{
public:
  EventSelectionScript();
  ~EventSelectionScript();

  /// Load a script
  void Load( const std::string& scriptName );
  /// Un load the python script
  void UnLoad();
  /// Process the event
  bool ProcessEvent( const RIDS::Event& event );  
private:
  std::string fCurrentScript;

  PyObject* fpScript;
  PyObject* fpSelectFunction;
};

} //::Viewer

#endif
