using namespace std;

#include <Viewer/RIDS/Event.hh>
using namespace Viewer::RIDS;

vector< pair< string, vector< string > > > Event::fsDataNames;

void 
Event::Initialise( const DataNames& sourceTypeStrings ) 
{ 
  fsDataNames = sourceTypeStrings; 
  // Push back a analysis script source
  fsDataNames.push_back( pair< string, vector< string > >( "Script", vector<string>() ) );
}

void
Event::SetTypeNames( int source, 
                     vector<string> types )
{
  fsDataNames[source] = pair< string, vector< string > >( "Script", types );
}

Event::Event()
{
  for( DataNames::const_iterator iTer = fsDataNames.begin(); iTer != fsDataNames.end(); iTer++ )
    {
      Source source( iTer->second.size() );
      fSources.push_back( source );
    }
}

Event::Event( size_t types )
{
  Source source( types );
  fSources.push_back( source );
}

const Source& 
Event::GetSource( int id ) const
{
  return fSources[id];
}

const vector<Channel>& 
Event::GetData( size_t source, 
                size_t type ) const
{
  return GetSource( source ).GetData( type );
}

vector<string>
Event::GetSourceNames()
{
  vector<string> sourceNames;
  for( DataNames::const_iterator iTer = fsDataNames.begin(); iTer != fsDataNames.end(); iTer++ )
    sourceNames.push_back( iTer->first );
  return sourceNames;
}

vector<string>
Event::GetTypeNames( int source )
{
  return fsDataNames[source].second;
}
