////////////////////////////////////////////////////////////////////////
/// \class PythonScripts
///
/// \brief   Holds all the python scripts.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     27/10/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Holds and initialises the python scripts. This is a singleton.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_PythonScripts__
#define __Viewer_PythonScripts__

#include <Viewer/AnalysisScript.hh>
#include <Viewer/EventSelectionScript.hh>
#include <Viewer/PMTSelectionScript.hh>

namespace Viewer
{

class PythonScripts
{
public:
  static PythonScripts& GetInstance();

  void Initialise();

  AnalysisScript& GetAnalysis() { return fAnalysis; }
  EventSelectionScript& GetEventSelection() { return fEventSelection; }
  PMTSelectionScript& GetPMTSelection() { return fPMTSelection; }

  ~PythonScripts();
private:
  AnalysisScript fAnalysis;
  EventSelectionScript fEventSelection;
  PMTSelectionScript fPMTSelection;

  /// Prevent usage of methods below
  PythonScripts();
  PythonScripts( PythonScripts& );
  void operator=( PythonScripts& );
};

inline PythonScripts&
PythonScripts::GetInstance()
{
  static PythonScripts instance;
  return instance;
}

} //::Viewer

#endif
