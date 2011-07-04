////////////////////////////////////////////////////////////////////////
/// \class EventData
///
/// \brief   Current EventData data container
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     12/05/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_EventData__
#define __Viewer_EventData__

#include <vector>

#include <Viewer/Mutex.hh>

namespace RAT
{
namespace DS
{
  class Root;
  class EV;
  class PMTProperties;
}
}

namespace Viewer
{

class EventData
{
public:
  static EventData&
  GetInstance() 
  {
    if( fsEventData == NULL )
      fsEventData = new EventData();
    return *fsEventData;
  }

  ~EventData();

  RAT::DS::EV* GetCurrentEV();

  RAT::DS::PMTProperties* GetPMTList() { return fPMTList; }

  void SetPMTList( RAT::DS::PMTProperties* pmtList );
  bool AddEV( RAT::DS::EV* ev );

  RAT::DS::EV* NextEV();

  RAT::DS::EV* PreviousEV();
private:
  EventData();

  static EventData* fsEventData;

  Mutex fLock;
  std::vector<RAT::DS::EV*> fEVs; /// <Must Lock to access
  int fCurrentID; /// <Must Lock to access
  RAT::DS::PMTProperties* fPMTList;
  RAT::DS::EV* fCurrentEvent;
};

} //::Viewer

#endif
