////////////////////////////////////////////////////////////////////////
/// \class ScriptData
///
/// \brief   Produces and holds the data as produced by the current script
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     10/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_ScriptData__
#define __Viewer_ScriptData__

// Special Python object forward declaration
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif

#include <vector>
#include <string>

#include <Viewer/RIDS/PMTHit.hh>
#include <Viewer/RIDS/Event.hh>

namespace Viewer
{

class ScriptData
{
public:
  ScriptData();
  ~ScriptData();

  /// Load a script
  void Load( const std::string& scriptName );
  /// Reset the data and clear
  void Clear();
  /// Process the event
  void ProcessEvent( const RIDS::Event& event );  

  std::vector<RIDS::PMTHit> GetHitData() const;
private:
  PyObject* NewEmptyPyList();
  PyObject* FillList( const RIDS::Event& event,
                      RIDS::EDataSource source );

  PyObject* fpScript;
  PyObject* fpFunction;
  PyObject* fpData;
};

} //::Viewer

#endif
