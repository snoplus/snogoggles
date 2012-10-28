#include <Python.h>

#include <Viewer/PythonScripts.hh>
using namespace Viewer;

PythonScripts::PythonScripts()
{ 
  Py_InitializeEx(0); // Must be FIRST
  fAnalysis = new AnalysisScript();
  fEventSelection = new EventSelectionScript();
  fPMTSelection = new PMTSelectionScript();
}


PythonScripts::~PythonScripts()
{
  delete fAnalysis;
  delete fEventSelection;
  delete fPMTSelection;
  Py_Finalize();
}

void
PythonScripts::Initialise()
{
  fAnalysis->Load( "default" );
  fEventSelection->Load( "ev_default" );
  fPMTSelection->Load( "pmt_default" );
}
