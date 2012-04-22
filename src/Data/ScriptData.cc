#include <RAT/DS/PMTCal.hh>
#include <RAT/DS/Root.hh>
#include <RAT/Extensible.hh>

#include <sstream>
#include <stdlib.h>
using namespace std;

#include <Viewer/ScriptData.hh>
using namespace Viewer;

const int kNumChannels = 10000; // This just needs to be greater or equal to the max lcn

ScriptData::ScriptData()
{
  for( int i = 0; i < kNumChannels; i++ )
    {
      RAT::DS::PMTCal* pmtCal = RAT::Extensible<RAT::DS::PMTCal>::New();
      pmtCal->SetID( i );
      fPyResultArray.Add( pmtCal );
    }
  ChangeScript( "Example.py" );
  Clear();
}

void
ScriptData::ChangeScript( const std::string& fileName )
{
  stringstream fullFileName;
  fullFileName << getenv( "VIEWERROOT" ) << "/scripts/sum/" << fileName;
  fScriptFileName = fullFileName.str();
}

void
ScriptData::Clear()
{
  TPython pyWrapper;
  pyWrapper.LoadMacro( fScriptFileName.c_str() );
  pyWrapper.Bind( &fPyResultArray, "resultArray" );
  pyWrapper.Exec( "Clear( resultArray )" );
}

void
ScriptData::ProcessEvent( RAT::DS::Root* rDS )
{
  TPython pyWrapper;
  pyWrapper.LoadMacro( fScriptFileName.c_str() );
  pyWrapper.Bind( &fPyResultArray, "resultArray" );
  //pyWrapper.Bind( rDS, "dsEvent" );
  pyWrapper.Exec( "print 'hello'" );
  pyWrapper.Exec( "Hello( 'bob' )");
  pyWrapper.Exec( "Clear( resultArray )" );
  //pyWrapper.Exec( "SumEvent( dsEvent, resultArray )" );
  fScriptData.clear();
  for( int i = 0; i < kNumChannels; i++ )
    {
      RAT::DS::PMTCal* pyPMTCal = reinterpret_cast<RAT::DS::PMTCal*>( fPyResultArray.At( i ) );
      fScriptData.push_back( new RAT::DS::PMTCal( *pyPMTCal ) );
    }
}
