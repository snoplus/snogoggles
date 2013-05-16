#include <RAT/DS/Root.hh>

using namespace std;

#include <Viewer/LoadZdabFileThread.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>

#include <zdab_file.hpp>

void
LoadZdabFileThread::InitialiseRIDS()
{
  vector< pair< string, vector< string > > > dataNames;
  vector<string> uncalTypes; uncalTypes.push_back( "TAC" ); uncalTypes.push_back( "QHL" ); uncalTypes.push_back( "QHS" ); uncalTypes.push_back( "QLX" );
  dataNames.push_back( pair< string, vector< string > >( "UnCal", uncalTypes ) );
  RIDS::Event::Initialise( dataNames );
}

void
LoadZdabFileThread::Run()
{
  if( fFile == NULL )
    {
      InitialiseRIDS();
      fFile = new ratzdab::zdabfile( fFileName.c_str() );
      LoadNextEvent();
      fSemaphore.Signal();
      fMCEvent++;
      return;
    }
  bool success = LoadNextEvent();
  fMCEvent++;
  cout << "Loaded " << fMCEvent << " events." << endl;  
  if( !success )
    {
      delete fFile;
      Kill();
    }
}

bool
LoadZdabFileThread::LoadNextEvent()
{
  try
    {
      TObject* record = fFile->next();
      if( record == NULL )
        return false;
      if( record->IsA() == RAT::DS::Root::Class() ) 
        {
          RAT::DS::Root* ds = new RAT::DS::Root( *reinterpret_cast<RAT::DS::Root*>( record ) );
          BuildRIDSEvent( ds );
          delete ds;
          return true;
        }
      else // Iterate through until an event is located
        return LoadNextEvent();
    }
  catch( ratzdab::unknown_record_error& e )
    {
      return LoadNextEvent(); // Carry on and try again...
    }
}

void
LoadZdabFileThread::BuildRIDSEvent( RAT::DS::Root* rDS )
{
  RAT::DS::EV* rEV = rDS->GetEV( 0 );
  RIDS::Source unCal( 4 );
  RIDS::Type tac, qhl, qhs, qlx;
  for( int iUnCal = 0; iUnCal < rEV->GetPMTUnCalCount(); iUnCal++ )
    {
      RAT::DS::PMTUnCal* rPMTUnCal = rEV->GetPMTUnCal( iUnCal );
      tac.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetTime() );
      qhl.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetsQHL() );
      qhs.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetsQHS() );
      qlx.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetsQLX() );
    }
  unCal.SetType( 0, tac );
  unCal.SetType( 1, qhl );
  unCal.SetType( 2, qhs );
  unCal.SetType( 3, qlx );
  RIDS::Event* event = new RIDS::Event();
  event->SetSource( 0, unCal );
  event->SetRunID( rDS->GetRunID() );
  event->SetSubRunID( rDS->GetSubRunID() );
  event->SetEventID( rDS->GetEV( 0 )->GetEventID() );
  event->SetTrigger( rDS->GetEV( 0 )->GetTrigType() );
  event->SetTime( RIDS::Time( rEV->GetClockCount10() ) );
  DataStore::GetInstance().AddEvent( event );
}
