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

#include <Viewer/RIDS/Channel.hh>

namespace Viewer
{
namespace RIDS
{
  class Event;
}

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
  /// Reset the data
  void Reset();
  /// Return the vector of data labels
  std::vector<std::string> GetDataLabels() const { return fDataLabels; }
private:
  PyObject* NewEmptyPyList();
  PyObject* FillList( const RIDS::Event& event );

  std::vector<std::string> fDataLabels; /// < Script labels the data types
  std::string fCurrentScript;

  PyObject* fpScript; /// < The actual script
  PyObject* fpEventFunction; /// < Analyse event function
  PyObject* fpResetFunction; /// < Reset the script data function
  PyObject* fpData; /// < Data created by the script, this is displayed
};

} //::Viewer

#endif
