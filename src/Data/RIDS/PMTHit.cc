#include <Python.h>

#include <RAT/DS/PMTCal.hh>
#include <RAT/DS/PMTUnCal.hh>
#include <RAT/DS/PMTTruth.hh>
#include <RAT/DS/MCPMT.hh>

#include <Viewer/RIDS/PMTHit.hh>
using namespace Viewer::RIDS;

#include <iostream>
using namespace std;

PMTHit::PMTHit( double tac, 
                double qhl,
                double qhs,
                double qlx )
{
  fLCN = -1;
  fTAC = tac;
  fQHL = qhl;
  fQHS = qhs;
  fQLX = qlx;
}

PMTHit::PMTHit( RAT::DS::PMTCal* rPMTCal )
{
  fLCN = rPMTCal->GetID();
  fTAC = rPMTCal->GetsPMTt();
  fQHL = rPMTCal->GetsQHL();
  fQHS = rPMTCal->GetsQHS();
  fQLX = rPMTCal->GetsQLX();
}

PMTHit::PMTHit( RAT::DS::PMTUnCal* rPMTUnCal )
{
  fLCN = rPMTUnCal->GetID();
  fTAC = rPMTUnCal->GetsPMTt();
  fQHL = rPMTUnCal->GetsQHL();
  fQHS = rPMTUnCal->GetsQHS();
  fQLX = rPMTUnCal->GetsQLX();
}

PMTHit::PMTHit( RAT::DS::PMTTruth* rPMTTruth )
{
  fLCN = rPMTTruth->GetID();
  fTAC = rPMTTruth->GetsPMTt();
  fQHL = rPMTTruth->GetsQHL();
  fQHS = rPMTTruth->GetsQHS();
  fQLX = rPMTTruth->GetsQLX();
}

PMTHit::PMTHit( RAT::DS::MCPMT* rMCPMT )
{
  
}

PMTHit::PMTHit( PyObject* pData,
                int lcn )
{
  PyList_Check( pData ); // Throw on this??
  fLCN = lcn;
  fTAC = PyFloat_AsDouble( PyList_GetItem( pData, 0 ) );
  fQHL = PyFloat_AsDouble( PyList_GetItem( pData, 1 ) );
  fQHS = PyFloat_AsDouble( PyList_GetItem( pData, 2 ) );
  fQLX = PyFloat_AsDouble( PyList_GetItem( pData, 3 ) );
}

PMTHit::~PMTHit()
{

}

double
PMTHit::GetData( EDataType type ) const
{
  switch( type )
    {
    case eTAC:
      return fTAC;
    case eQHL:
      return fQHL;
    case eQHS:
      return fQHS;
    case eQLX:
      return fQLX;
    }
  return 0.0;
}

PyObject* 
PMTHit::NewPyList()
{
  PyObject* pList = PyList_New( 4 );
  PyObject* pTAC = PyFloat_FromDouble( fTAC );
  PyList_SetItem( pList, 0, pTAC );
  PyObject* pQHL = PyFloat_FromDouble( fQHL );
  PyList_SetItem( pList, 1, pQHL );
  PyObject* pQHS = PyFloat_FromDouble( fQHS );
  PyList_SetItem( pList, 2, pQHS );
  PyObject* pQLX = PyFloat_FromDouble( fQLX );
  PyList_SetItem( pList, 3, pQLX );
  return pList;
}
