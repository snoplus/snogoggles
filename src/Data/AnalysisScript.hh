////////////////////////////////////////////////////////////////////////
/// \class AnalysisScript
///
/// \brief   Controls the analysis scripts
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     27/10/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Holds the python api pointers to the script and the data
///          produced by the script.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_AnalysisScript__
#define __Viewer_AnalysisScript__

// Special Python object forward declaration
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif

#include <vector>
#include <string>

#include <Viewer/RIDS/Event.hh>

namespace Viewer
{

class AnalysisScript
{
public:
  AnalysisScript();
  ~AnalysisScript();

  /// Load a script
  void Load( const std::string& scriptName );
  /// Un load the python script
  void UnLoad();

  /// Process the event
  void ProcessEvent( const RIDS::Event& event );  
  /// Reset the accumulated data
  void Reset();
  /// Return the vector of type labels
  std::vector<std::string> GetTypeNames() const { return fTypes; }
  
private:
  /// Convert fpData to fEvent
  void PyToRIDS();

  std::vector<std::string> fTypes; /// < Script labels the data types
  std::string fCurrentScript; /// < Name of the current script
  RIDS::Event fEvent; /// < Data created by the script, RIDS format

  PyObject* fpScript; /// < The actual script
  PyObject* fpEventFunction; /// < Analyse event function
  PyObject* fpResetFunction; /// < Reset the script data function
  PyObject* fpData; /// < Data created by the script, Py format
};

} //::Viewer

#endif
