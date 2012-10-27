#include <Python.h>

#include <Viewer/PythonScripts.hh>
using namespace Viewer;

PythonScripts::PythonScripts()
{ 
  Py_InitializeEx(0);
}


PythonScripts::~PythonScripts()
{
  Py_Finalize();
}

void
PythonScripts::Initialise()
{
  fAnalysis.Load( "default" );
  fEventSelection.Load( "ev_default" );
  fPMTSelection.Load( "pmt_default" );
}
