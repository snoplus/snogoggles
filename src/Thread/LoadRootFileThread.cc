#include <RAT/DS/Root.hh>
#include <RAT/DS/Run.hh>
using namespace RAT;

#include <TTree.h>
#include <TFile.h>
using namespace ROOT;

#include <sstream>
#include <iostream>
using namespace std;

#include <Viewer/LoadRootFileThread.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/Source.hh>
#include <Viewer/RIDS/Type.hh>
#include <Viewer/RIDS/Track.hh>

void
LoadRootFileThread::Run()
{
  if( fTree == NULL )
    {
      LoadRootFile();
      fTree->GetEntry( fMCEvent );
      InitialiseRIDS();
      BuildRIDSEvent();
      fSemaphore.Signal();
      fMCEvent++;
      return;
    }
  if( fMCEvent >= fTree->GetEntries() )
    {
      fFile->Close();
      delete fFile;
      delete fDS;
      delete fRun;

      Kill();
    }
  else
    {
      fTree->GetEntry( fMCEvent );
      BuildRIDSEvent();
      fMCEvent++;
      cout << "Loaded " << fMCEvent << " events." << endl;
    }
}

void
LoadRootFileThread::InitialiseRIDS()
{
  vector< pair< string, vector< string > > > dataNames;
  vector<string> mcTypes; mcTypes.push_back( "TAC" ); mcTypes.push_back( "PE" );
  dataNames.push_back( pair< string, vector< string > >( "MC", mcTypes ) );
  vector<string> truthTypes; truthTypes.push_back( "TAC" ); truthTypes.push_back( "QHL" ); truthTypes.push_back( "QHS" ); truthTypes.push_back( "QLX" );
  dataNames.push_back( pair< string, vector< string > >( "Truth", truthTypes ) );
  vector<string> uncalTypes; uncalTypes.push_back( "TAC" ); uncalTypes.push_back( "QHL" ); uncalTypes.push_back( "QHS" ); uncalTypes.push_back( "QLX" );
  dataNames.push_back( pair< string, vector< string > >( "UnCal", uncalTypes ) );
  vector<string> calTypes; calTypes.push_back( "TAC" ); calTypes.push_back( "QHL" ); calTypes.push_back( "QHS" ); calTypes.push_back( "QLX" );
  dataNames.push_back( pair< string, vector< string > >( "Cal", calTypes ) );
  RIDS::Event::Initialise( dataNames );
}

void
LoadRootFileThread::BuildRIDSEvent()
{
  for( int iEV = 0; iEV < fDS->GetEVCount(); iEV++ )
    {
      RIDS::Event* event = new RIDS::Event();
      event->SetRunID( fDS->GetRunID() );
      event->SetSubRunID( fDS->GetSubRunID() );
      event->SetEventID( fDS->GetEV( iEV )->GetEventID() );
      event->SetTrigger( fDS->GetEV( iEV )->GetTrigType() );
      if( fDS->ExistMC() )
        {
          RAT::DS::MC* rMC = fDS->GetMC();
          for( int iMCParticle = 0; iMCParticle < rMC->GetMCParticleCount(); iMCParticle++ )
            {
              RAT::DS::MCParticle* rMCParticle = rMC->GetMCParticle( iMCParticle );
              RIDS::Vertex vertex;
              vertex.SetPosition( sf::Vector3<double>( rMCParticle->GetPos().x(), 
                                                       rMCParticle->GetPos().y(), 
                                                       rMCParticle->GetPos().z() ) );
              vertex.SetTime( rMCParticle->GetTime() );
              stringstream name;
              name << "MC" << iMCParticle;
              vertex.SetName( name.str() );
              event->AddVertex( vertex );
            }

          RIDS::Source mc( 2 );
          RIDS::Type tac, pe;
          for( int iMCPMT = 0; iMCPMT < rMC->GetMCPMTCount(); iMCPMT++ )
            {
              RAT::DS::MCPMT* rMCPMT = rMC->GetMCPMT( iMCPMT );
              tac.AddChannel( rMCPMT->GetPMTID(), rMCPMT->GetMCPhoton( 0 )->GetHitTime() );
              pe.AddChannel( rMCPMT->GetPMTID(), rMCPMT->GetMCPhotonCount() );
            }
          mc.SetType( 0, tac );
          mc.SetType( 1, pe );
          event->SetSource( 0, mc );
          // Now tracking information
          vector<RIDS::Track> tracks;
          for( int iTrack = 0; iTrack < rMC->GetMCTrackCount(); iTrack++ )
            tracks.push_back( RIDS::Track( *rMC->GetMCTrack( iTrack ) ) );
          event->SetTracks( tracks );
        }

      RAT::DS::EV* rEV = fDS->GetEV( iEV );
      for( map<string, RAT::DS::FitResult>::iterator iTer = rEV->GetFitResultIterBegin(); iTer != rEV->GetFitResultIterEnd(); iTer++ )
        {
          RIDS::Vertex vertex;
          vertex.SetName( iTer->first );
          try
            {
              vertex.SetPosition( sf::Vector3<double>( iTer->second.GetVertex( 0 ).GetPosition().x(),
                                                       iTer->second.GetVertex( 0 ).GetPosition().y(),
                                                       iTer->second.GetVertex( 0 ).GetPosition().z() ) );
              vertex.SetTime( iTer->second.GetVertex( 0 ).GetTime() );
            }
          catch( RAT::DS::FitResult::NoVertexError& error )
            {
              // Strange
            }
          catch( RAT::DS::FitVertex::NoValueError& error )
            {
              // Oh well...
            }
          event->AddVertex( vertex );
        }

      {
        RIDS::Source truth( 4 );
        RIDS::Type tac, qhl, qhs, qlx;
        for( int iTruth = 0; iTruth < rEV->GetPMTTruthCount(); iTruth++ )
          {
            RAT::DS::PMTTruth* rPMTTruth = rEV->GetPMTTruth( iTruth );
            tac.AddChannel( rPMTTruth->GetID(), rPMTTruth->GetTime() );
            qhl.AddChannel( rPMTTruth->GetID(), rPMTTruth->GetsQHL() );
            qhs.AddChannel( rPMTTruth->GetID(), rPMTTruth->GetsQHS() );
            qlx.AddChannel( rPMTTruth->GetID(), rPMTTruth->GetsQLX() );
          }
        truth.SetType( 0, tac );
        truth.SetType( 1, qhl );
        truth.SetType( 2, qhs );
        truth.SetType( 3, qlx );
        event->SetSource( 1, truth );
      }
      {
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
        event->SetSource( 2, unCal );
      }
      {
        RIDS::Source cal( 4 );
        RIDS::Type tac, qhl, qhs, qlx;
        for( int iCal = 0; iCal < rEV->GetPMTCalCount(); iCal++ )
          {
            RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( iCal );
            tac.AddChannel( rPMTCal->GetID(), rPMTCal->GetTime() );
            qhl.AddChannel( rPMTCal->GetID(), rPMTCal->GetsQHL() );
            qhs.AddChannel( rPMTCal->GetID(), rPMTCal->GetsQHS() );
            qlx.AddChannel( rPMTCal->GetID(), rPMTCal->GetsQLX() );
          }
        cal.SetType( 0, tac );
        cal.SetType( 1, qhl );
        cal.SetType( 2, qhs );
        cal.SetType( 3, qlx );
        event->SetSource( 3, cal );
      }
      DataStore::GetInstance().AddEvent( event );
    }
}

void
LoadRootFileThread::LoadRootFile()
{
  fFile = new TFile( fFileName.c_str(), "READ" );
 
  fTree = (TTree*)fFile->Get( "T" ); 
  fDS = new RAT::DS::Root();
  fTree->SetBranchAddress( "ds", &fDS );

  fRunTree = (TTree*)fFile->Get( "runT" ); 
  fRun = new RAT::DS::Run();
  fRunTree->SetBranchAddress( "run", &fRun );
  fRunTree->GetEntry();
}
