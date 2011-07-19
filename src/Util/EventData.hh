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
#include <map>

#include <Viewer/Mutex.hh>

namespace RAT
{
namespace DS
{
  class Root;
  class EV;
  class Run;
  class MC;
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
  RAT::DS::MC* GetCurrentMC();

  RAT::DS::Run* GetRun() { return fRun; }

  void SetRun( RAT::DS::Run* run );
  bool AddEV( RAT::DS::EV* ev, int mcEvent );
  bool AddMC( RAT::DS::MC* mc );

  void NextEV();

  void PreviousEV();

  void GetEVData( int& currentEV, int& evCount );
  void GetMCData( int& currentMC, int& mcCount );
private:
  EventData();

  static EventData* fsEventData;

  Mutex fLock;
  std::vector<RAT::DS::EV*> fEVs; /// <Must Lock to access
  std::vector<RAT::DS::MC*> fMCs; /// <Must Lock to access
  std::map< int, int > fEVToMC; /// <Must Lock to access, mapping from EV number to MC number
  int fCurrentID; /// <Must Lock to access
  RAT::DS::Run* fRun;
  RAT::DS::EV* fCurrentEvent;
  RAT::DS::MC* fCurrentMC;
};

} //::Viewer

#endif
